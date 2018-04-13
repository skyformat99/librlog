//
// Created by Giuseppe Persico on 12/04/2018.
//

#include "../include/client.hpp"

rlog::client::client() noexcept {
    std::call_once(this->curl_once_flag_init, &rlog::client::init_libcurl, this);
}

rlog::client::~client() noexcept {
    curl_global_cleanup();
}

void rlog::client::init_libcurl() {
    const CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
    if (result != CURLE_OK) {
        throw std::runtime_error(curl_easy_strerror(result));
    }
}

CURL *rlog::client::get_curl_handle() {
    CURL *curl_handle = curl_easy_init();
    if (curl_handle == nullptr) {
        throw std::runtime_error("Can not initialize libcurl easy handle!");
    }
    return curl_handle;
}

nlohmann::json rlog::client::log_message(rlog::options &options, rlog::message::stream &message) {
    CURL *curl_handle = this->get_curl_handle();
    curl_easy_setopt(curl_handle, CURLOPT_URL, options.get_url().c_str());
    curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, false);
    curl_easy_setopt(curl_handle, CURLOPT_POST, true);

    std::string post_data = message.get_content();
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, post_data.c_str());

    /*struct curl_slist *chunk = nullptr;
    chunk = curl_slist_append(chunk, "Content-type: application/json");
    curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, chunk);*/


    const CURLcode result = curl_easy_perform(curl_handle);
    if (result != CURLE_OK) {
        //curl_slist_free_all(chunk);
        curl_easy_cleanup(curl_handle);
        throw std::runtime_error(curl_easy_strerror(result));
    }
    //curl_slist_free_all(chunk);
    curl_easy_cleanup(curl_handle);

    nlohmann::json response;
    return response;
}