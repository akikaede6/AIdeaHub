#include "ChatWidget.h"
#include "OpenAIClient/OpenAIClientFactory.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>

ChatWidget::ChatWidget(QWidget *parent)
    : QWidget{parent}
    , m_apiClient(OpenAIClientFactory::createChatClient())
    , m_sendBtn(new QPushButton(tr("Send"), this))
    , m_sendEdit(new QLineEdit(this))
    , m_textEdit(new QTextEdit(this))
{
    init();
    initConnection();
}

ChatWidget::~ChatWidget()
{
    m_thread.quit();
    m_thread.wait();
}

void ChatWidget::init()
{
    QVBoxLayout *chatLayout = new QVBoxLayout(this);

    chatLayout->addWidget(m_textEdit);
    chatLayout->addWidget(m_sendEdit);
    chatLayout->addWidget(m_sendBtn, 0, Qt::AlignRight);
    m_apiClient->moveToThread(&m_thread);
    m_thread.start();
}

void ChatWidget::initConnection()
{
    connect(m_sendBtn, &QPushButton::clicked, this, &ChatWidget::onSendBtnClicked);
    connect(m_apiClient, &OpenAIApiClient::textGenerated, this, &ChatWidget::onTextGenerated);
    connect(m_sendEdit, &QLineEdit::returnPressed, this, &ChatWidget::onSendBtnClicked);
}

void ChatWidget::onSendBtnClicked()
{
    m_textEdit->append("user:");
    m_textEdit->append(m_sendEdit->text());
    m_apiClient->generate_respond(m_sendEdit->text());
    m_textEdit->append("responds:");
    m_sendEdit->clear();
}

void ChatWidget::onTextGenerated(const QString &text)
{
    m_textEdit->append(QString("%1\n").arg(text.trimmed()));
}
