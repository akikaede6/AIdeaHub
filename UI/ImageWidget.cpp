#include "ImageWidget.h"
#include "OpenAIClient/OpenAIImageClient.h"
#include "OpenAIClient/OpenAIClientFactory.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QWebEnginePage>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QFileDialog>

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

    m_view->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_downloadAction = new QAction(this);
    m_downloadAction->setIconVisibleInMenu(true);
    m_downloadAction->setText(tr("Download"));
    m_view->addAction(m_downloadAction);
}

void ImageWidget::initConnection()
{
    connect(m_sendBtn, &QPushButton::clicked, this, &ImageWidget::onSendBtnClicked);
    connect(m_apiClient, &OpenAIImageClient::textGenerated, this, &ImageWidget::onTextGenerated);
    connect(m_downloadAction, &QAction::triggered, this, &ImageWidget::onDownloadTriggered);
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

void ImageWidget::onDownloadTriggered(bool triggered)
{
    Q_UNUSED(triggered);
    QNetworkAccessManager networkAccessManager;
    QNetworkReply* networkReply = networkAccessManager.get(QNetworkRequest(m_view->url()));
    QEventLoop eventLoop;
    connect(networkReply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (networkReply->error() == QNetworkReply::NoError) {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), QString(), tr("Images (*.png *.xpm *.jpg)"));
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(networkReply->readAll());
                file.close();
            }
        }
    }
    networkReply->deleteLater();
}
