#ifndef TESTIT_H
#define TESTIT_H

#include <QApplication>
#include <QtTest/QtTest>
#include <QPushButton>

//============================================================
//====================== TestIt ==============================
//============================================================

// Run the tests from here.

class TestIt : public QObject
{
    Q_OBJECT

public:

TestIt(void);
int testitStatus(void);

private:

public slots:

    void doCQtest();

private:
    int teststatus;
};



#endif // TESTIT_H
