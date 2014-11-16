// must be in .h file!
//#include <QApplication>
//#include <QtTest/QtTest>

#include "cqtest.h"

//============================================================
//====================== housekeeping ========================
//============================================================

void CQTest::initTestCase(void)
{
    // Calculate how many bytes we need.
    elementsz=CqueueElementSize();
    sz=CqueueSize();
    // Get memory for two queues to test. Set them up.
    queue1array=(CqueueElement *) malloc( sz*elementsz );
    CqueueInit( &queue1, queue1array );
    queue2array=(CqueueElement *) malloc( sz*elementsz );
    CqueueInit( &queue2, queue2array );
}

void CQTest::cleanupTestCase(void)
{
    free(queue1array);
    free(queue2array);
}

void CQTest::init()
{
    // executed before each test function
}

void CQTest::cleanup()
{
    // executed after each test function
}

//============================================================
//====================== testAddFirst ========================
//============================================================

// Start super simple, with just one member in and out.

void CQTest::testAddFirst()
{
    int currentsz;
    CqueueAdd(&queue1,10);
    // Check the count. Should be just the 1 member.
    currentsz=CqueueCount(&queue1);
    QCOMPARE( currentsz, 1 );
}

//============================================================
//====================== testEmptyFirst ======================
//============================================================

void CQTest::testEmptyFirst()
{
    int currentsz;
    int element;
    element=CqueueRemove(&queue1);
    currentsz=CqueueCount(&queue1);
    // We wrote '10' so it better be '10'
    QVERIFY2(element==10, "Bad Data!");
    // and the count should be back to 0
    QCOMPARE( currentsz, 0 );
}

//============================================================
//====================== testAddSecond =======================
//============================================================

// Now do two members ...

void CQTest::testAddSecond()
{
    int currentsz;
    CqueueAdd(&queue1,11);
    CqueueAdd(&queue1,12);
    currentsz=CqueueCount(&queue1);
    QCOMPARE( currentsz, 2 );
}

//============================================================
//====================== testEmptySecond =====================
//============================================================

// ... and check we get those two members back.

void CQTest::testEmptySecond()
{
    int currentsz;
    int element1;
    int element2;
    element1=CqueueRemove(&queue1);
    QVERIFY2(element1==11, "Bad Data1!");
    currentsz=CqueueCount(&queue1);
    QVERIFY2( currentsz==1,"Bad Count, expect 1!" );
    element2=CqueueRemove(&queue1);
    QVERIFY2(element2==12, "Bad Data2!");
    currentsz=CqueueCount(&queue1);
    QVERIFY2( currentsz==0,"Bad Count, expect 0!" );
 }

//============================================================
//====================== testAddAll ==========================
//============================================================

// Fill to the brink.

void CQTest::testAddAll()
{
    int currentsz;

    for (int i=0; i<sz; i++ )
    {
        CqueueAdd( &queue1, i );
        currentsz=CqueueCount(&queue1);
        QCOMPARE( currentsz, i+1 );
    }
}

//============================================================
//====================== testRemoveAll =======================
//============================================================

// Make sure a full queue reads back properly.

void CQTest::testRemoveAll()
{
    int currentsz;
    int element;

    for (int i=0; i<sz; i++ )
    {
        element=CqueueRemove( &queue1 );
        currentsz=CqueueCount(&queue1);
        QCOMPARE( currentsz, (sz-i)-1 );
        QCOMPARE( element, i );
    }
}

//============================================================
//====================== testOverflow ========================
//============================================================

// Stuff too much data in and see what happens.

void CQTest::testOverflow()
{
    int currentsz;
    int status;

    for (int i=0; i<sz; i++ )
    {
        CqueueAdd( &queue1, i );
        currentsz=CqueueCount(&queue1);
        QCOMPARE( currentsz, i+1 );
    }
    // This should overflow.
    status=CqueueAdd( &queue1, 77 );
    // Did it overflow?
    QVERIFY2( status==FULL, "Expected FULL!" );
    // Did the count remain at the max?
    currentsz=CqueueCount(&queue1);
    QVERIFY2( currentsz==sz, "Unexpected count!" );
}

//============================================================
//====================== testRemoveOverflow ==================
//============================================================

// Make sure all of the data that fit is still good.

void CQTest::testRemoveOverflow()
{
    int currentsz;
    int element;

    for (int i=0; i<sz; i++ )
    {
        element=CqueueRemove( &queue1 );
        currentsz=CqueueCount(&queue1);
        QCOMPARE( currentsz, (sz-i)-1 );
        QCOMPARE( element, i );
    }
}

//============================================================
//====================== testDual ============================
//============================================================

// Run two queues at once to see if there is
// corruption between them.

void CQTest::testDual()
{
    int currentsz;
    int element;

    CqueueAdd(&queue1,20);
    currentsz=CqueueCount(&queue1);
    QVERIFY2( currentsz==1, "Bad queue1 count1!" );

    currentsz=CqueueCount(&queue2);
    QVERIFY2( currentsz==0, "Bad queue2 count0!" );

    CqueueAdd(&queue2,30);
    CqueueAdd(&queue2,31);
    currentsz=CqueueCount(&queue2);
    QVERIFY2( currentsz==2, "Bad queue2 count2!" );

    currentsz=CqueueCount(&queue1);
    QVERIFY2( currentsz==1, "Bad queue1 count1a!" );

    element=CqueueRemove( &queue1 );
    QVERIFY2( element==20, "Bad queue1 Data!" );

    currentsz=CqueueCount(&queue1);
    QVERIFY2( currentsz==0, "Bad queue1 count0!" );

    currentsz=CqueueCount(&queue2);
    QVERIFY2( currentsz==2, "Bad queue2 count2a!" );

    element=CqueueRemove( &queue2 );
    QVERIFY2( element==30, "Bad queue2 Data30!" );

    currentsz=CqueueCount(&queue2);
    QVERIFY2( currentsz==1, "Bad queue2 count1a!" );

    element=CqueueRemove( &queue2 );
    QVERIFY2( element==31, "Bad queue2 Data31!" );

    currentsz=CqueueCount(&queue2);
    QVERIFY2( currentsz==0, "Bad queue2 count0a" );

    currentsz=CqueueCount(&queue1);
    QVERIFY2( currentsz==0, "Bad queue1 count0a" );
}

//============================================================
//====================== testEmpty ===========================
//============================================================

// make sure an empty queue returns empty.

void CQTest::testEmptyData()
{
    int currentsz;
    int element;
    element=CqueueRemove(&queue1);
    currentsz=CqueueCount(&queue1);
    QVERIFY2(element==EMPTY, "Bad EMPTY Data!");
    QCOMPARE( currentsz, 0 );
}

//============================================================
//====================== testBenchmark =======================
//============================================================

// See how fast it is because we can.

void CQTest::testBenchmark()
{
    QBENCHMARK
    {
        for( int i=0; i<100000; i++ )
        {
            CqueueAdd( &queue1, 1 );
            CqueueRemove( &queue1 );
        }
    }
}


