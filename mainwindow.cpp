#include "mainwindow.h"

#include <QVBoxLayout>

MainWindow::MainWindow(const QString& api_key, QWidget *parent)
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
    connect(m_sendBtn, &QPushButton::clicked, this, &MainWindow::onSendBtnClicked);
    setCentralWidget(mainWidget);

    connect(&m_apiClient, &OpenAIApiClient::textGenerated, this, &MainWindow::onTextGenerated);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onSendBtnClicked() {
    m_textEdit->append("user:");
    m_textEdit->append(m_sendEdit->text());
    m_apiClient.generate_text(m_sendEdit->text());
    m_textEdit->append("\nresponds:");
}

void MainWindow::onTextGenerated(const std::string &text)
{
    m_textEdit->append(QString::fromStdString(text).trimmed());
}
