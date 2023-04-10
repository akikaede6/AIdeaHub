#ifndef OPENAICLIENTFACTORY_H
#define OPENAICLIENTFACTORY_H

#include "OpenAIChatClient.h"
#include "OpenAIImageClient.h"

class OpenAIClientFactory
{
public:
    OpenAIClientFactory();
    static OpenAIChatClient* createChatClient();
    static OpenAIImageClient* createImageClient();
};

#endif // OPENAICLIENTFACTORY_H
