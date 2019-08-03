#ifndef QTASCIIARTERDIALOGTEST_H
#define QTASCIIARTERDIALOGTEST_H

#pragma GCC diagnostic push


#include <QtTest/QtTest>
#pragma GCC diagnostic pop

namespace ribi {

class qtasciiartermaindialog_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void all_tests();
};


} //~namespace ribi

#endif // QTASCIIARTERDIALOGTEST_H
