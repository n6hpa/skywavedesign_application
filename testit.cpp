#include <fstream>
#include <iostream>
using namespace std;

#include "testit.h"
#include "CQTest.h"

//============================================================
//====================== constructor =========================
//============================================================

TestIt::TestIt(QPushButton * b)
{
   button=b; // We're using a button to start things.
   teststatus=2; // Return an error if the user doesn't test.
}

//============================================================
//====================== TestItStatus ========================
//============================================================

int TestIt::TestItStatus(void)
{
    // the status of the last test run
    return teststatus;
}

//============================================================
//====================== AddHTML =============================
//============================================================

// Per the spec, collect the data as html.
// It was first saved as plain text, so
// parse through and look for significant
// reports.
//
// NOTE: There may be a better way to do
// this in Qt but after much seeking I didn't
// find it.

void TestIt::AddHTML(void)
{
    FILE * pFile;
    teststatus=0;

    pFile=fopen("log.txt","r");
    if( pFile==NULL )
    {
        // sanity check
        teststatus=3;
        return;
    }
    fclose( pFile );

    pFile=fopen( "log.html", "w" );
    if( pFile==NULL )
    {
        teststatus=3;
        return;
    }

    fputs( "<!DOCTYPE html>\n", pFile );
    fputs( "<html>\n", pFile );
    fputs( "<body>\n", pFile );

    std::ifstream file( "log.txt" );
    std::string str;

    while ( std::getline(file, str) )
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
            fputs( "<h2>", pFile );
            fputs( str.c_str(), pFile );
            fputs( "</h2>", pFile );
        }
        else if( str2.compare("PASS")==0 )
        {
            // a PASS condition is green
            fputs( "<font color=\"green\">", pFile );
            fputs( "<p>", pFile );
            fputs( str.c_str(), pFile );
            fputs( "</p>\n", pFile );
            fputs( "</font>", pFile );
        }
        else if( str2.compare("FAIL")==0 )
        {
            // a FAIL condition is red
            fputs( "<font color=\"red\">", pFile );
            fputs( "<p>", pFile );
            fputs( str.c_str(), pFile );
            fputs( "</p>\n", pFile );
            fputs( "</font>", pFile );
            teststatus=1;
        }
        else if( (str2.compare("Tota")==0) && (teststatus==1) )
        {
            // make totals red if there was a failure
            fputs( "<font color=\"red\">",pFile );
            fputs( "<p>", pFile );
            fputs( str.c_str(), pFile );
            fputs( "</p>\n", pFile );
            fputs( "</font>", pFile );
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
    fputs( "</body>\n", pFile );
    fputs( "</html>\n", pFile );
    file.close();
    fclose( pFile );
    remove( "log.txt" );
}

//============================================================
//====================== domybutton ==========================
//============================================================

void TestIt::domybutton()
{
    QStringList cmdline;
    // We'll log to a file:
    cmdline<<" "<<"-o"<<"log.txt";
    button->setText( "Processing" );
    button->show();
    // Make sure we see the message.
    QCoreApplication::processEvents();
    // Do the actual tests.
    CQTest tc;
    QTest::qExec( &tc,  cmdline );
    // Wrap the text output with html. (log.html)
    AddHTML();
    // Tell user the verdict.
    if( teststatus==0 ) button->setText( "PASS: Test Again?" );
    else button->setText( "FAIL: Test Again?" );
    button->show();
}


