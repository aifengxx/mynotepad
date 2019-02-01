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
    QObject::connect(ui->saveAction,SIGNAL(triggered()),this,SLOT(saveFileSlot()));
    QObject::connect(ui->exitAction,SIGNAL(triggered()),this,SLOT(close()));//这是个很大的bug啊，无论什么情况都能退出
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
void MainWindow::saveFileSlot()
{
    if(saveFileName.isEmpty())//先判断saveFileName是不是为空
    {
            this->saveAsFileSlot();
    }
    else//如果文件名不为空，直接保存就行了
    {
        QFile *file=new QFile;
        file->setFileName(saveFileName);
        bool ok=file->open(QIODevice::WriteOnly);//写入文件？
        if(ok)
        {
            QTextStream out(file);
            out<<ui->textEdit->toPlainText();//我们做一个重对象，放到out当中。这个流当中就放到C盘当中去了
            file->close();//保存文件后关闭文件
            delete file;//然后删除文件
            //这样我们就演示了怎么保存文件，尽管有些抽象和不理解内部的机制
        }
    }
    if(ui->textEdit->document()->isModified())//这个是多余的啊，我想模拟刚打开的空文件不能保存。
    {
        QFile *file=new QFile;
        file->setFileName(saveFileName);
        bool ok=file->open(QIODevice::WriteOnly);//写入文件？
        if(ok)
        {
            QTextStream out(file);
            out<<ui->textEdit->toPlainText();//我们做一个重对象，放到out当中。这个流当中就放到C盘当中去了
            file->close();//保存文件后关闭文件
            delete file;//然后删除文件
            //这样我们就演示了怎么保存文件，尽管有些抽象和不理解内部的机制
        }
        else
         {
            QMessageBox::information(this,"Error","save error");
            return;
          }
      }
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
/*void MainWindow::exitSlot()
{
    if(ui->textEdit->document()->isModified())
    {
        QMessageBox msgBox;
          msgBox.setText("The document has been modified.");
          msgBox.setInformativeText("Do you want to save your changes?");
          msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
          msgBox.setDefaultButton(QMessageBox::Save);
          int ret = msgBox.exec();
          switch (ret) {
             case QMessageBox::Save:
                 // Save was clicked
              QFile *file=new QFile;
              file->setFileName(saveFileName);
              bool ok=file->open(QIODevice::WriteOnly);//写入文件？
              if(ok)
              {
                  QTextStream out(file);
                  out<<ui->textEdit->toPlainText();//我们做一个重对象，放到out当中。这个流当中就放到C盘当中去了
                  file->close();//保存文件后关闭文件
                  delete file;//然后删除文件
                  //这样我们就演示了怎么保存文件，尽管有些抽象和不理解内部的机制
              }
              else
               {
                  QMessageBox::information(this,"Error","save error");
                  return;
                }
                 break;
             case QMessageBox::Discard:
              quit();
                 // Don't Save was clicked
                 break;
             case QMessageBox::Cancel:
                 // Cancel was clicked
                 break;
             default:
                 // should never be reached
                 break;
           }
    }
    else
    {
        return;
    }


}
*/
