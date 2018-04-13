//
// Created by Giuseppe Persico on 12/04/2018.
//

#include "stream.hpp"

#include <curl/curl.h>
#include <iostream>

std::string rlog::message::stream::get_content() const noexcept {
    return this->message_stream.str();
}

std::string rlog::message::stream::escape(const std::string &str) {
    auto escaped_content = curl_easy_escape(nullptr, str.c_str(), 0);
    if (escaped_content == nullptr) {
        throw std::runtime_error("Attempt to write a null pointer into message stream!");
    }
    std::string escaped_string(escaped_content);
    curl_free(escaped_content);
    return escaped_string;
}

