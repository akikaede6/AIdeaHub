#include "OpenAIImageClient.h"

OpenAIImageClient::OpenAIImageClient()
{

}

void OpenAIImageClient::generate_respond(const QString &prompt)
{
    QUrl url(m_baseUrl + "/v1/images/generations");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer " + m_apiKey).toUtf8());

    QJsonObject jsonObj;
    jsonObj["prompt"] = prompt;
    jsonObj["n"] = 2;
    jsonObj["size"] = "1024x1024";

    QJsonDocument jsonDoc(jsonObj);
    auto reply = m_manager->post(request, jsonDoc.toJson());

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            auto jsonResponse = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonResponse);
            auto result = jsonDoc.object();
            auto data = result["data"].toArray();
            foreach (auto obj, data) {
                auto text = obj.toObject()["url"].toString();
                emit textGenerated(text);
            }
        } else {
            emit textGenerated(reply->errorString());
        }
        reply->deleteLater();
    });
}
