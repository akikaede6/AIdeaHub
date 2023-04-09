#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::string openai_api_key = ""; // TODO
    MainWindow w(openai_api_key);
    w.setWindowTitle("openai desktop for LiChen & qiqi");
    w.show();
    return a.exec();
}
