#ifndef QTASCIIARTERMENUDIALOGTEST_H
#define QTASCIIARTERMENUDIALOGTEST_H

#pragma GCC diagnostic push

#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QtTest/QtTest>
#pragma GCC diagnostic pop

namespace ribi {

class qtasciiartermenudialog_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void all_tests();
};


} //~namespace ribi

#endif // QTASCIIARTERMENUDIALOGTEST_H
