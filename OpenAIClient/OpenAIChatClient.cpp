#include "OpenAIChatClient.h"

OpenAIChatClient::OpenAIChatClient()
{
}

void OpenAIChatClient::generate_respond(const QString &prompt)
{
    QUrl url(m_baseUrl + "/v1/completions");
    m_request.setUrl(url);
    m_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    m_request.setRawHeader("Authorization", QString("Bearer " + m_apiKey).toUtf8());

    QJsonObject jsonObj;
    jsonObj["model"] = engine;
    jsonObj["prompt"] = prompt;
    jsonObj["max_tokens"] = 50;

    postMsg(jsonObj);
}

void OpenAIChatClient::postMsg(QJsonObject jsonObj)
{
    jsonObj["prompt"] = jsonObj["prompt"].toString() + m_generateText;
    QJsonDocument jsonDoc(jsonObj);
    auto reply = m_manager->post(m_request, jsonDoc.toJson());
    connect(reply, &QNetworkReply::finished, this, [reply, this, jsonObj]{
            auto jsonResponse = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonResponse);
            auto result = jsonDoc.object();
            auto choices = result["choices"].toArray();
            auto text = choices[0].toObject()["text"].toString();
            m_generateText += text;
            if (choices[0].toObject()["finish_reason"].toString() != QString("stop"))
                postMsg(jsonObj);
            else
                emit textGenerated(QString(m_generateText));
    });
}
