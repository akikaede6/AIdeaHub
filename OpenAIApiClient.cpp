#include "OpenAIApiClient.h"
#include "json.hpp"

OpenAIApiClient::OpenAIApiClient(const std::string& api_key) : client(base_url), api_key(api_key)
{
    client.set_proxy(proxy_host.c_str(), proxy_port);
}

std::string OpenAIApiClient::generate_text(const std::string& prompt) {
    httplib::Headers headers = {
        {"Authorization", "Bearer " + api_key},
        {"Content-Type", "application/json"},
    };

    nlohmann::json data = {
        {"model", engine},
        {"prompt", prompt},
        {"max_tokens", 100},
    };

    std::cout << data.dump();
    auto response = client.Post("/v1/completions", headers, data.dump(), "application/json");
    if (response && response->status == 200) {
        auto result = nlohmann::json::parse(response->body);
        return result["choices"][0]["text"].get<std::string>();
    } else {
        return "Error: API request failed.";
    }
}
