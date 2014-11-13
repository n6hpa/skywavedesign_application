#include <QApplication>
#include <QPushButton>

#include "qunittest.h"
#include "cqtest.h"
#include "testit.h"

//============================================================
//====================== main ================================
//============================================================

int main(int argc, char** argv)
{
   QApplication a(argc,argv);

   QPushButton *button = new QPushButton( "Test" );
   TestIt b(button);
   // Just using 1 simple button.
   button->setGeometry( 200, 200, 180, 60 );
   // When the button is pressed, do the test in TestIt
   QObject::connect( button, SIGNAL(clicked()), &b, SLOT( domybutton() ));
   button->show();
   a.exec();
   return b.TestItStatus();
}

#include "qunittest.moc"
