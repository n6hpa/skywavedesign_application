#ifndef CQTEST_H
#define CQTEST_H

#include <QApplication>
#include <QtTest/QtTest>

extern "C"
{
#include "cqueue.h"
}

//============================================================
//====================== CQTest ==============================
//============================================================

class CQTest : public QObject
{

    Q_OBJECT

public:
    explicit CQTest(QObject *parent = 0) : QObject(parent) {}

    int sz;
    int elementsz;
    Cqueue queue1;
    CqueueElement * queue1array;
    Cqueue queue2;
    CqueueElement * queue2array;

private slots:

    void initTestCase(void);
    void cleanupTestCase(void);
    void init();
    void cleanup();

    // Start super simple, with just one member in and out.
    void testAddFirst();
    void testEmptyFirst();

    // Now do two members ...
    void testAddSecond();

    // ... and check we get those two members back.
    void testEmptySecond();

    // Fill to the brink.
    void testAddAll();

    // Make sure a full queue reads back properly.
    void testRemoveAll();

    // Stuff too much data in and see what happens.
    void testOverflow();

    // Make sure all of the data that fit is still good.
    void testRemoveOverflow();

    // Run two queues at once to see if there is
    // corruption between them.
    void testDual();

    // make sure an empty queue returns empty.
    void testEmptyData();

    // See how fast it is because we can.
    void testBenchmark();

};


#endif // CQTEST_H
