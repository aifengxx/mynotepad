#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Untitiled_aifengxx.txt");
    QObject::connect(ui->newAction,SIGNAL(triggered()),this,SLOT(newFileSlot()));
    QObject::connect(ui->openAction,SIGNAL(triggered()),this,SLOT(openFlieSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::newFileSlot()
{
    //如果当前文档的内容已经改变了,就打印出来
    if(ui->textEdit->document()->isModified())
    {
        qDebug()<<"Current file is modified";

    }
    else
    {
      //qDebug()<<"Not modified";
      // ui->textEdit->clear();//这一行个人认为没必要加上去，本来就没有内容为什么要清理呢？
        this->setWindowTitle("Untitled_new.txt");
    }
}
void MainWindow::openFlieSlot()
{
    //first，we need to get the file name
    QString fileName=QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath());
    //这个函数有三个参数：this，“Open File”和QDir。目的是在程序运行目录下的路径下打开
    qDebug()<<"open file"<<fileName;
}
