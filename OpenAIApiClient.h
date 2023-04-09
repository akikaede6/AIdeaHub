#ifndef OPENAIAPICLIENT_H
#define OPENAIAPICLIENT_H

#include <string>
#include <QObject>

class QNetworkAccessManager;
class OpenAIApiClient : public QObject
{
    Q_OBJECT
public:
    explicit OpenAIApiClient();
    void generate_text(const QString &prompt);

signals:
    void textGenerated(QString);

private:
    QNetworkAccessManager *manager;
    const QString base_url = "https://api.openai.com";
    const QString proxy_host = "127.0.0.1";
    int proxy_port = 7890;
    const QString engine = "text-davinci-003";
    QString api_key;
};

#endif // OPENAIAPICLIENT_H
