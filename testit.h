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

TestIt(QPushButton * b);

int TestItStatus(void);

private:

void AddHTML(void);

public slots:

    void domybutton();

private:
    QPushButton * button;
    int teststatus;
};



#endif // TESTIT_H
