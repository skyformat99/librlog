//
// Created by Giuseppe Persico on 12/04/2018.
//

#include "../include/client.hpp"

remlog::client::libcurl::libcurl() {
    std::call_once(this->global_init_flag, &remlog::client::libcurl::init, this);
    this->handle = curl_easy_init();
    if (this->handle == nullptr) {
        throw std::runtime_error("Can not initialize libcurl easy handle!");
    }
}

remlog::client::libcurl::~libcurl() noexcept {
    if (this->handle != nullptr) {
        curl_easy_cleanup(this->handle);
    }
    curl_global_cleanup();
}

void remlog::client::libcurl::init() {
    const CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
    if (result != CURLE_OK) {
        throw std::runtime_error(curl_easy_strerror(result));
    }
}

void remlog::client::libcurl::log(const char *url, const char *message) {
    curl_easy_setopt(this->handle, CURLOPT_URL, url);
    curl_easy_setopt(this->handle, CURLOPT_VERBOSE, false);
    curl_easy_setopt(this->handle, CURLOPT_POST, true);
    curl_easy_setopt(this->handle, CURLOPT_POSTFIELDS, message);
    const CURLcode result = curl_easy_perform(this->handle);
    if (result != CURLE_OK) {
        throw std::runtime_error(curl_easy_strerror(result));
    }
}

nlohmann::json remlog::client::log(const std::string &url, remlog::message::stream &message) {
    remlog::client::libcurl curl;
    curl.log(url.c_str(), message.get_content().c_str());

    nlohmann::json response;
    return response;
}