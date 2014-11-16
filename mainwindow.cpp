#include <QApplication>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "testit.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("Ready to test");
    status=2; // show we're as yet untested
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    char filename[]={ 'l', 'o', 'g', '.', 'h', 't', 'm', 'l', 0 }; // hardcoded for now

    // tell user we're busy
    ui->label->setText("Processing...");
    // Make sure we see the message.
    QCoreApplication::processEvents();

    // now do the tests
    TestIt t;
    ss->str("");
    t.doCQtest();
    ui->textEdit->setText(ss->str().c_str());

    // write the final html file to disk
    FILE * pFile;
    pFile=fopen( filename, "w" );
    if( pFile==NULL )
    {
        status=3;
        return;
    }
    fputs( ss->str().c_str(), pFile );
    fclose( pFile );

    // Tell user the verdict.
    if( t.testitStatus()==0 )
    {
        ui->label->setText("PASSED");
        status=0;
    }
    else
    {
        ui->label->setText("FAILED");
        status=1;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QApplication::quit();
}

void MainWindow::textRefresh(ostringstream * s)
{
    ss=s;
    ui->textEdit->setText(ss->str().c_str());
}

int MainWindow::testStatus(void)
{
  return status;
}




