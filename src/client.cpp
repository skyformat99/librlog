//
// Created by Giuseppe Persico on 12/04/2018.
//

#include "client.hpp"

#include <utility>

remlog::client::curl::curl() {
    std::call_once(this->global_init, &remlog::client::curl::init, this);
}

remlog::client::curl::~curl() noexcept {
    curl_global_cleanup();
}

void remlog::client::curl::init() {
    const CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
    if (result != CURLE_OK) {
        throw std::runtime_error(curl_easy_strerror(result));
    }
}

remlog::response remlog::client::curl::log(const std::string url, const std::string message) {
    CURL *handle = curl_easy_init();

    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(handle, CURLOPT_POST, true);
    curl_easy_setopt(handle, CURLOPT_VERBOSE, false);
    curl_easy_setopt(handle, CURLOPT_POSTFIELDS, message.c_str());

	write_callback_ptr_type write_function_ptr = write_callback<std::stringstream>;
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_function_ptr);
	std::unique_ptr<std::stringstream> stream_ptr(new std::stringstream);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, static_cast<void *>(stream_ptr.get()));

    struct curl_slist *chunk = nullptr;
    curl_slist_append(chunk, "Content-Type: text/json");
    curl_easy_setopt(handle, CURLOPT_HTTPHEADER, chunk);

    CURLcode code = curl_easy_perform(handle);
    curl_slist_free_all(chunk);
    curl_easy_cleanup(handle);

    remlog::response response(stream_ptr->str(), code);
    return response;
}

remlog::response remlog::client::log(remlog::url &url, remlog::message::stream &message) {
	return this->curl_client.log(url.get(), message.get());
}


std::future<remlog::response> remlog::client::async_log(
		const remlog::url &url, const remlog::message::stream &message) {
	return std::async(std::launch::async, &remlog::client::curl::log, std::ref(this->curl_client),
	                  url.get(),
	                  message.get()
	);
}