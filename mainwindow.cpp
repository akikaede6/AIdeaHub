#include "mainwindow.h"

#include <QVBoxLayout>

MainWindow::MainWindow(const std::string& api_key, QWidget *parent)
    : QMainWindow(parent)
    , m_apiClient(api_key)
    , m_sendBtn(new QPushButton(tr("Send"), this))
    , m_sendEdit(new QLineEdit(this))
    , m_textEdit(new QTextEdit(this))
{
    QWidget *mainWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->addWidget(m_textEdit);
    mainLayout->addWidget(m_sendEdit);
    mainLayout->addWidget(m_sendBtn, 0, Qt::AlignRight);
    connect(m_sendBtn, &QPushButton::clicked, this, &MainWindow::on_sendRequestButton_clicked);
    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_sendRequestButton_clicked() {
    QString prompt = m_sendEdit->text();
    m_textEdit->append("user:");
    m_textEdit->append(m_sendEdit->text());
    std::string response = m_apiClient.generate_text(prompt.toStdString());
    m_textEdit->append("\nresponds:");
    m_textEdit->append(QString::fromStdString(response).trimmed());
}
