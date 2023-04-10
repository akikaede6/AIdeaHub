#include "OpenAIApiClient.h"

#include <QDebug>

OpenAIApiClient::OpenAIApiClient()
{
    QFile file(QString("%1/.config/%2/key").arg(QDir::homePath()).arg(projectName));
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        m_apiKey = stream.readAll().trimmed();
        file.close();
    } else {
        qDebug() << "Error: could not read API key file";
    }

    m_manager = new QNetworkAccessManager(this);
    if (!proxy_host.isEmpty() && proxy_port != 0) {
        QNetworkProxy proxy(QNetworkProxy::HttpProxy, proxy_host, proxy_port);
        m_manager->setProxy(proxy);
    }
}
