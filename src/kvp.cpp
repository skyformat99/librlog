//
// Created by Giuseppe Persico on 13/04/2018.
//

#include <algorithm>
#include <curl/curl.h>

#include "../include/kvp.hpp"

remlog::message::kvp::kvp(std::string &key, std::string &value) noexcept {
    this->set_key(key);
    this->set_value(value);
}

remlog::message::kvp::kvp(const char *key, const char *value) noexcept {
    this->set_key(key);
    this->set_value(value);
}

remlog::message::kvp::kvp(std::string &key, const char *value) noexcept {
    this->set_key(key);
    this->set_value(value);
}

remlog::message::kvp::kvp(const char *key, std::string &value) noexcept {
    this->set_key(key);
    this->set_value(value);
}

void remlog::message::kvp::set_key(std::string &key) noexcept {
    key.erase(std::remove(key.begin(), key.end(), ' '), key.end());
    this->key = key;
}

void remlog::message::kvp::set_key(const char *key) noexcept {
    std::string string_key(key);
    this->set_key(string_key);
}

void remlog::message::kvp::set_value(std::string &value) noexcept {
    this->value = this->escape(value);
}

void remlog::message::kvp::set_value(const char *value) noexcept {
    std::string string_value(value);
    this->set_value(string_value);
}

std::string remlog::message::kvp::escape(std::string &str) {
    auto escaped_content = curl_easy_escape(nullptr, str.c_str(), 0);
    if (escaped_content == nullptr) {
        throw std::runtime_error("Attempt to write a null pointer into message stream!");
    }
    std::string escaped_string(escaped_content);
    curl_free(escaped_content);
    return escaped_string;
}

std::string remlog::message::kvp::get_pair() const noexcept {
    return this->key + "=" + this->value;
}
