#include "mainwindow.h"
#include "ChatWidget.h"
#include "ImageWidget.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    init();
}

MainWindow::~MainWindow()
{
}

void MainWindow::init()
{
    QTabWidget *mainWidget = new QTabWidget(this);
    setCentralWidget(mainWidget);

    ChatWidget *chatWidget = new ChatWidget(mainWidget);
    mainWidget->addTab(chatWidget, tr("Chat"));

    ImageWidget *imageWidget = new ImageWidget(mainWidget);
    mainWidget->addTab(imageWidget, tr("Image"));
}
