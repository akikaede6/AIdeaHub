#include "OpenAIApiClient.h"
#include "json.hpp"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QNetworkProxy>

OpenAIApiClient::OpenAIApiClient(const std::string& api_key) : api_key(api_key)
{
    manager = new QNetworkAccessManager(this);
    if (!proxy_host.isEmpty() && proxy_port != 0) {
        QNetworkProxy proxy(QNetworkProxy::HttpProxy, proxy_host, proxy_port);
        manager->setProxy(proxy);
    }}

void OpenAIApiClient::generate_text(const std::string& prompt) {
    QUrl url(base_url + "/v1/completions");
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + api_key).c_str());

    nlohmann::json data = {
        {"model", engine},
        {"prompt", prompt},
        {"max_tokens", 100},
    };

    auto reply = manager->post(request, QByteArray(data.dump().c_str()));

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            auto result = nlohmann::json::parse(reply->readAll().toStdString());
            emit textGenerated(result["choices"][0]["text"].get<std::string>());
        } else {
            emit textGenerated(reply->errorString().toStdString());
        }
        reply->deleteLater();
    });
}
