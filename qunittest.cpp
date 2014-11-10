#include <QApplication>
#include <QtTest/QtTest>
#include <QPushButton>
#include <fstream>
#include "qunittest.h"
#include <iostream>
using namespace std;

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

    void initTestCase(void)
    {
        elementsz=CqueueElementSize();
        sz=CqueueSize();
        queue1array=(CqueueElement *) malloc( sz*elementsz );
        CqueueInit( &queue1, queue1array );
        queue2array=(CqueueElement *) malloc( sz*elementsz );
        CqueueInit( &queue2, queue2array );
    }

    void cleanupTestCase()
    {
        free(queue1array);
        free(queue2array);
    }

    void init()
    {
        // executed before each test function
    }

    void cleanup()
    {
        // executed after each test function
    }

    // Start super simple with one member in and out.
    void testAddFirst()
    {
        int currentsz;
        CqueueAdd(&queue1,10);
        currentsz=CqueueCount(&queue1);
        QCOMPARE( currentsz, 1 );
    }

    void testEmptyFirst()
    {
        int currentsz;
        int element;
        element=CqueueRemove(&queue1);
        currentsz=CqueueCount(&queue1);
        QVERIFY2(element==10, "Bad Data!");
        QCOMPARE( currentsz, 0 );
    }

    // Now do two members ...
    void testAddSecond()
    {
        int currentsz;
        CqueueAdd(&queue1,11);
        CqueueAdd(&queue1,12);
        currentsz=CqueueCount(&queue1);
        QCOMPARE( currentsz, 2 );
    }

    // ... and check we get those two members back.
    void testEmptySecond()
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

    // Fill to the brink.
    void testAddAll()
    {
        int currentsz;

        for (int i=0; i<sz; i++ )
        {
            CqueueAdd( &queue1, i );
            currentsz=CqueueCount(&queue1);
            QCOMPARE( currentsz, i+1 );
        }
    }

    // Make sure a full queue reads back properly.
    void testRemoveAll()
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

    // Stuff too much data in and see what happens.
    void testOverflow()
    {
        int currentsz;
        int status;

        for (int i=0; i<sz; i++ )
        {
            CqueueAdd( &queue1, i );
            currentsz=CqueueCount(&queue1);
            QCOMPARE( currentsz, i+1 );
        }
        status=CqueueAdd( &queue1, 77 );
        QVERIFY2( status==FULL, "Expected FULL!" );
        currentsz=CqueueCount(&queue1);
        QVERIFY2( currentsz==sz, "Unexpected count!" );
    }

    // Make sure all of the data that fit is still good.
    void testRemoveOverflow()
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

    // Run two queues at once to see if there is corruption.
    void testDual()
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

    // make sure an empty queue returns empty.
    void testEmptyData()
    {
        int currentsz;
        int element;
        element=CqueueRemove(&queue1);
        currentsz=CqueueCount(&queue1);
        QVERIFY2(element==EMPTY, "Bad EMPTY Data!");
        QCOMPARE( currentsz, 0 );
    }

    // See how fast it is because we can.
    void testBenchmark()
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
};  


//============================================================
//====================== TestIt ==============================
//============================================================

// Run the tests from here.

class TestIt : public QObject
{
    Q_OBJECT

public:

TestIt(QPushButton * b)
{
   button=b; // We're using a button to start things.
   teststatus=2; // Return an error if the user doesn't test.
}

int TestItStatus(void)
{
    // the status of the last test run
    return teststatus;
}

private:

// Per the spec, collect the data as html.

void AddHTML(void)
{
    FILE * pFile;
    teststatus=0;

    pFile=fopen("log.txt","r");
    if(pFile==NULL)
    {
        // sanity check
        return;
    }
    fclose(pFile);

    pFile=fopen("log.html","w");
    if(pFile==NULL)
    {
        return;
    }

    fputs("<!DOCTYPE html>\n",pFile);
    fputs("<html>\n",pFile);
    fputs("<body>\n",pFile);

    std::ifstream file("log.txt");
    std::string str;

    while ( std::getline(file, str))
    {
        std::string str2;

        if( str.length()>3 )
        {
          str2=str.substr(0,4);
        }
        else
        {
           // dummy value since the string is too short
           str2="    ";
        }

        // keep this simple since it's a test

        if(str2.compare("****")==0)
        {
            // a heading
            fputs("<h2>",pFile);
            fputs(str.c_str(),pFile);
            fputs("</h2>",pFile);
        }
        else if(str2.compare("PASS")==0)
        {
            // a PASS condition is green
            fputs("<font color=\"green\">",pFile);
            fputs("<p>",pFile);
            fputs(str.c_str(),pFile);
            fputs("</p>\n",pFile);
            fputs("</font>",pFile);
        }
        else if(str2.compare("FAIL")==0)
        {
            // a FAIL condition is red
            fputs("<font color=\"red\">",pFile);
            fputs("<p>",pFile);
            fputs(str.c_str(),pFile);
            fputs("</p>\n",pFile);
            fputs("</font>",pFile);
            teststatus=1;
        }
        else if( (str2.compare("Tota")==0) && teststatus==1 )
        {
            // make totals red if there was a failure
            fputs("<font color=\"red\">",pFile);
            fputs("<p>",pFile);
            fputs(str.c_str(),pFile);
            fputs("</p>\n",pFile);
            fputs("</font>",pFile);
            teststatus=1;
        }
        else
        {
            // otherwise, normal text
            fputs("<p>",pFile);
            fputs(str.c_str(),pFile);
            fputs("</p>\n",pFile);
        }
    }
    fputs("</body>\n",pFile);
    fputs("</html>\n",pFile);
    file.close();
    fclose(pFile);
    remove("log.txt");
}

public slots:

    void domybutton()
    {
        QStringList cmdline;
        // We'll log to a file:
        cmdline<<" "<<"-o"<<"log.txt";
        button->setText("Processing");
        button->show();
        // Make sure we see the message.
        QCoreApplication::processEvents();
        // Do the actual tests.
        CQTest tc;
        QTest::qExec( &tc,  cmdline );
        // Wrap the text output with html. (log.html)
        AddHTML();
        // Tell user the verdict.
        if( teststatus==0 ) button->setText("PASS: Test Again?");
        else button->setText("FAIL: Test Again?");
        button->show();
    }

 private:
    QPushButton * button;
    int teststatus;
};


//============================================================
//====================== main ================================
//============================================================

int main(int argc, char** argv)
{
   QApplication a(argc,argv);

   QPushButton *button = new QPushButton("Test");
   TestIt b(button);
   // Just using 1 simple button.
   button->setGeometry(200,200,180,60);
   // When the button is pressed, do the test in TestIt
   QObject::connect(button, SIGNAL(clicked()), &b, SLOT(domybutton()   ));
   button->show();
   a.exec();
   return b.TestItStatus();
}

#include "qunittest.moc"
