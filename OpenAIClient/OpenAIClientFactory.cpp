#include "OpenAIClientFactory.h"

OpenAIClientFactory::OpenAIClientFactory()
{

}

OpenAIChatClient *OpenAIClientFactory::createChatClient()
{
    return new OpenAIChatClient();
}

OpenAIImageClient *OpenAIClientFactory::createImageClient()
{
    return new OpenAIImageClient();
}
