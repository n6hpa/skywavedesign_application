#include <QApplication>
//#include <QPushButton>
#include "mainwindow.h"
#include <iostream>
#include <fstream>
using namespace std;
#include <sstream>

#include "qunittest.h"
#include "cqtest.h"
#include "testit.h"

//============================================================
//====================== main ================================
//============================================================

int main(int argc, char** argv)
{
   QApplication a(argc,argv);
   MainWindow w;

   streambuf * savestreambuf = cout.rdbuf();
   ostringstream strCout;
   cout.rdbuf( strCout.rdbuf() );
   // initial text box message
   cout <<"Untested"<<endl;
   // setup the text redirection
   w.textRefresh(&strCout);
   w.show();
   a.exec();
   cout.rdbuf( savestreambuf );
   return w.testStatus();
}

#include "qunittest.moc"
