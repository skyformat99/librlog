//
// Created by Giuseppe Persico on 12/04/2018.
//

#include "../include/client.hpp"

remlog::client::curl_client::curl_client() {
    std::call_once(this->global_init, &remlog::client::curl_client::init, this);
}

remlog::client::curl_client::~curl_client() noexcept {
    curl_global_cleanup();
}

void remlog::client::curl_client::init() {
    const CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
    if (result != CURLE_OK) {
        throw std::runtime_error(curl_easy_strerror(result));
    }
}

CURLcode remlog::client::curl_client::log(std::string url, std::string message) {
    CURL *handle = curl_easy_init();
    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(handle, CURLOPT_POST, true);
    curl_easy_setopt(handle, CURLOPT_VERBOSE, false);
    curl_easy_setopt(handle, CURLOPT_POSTFIELDS, message.c_str());
    struct curl_slist *chunk = nullptr;
    curl_slist_append(chunk, "Content-Type: text/json");
    curl_easy_setopt(handle, CURLOPT_HTTPHEADER, chunk);
    const CURLcode result = curl_easy_perform(handle);
    curl_slist_free_all(chunk);
    if (result != CURLE_OK) {
        curl_easy_cleanup(handle);
        throw std::runtime_error(curl_easy_strerror(result));
    }
    curl_easy_cleanup(handle);
    return result;
}

CURLcode remlog::client::_log_util(std::string &url, remlog::message::stream &message) {
    return this->libcurl_client.log(url, message.get_content());
}

std::future<CURLcode> remlog::client::_async_log_util(std::string url, remlog::message::stream &message) {
    return std::async(
            std::launch::async,
            &remlog::client::curl_client::log,
            std::ref(this->libcurl_client),
            std::move(url),
            std::move(message.get_content())
    );
}

CURLcode remlog::client::log(std::string &url, remlog::message::stream &message) {
    return this->_log_util(url, message);
}

CURLcode remlog::client::log(const char *url, remlog::message::stream &message) {
    std::string string_url(url);
    return this->_log_util(string_url, message);
}

std::future<CURLcode> remlog::client::async_log(std::string &url, remlog::message::stream &message) {
    return this->_async_log_util(url, message);
}

std::future<CURLcode> remlog::client::async_log(const char *url, remlog::message::stream &message) {
    return this->_async_log_util(std::string(url), message);
}