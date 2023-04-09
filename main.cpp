#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("openai desktop for LiChen & qiqi");
    w.show();
    return a.exec();
}
