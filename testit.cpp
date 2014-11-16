#include <fstream>
#include <iostream>
using namespace std;

#include "testit.h"
#include "CQTest.h"

//============================================================
//====================== constructor =========================
//============================================================

TestIt::TestIt()
{
   teststatus=2; // Return an error if the user doesn't test.
}

//============================================================
//====================== testitStatus ========================
//============================================================

int TestIt::testitStatus(void)
{
    // the status of the last test run
    return teststatus;
}


//============================================================
//====================== docqtest ============================
//============================================================

void TestIt::doCQtest()
{
    QStringList cmdline;
    teststatus=0; // no errors yet
    // We'll log to a temporary file:
    cmdline<<" "<<"-o"<<"templog.txt";
    // Do the actual tests.
    CQTest tc;
    QTest::qExec( &tc,  cmdline );
    // QTest::qExec( &tc, 0 );

    // convert the text to html
    std::ifstream file("templog.txt");
    std::string str;

    cout<< "<!DOCTYPE html>\n";
    cout<< "<html>\n";
    cout<< "<body>\n";
    cout<< "<style>\n";
    cout<< "p {line-height:90%; text-indent:20px}" << endl;
    cout<< "</style>" << endl;

    // read each line and super-simple parse it for context
    while( getline(file,str))
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

        if( str2.compare("****")==0 )
        {
            // a heading
            cout << "<h2>" <<endl;
            cout << str.c_str() << endl;
            cout << "</h2>" << endl;
        }
        else if( str2.compare("PASS")==0 )
        {
            // a PASS condition is green
            cout << "<font color=\"green\">" << endl;
            cout << "<p>" << endl;
            cout << str.c_str() << endl;
            cout << "</p>" << endl;
            cout << "</font>" << endl;
        }
        else if( str2.compare("FAIL")==0 )
        {
            // a FAIL condition is red
            cout << "<font color=\"red\">" << endl;
            cout << "<p>" << endl;
            cout << str.c_str() << endl;
            cout << "</p>" << endl;
            cout << "</font>" << endl;
            teststatus=1;
        }
        else if( (str2.compare("Tota")==0) && (teststatus==1) )
        {
            // make totals red if there was a failure
            cout << "<font color=\"red\">" << endl;
            cout << "<p>" << endl;
            cout << str.c_str() << endl;
            cout << "</p>" << endl;
            cout << "</font>" << endl;
            teststatus=1;
        }
        else
        {
            // otherwise, normal text
            cout << "<p>" << endl;
            cout << str.c_str() << endl;
            cout << "</p>" << endl;
        }
    }

    cout<< "</body>\n";
    cout<< "</html>\n";
    // The text has been streamed.
    // Soon we will read it, send it to
    // a text edit box and also to disk.
}


