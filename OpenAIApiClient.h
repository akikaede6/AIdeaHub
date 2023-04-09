#ifndef OPENAIAPICLIENT_H
#define OPENAIAPICLIENT_H

#include <string>
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>

class OpenAIApiClient
{
public:
    OpenAIApiClient(const std::string& api_key);
    std::string generate_text(const std::string& prompt);

private:
    const std::string base_url = "api.openai.com";
    const std::string proxy_host = "127.0.0.1";
    int proxy_port = 7890;
    httplib::SSLClient client;
    std::string engine = "text-davinci-003";
    std::string api_key;
};

#endif // OPENAIAPICLIENT_H
