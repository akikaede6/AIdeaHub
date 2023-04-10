#include "OpenAIChatClient.h"

OpenAIChatClient::OpenAIChatClient()
{
}

void OpenAIChatClient::generate_respond(const QString &prompt)
{
    QUrl url(m_baseUrl + "/v1/completions");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer " + m_apiKey).toUtf8());

    QJsonObject jsonObj;
    jsonObj["model"] = engine;
    jsonObj["prompt"] = prompt;
    jsonObj["max_tokens"] = 100;

    QJsonDocument jsonDoc(jsonObj);
    auto reply = m_manager->post(request, jsonDoc.toJson());

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            auto jsonResponse = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonResponse);
            auto result = jsonDoc.object();
            auto choices = result["choices"].toArray();
            auto text = choices[0].toObject()["text"].toString();
            emit textGenerated(text);
        } else {
            emit textGenerated(QString("error: %1").arg(reply->errorString()));
        }
        reply->deleteLater();
    });
}
