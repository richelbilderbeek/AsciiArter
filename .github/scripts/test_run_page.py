#!/usr/bin/env python3
"""Run the WebAssembly version of AsciiArter on the 'Run' page of a built website.

Usage: test_run_page.py <URL of the run page> <image file> <screenshot file>

AsciiArter must show up, load the image via the browser's file picker
and show ASCII art of it. The final screenshot is saved for inspection.
"""
import io
import sys
import time

from PIL import Image, ImageChops, ImageStat
from playwright.sync_api import sync_playwright

# Positions within the AsciiArter window, see qtasciiartermaindialog.ui
LOAD_BUTTON = (11, 11, 147, 39)  # left, top, right, bottom
TEXT_AREA = (11, 45, 549, 447)
START_TIMEOUT_SECS = 60
ART_TIMEOUT_SECS = 30
MIN_STDDEV = 5  # Standard deviation per color channel, from 0 to 255


def stddev(image):
    """How much the pixels of an image differ, 0 for a single color."""
    stat = ImageStat.Stat(image)
    return sum(stat.stddev) / len(stat.stddev)


def main():
    url, image_file, screenshot_file = sys.argv[1:4]
    errors = []
    with sync_playwright() as playwright:
        browser = playwright.chromium.launch()
        page = browser.new_page(viewport={"width": 1280, "height": 1000})
        page.on("pageerror", lambda error: errors.append(str(error)))
        page.on("console", lambda m: print(f"console: {m.text}"))
        page.goto(url)
        frame = page.locator("iframe")

        def screenshot():
            data = frame.screenshot()
            return Image.open(io.BytesIO(data)).convert("RGB")

        print("Waiting for AsciiArter to show up")
        deadline = time.time() + START_TIMEOUT_SECS
        button = 0.0
        while time.time() < deadline and button < MIN_STDDEV:
            time.sleep(1)
            button = stddev(screenshot().crop(LOAD_BUTTON))
            print(f"Variation at the 'Load image' button: {button:.1f}")
        assert button >= MIN_STDDEV, "AsciiArter not shown"
        assert not errors, errors
        empty_text = screenshot().crop(TEXT_AREA)

        print("Loading an image")
        x = (LOAD_BUTTON[0] + LOAD_BUTTON[2]) // 2
        y = (LOAD_BUTTON[1] + LOAD_BUTTON[3]) // 2
        with page.expect_file_chooser() as chooser:
            frame.click(position={"x": x, "y": y})
        chooser.value.set_files(image_file)

        print("Waiting for the ASCII art")
        deadline = time.time() + ART_TIMEOUT_SECS
        change = 0.0
        while time.time() < deadline and change < MIN_STDDEV:
            time.sleep(1)
            shot = screenshot()
            text = shot.crop(TEXT_AREA)
            change = stddev(ImageChops.difference(text, empty_text))
            print(f"Change in the text area: {change:.1f}")
        shot.save(screenshot_file)
        assert change >= MIN_STDDEV, "No ASCII art shown"
        assert not errors, errors
        browser.close()
    print("OK: AsciiArter converts an image to ASCII art")


if __name__ == "__main__":
    main()
