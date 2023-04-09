#ifndef OPENAIAPICLIENT_H
#define OPENAIAPICLIENT_H

#include <string>
#include <QObject>

class QNetworkAccessManager;
class OpenAIApiClient : public QObject
{
    Q_OBJECT
public:
    explicit OpenAIApiClient(const std::string& api_key);
    void generate_text(const std::string& prompt);

signals:
    void textGenerated(std::string);

private:
    QNetworkAccessManager *manager;
    const QString base_url = "https://api.openai.com";
    const QString proxy_host = "127.0.0.1";
    int proxy_port = 7890;
    std::string engine = "text-davinci-003";
    std::string api_key;
};

#endif // OPENAIAPICLIENT_H
