#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>//点击新建以后要跳出一个对话框，所以要使用QMessageBox。
#include <QMainWindow>
#include <QtDebug>//我们需要打印出一些消息看看我们的程序对不对
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QTextStream> //上面四个头文件用来实现openFileSlot(),为什么是这四个呢？如果忘记或者不知道添加某一个该怎么办。
namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void newFileSlot();//新建一个槽，这个槽用于新建这个按钮的功能实现。
    void openFlieSlot();//这个槽目的是打开一个文件，打开一个文件都要用槽。然后接下来到.cpp文件完成这个槽
    void saveAsFileSlot();//保存文件的槽
};

#endif // MAINWINDOW_H
