#include "OpenAIApiClient.h"

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QNetworkProxy>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDir>

const QString projectName = "RiderAI";

OpenAIApiClient::OpenAIApiClient()
{
    QFile file(QString("%1/.config/%2/key").arg(QDir::homePath()).arg(projectName));
    qDebug() << file;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        api_key = stream.readAll().trimmed();
        qDebug() << api_key;
        file.close();
    } else {
        qDebug() << "Error: could not read API key file";
    }

    manager = new QNetworkAccessManager(this);
    if (!proxy_host.isEmpty() && proxy_port != 0) {
        QNetworkProxy proxy(QNetworkProxy::HttpProxy, proxy_host, proxy_port);
        manager->setProxy(proxy);
    }
}

void OpenAIApiClient::generate_text(const QString& prompt) {
    QUrl url(base_url + "/v1/completions");
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer " + api_key).toUtf8());

    QJsonObject jsonObj;
    jsonObj["model"] = engine;
    jsonObj["prompt"] = prompt;
    jsonObj["max_tokens"] = 100;

    QJsonDocument jsonDoc(jsonObj);
    auto reply = manager->post(request, jsonDoc.toJson());

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            auto jsonResponse = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonResponse);
            auto result = jsonDoc.object();
            auto choices = result["choices"].toArray();
            auto text = choices[0].toObject()["text"].toString().toStdString();
            emit textGenerated(text);
        } else {
            emit textGenerated(reply->errorString().toStdString());
        }
        reply->deleteLater();
    });
}
