#ifndef OPENAIIMAGECLIENT_H
#define OPENAIIMAGECLIENT_H

#include "OpenAIApiClient.h"

class OpenAIImageClient : public OpenAIApiClient
{
public:
    OpenAIImageClient();
    void generate_respond(const QString &prompt) override;
};

#endif // OPENAIIMAGECLIENT_H
