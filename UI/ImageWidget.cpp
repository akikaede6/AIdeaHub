#include "ImageWidget.h"
#include "OpenAIClient/OpenAIImageClient.h"
#include "OpenAIClient/OpenAIClientFactory.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>

ImageWidget::ImageWidget(QWidget *parent)
    : QWidget{parent}
    , m_view(new QWebEngineView())
    , m_sendBtn(new QPushButton(tr("Send"), this))
    , m_sendEdit(new QLineEdit(this))
    , m_apiClient(OpenAIClientFactory::createImageClient())
{
    init();
    initConnection();
}

void ImageWidget::init()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_view);
    mainLayout->addWidget(m_sendEdit);
    mainLayout->addWidget(m_sendBtn, 0, Qt::AlignRight);
}

void ImageWidget::initConnection()
{
    connect(m_sendBtn, &QPushButton::clicked, this, &ImageWidget::onSendBtnClicked);
    connect(m_apiClient, &OpenAIImageClient::textGenerated, this, &ImageWidget::onTextGenerated);
}

void ImageWidget::onSendBtnClicked()
{
    m_apiClient->generate_respond(m_sendEdit->text());
}

void ImageWidget::onTextGenerated(const QString &text)
{
    m_view->setUrl(QUrl(text));
    m_view->show();
}
