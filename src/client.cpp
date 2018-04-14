//
// Created by Giuseppe Persico on 12/04/2018.
//

#include "../include/client.hpp"

remlog::client::curl_client::curl_client() {
    std::call_once(this->global_init_flag, &remlog::client::curl_client::init, this);
    this->handle = curl_easy_init();
    if (this->handle == nullptr) {
        throw std::runtime_error("Can not initialize libcurl easy handle!");
    }
}

remlog::client::curl_client::~curl_client() noexcept {
    if (this->handle != nullptr) {
        curl_easy_cleanup(this->handle);
    }
    curl_global_cleanup();
}

void remlog::client::curl_client::init() {
    const CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
    if (result != CURLE_OK) {
        throw std::runtime_error(curl_easy_strerror(result));
    }
}

void remlog::client::curl_client::log(const char * url, const char *message) {
    curl_easy_setopt(this->handle, CURLOPT_URL, url);
    curl_easy_setopt(this->handle, CURLOPT_POST, true);
    curl_easy_setopt(this->handle, CURLOPT_VERBOSE, false);
    curl_easy_setopt(this->handle, CURLOPT_POSTFIELDS, message);
    struct curl_slist *chunk = nullptr;
    curl_slist_append(chunk, "Content-Type: text/json");
    curl_easy_setopt(this->handle, CURLOPT_HTTPHEADER, chunk);
    const CURLcode result = curl_easy_perform(this->handle);
    curl_slist_free_all(chunk);
    if (result != CURLE_OK) {
        throw std::runtime_error(curl_easy_strerror(result));
    }
}

void remlog::client::log(const std::string &url, remlog::message::stream &message) {
    remlog::client::curl_client curl_client;
    curl_client.log(url.c_str(), message.get_content().c_str());
}

void remlog::async_client::log(const std::string &url, remlog::message::stream &message) {
    remlog::client::curl_client curl_client;
    curl_client.log(url.c_str(), message.get_content().c_str());
}