#ifndef OPENAIAPICLIENT_H
#define OPENAIAPICLIENT_H

#include <string>
#include <QObject>
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

class QNetworkAccessManager;
class OpenAIApiClient : public QObject
{
    Q_OBJECT
public:
    explicit OpenAIApiClient();
    virtual void generate_respond(const QString &prompt) = 0;

signals:
    void textGenerated(QString);

protected:
    QNetworkAccessManager *m_manager;
    QString m_apiKey;
    const QString m_baseUrl = "https://api.openai.com";


private:
    const QString proxy_host = "127.0.0.1";
    int proxy_port = 7890;
};

#endif // OPENAIAPICLIENT_H
