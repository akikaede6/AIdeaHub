#ifndef OPENAICHATCLIENT_H
#define OPENAICHATCLIENT_H

#include "OpenAIApiClient.h"

class OpenAIChatClient : public OpenAIApiClient
{
public:
    OpenAIChatClient();
    void generate_respond(const QString &prompt) override;

private:
    const QString engine = "text-davinci-003";
    const QString proxy_host = "127.0.0.1";
    int proxy_port = 7890;
};

#endif // OPENAICHATCLIENT_H
