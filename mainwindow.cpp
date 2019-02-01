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
    QObject::connect(ui->saveAsAction,SIGNAL(triggered()),this,SLOT(saveAsFileSlot()));
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
void MainWindow::saveAsFileSlot()
{
    if(ui->textEdit->document()->isModified())
    {
        QString fileName=QFileDialog::getSaveFileName(this,"Save File",QDir::currentPath());
        //这样无论如何都会跳出窗口，这是个bug
        if(fileName.isEmpty())
        {
            QMessageBox::information(this,"error","Please enter a file name");
            return;
        }
        QFile *file=new QFile;
        file->setFileName(fileName);
        bool ok=file->open(QIODevice::WriteOnly);//写入文件？
        if(ok)
        {
            QTextStream out(file);
            //ui->textEdit->toPlainText();//这里是取出textEdit当中的纯文本
            out<<ui->textEdit->toPlainText();//我们做一个重对象，放到out当中。这个流当中就放到C盘当中去了
            file->close();//保存文件后关闭文件
            delete file;//然后删除文件
            //这样我们就演示了怎么保存文件，尽管有些抽象和不理解内部的机制
        }

    }

    else
    {
        QMessageBox::information(this,"Error","Text is empty");
        return;
    }
}
