//
// Created by Giuseppe Persico on 12/04/2018.
//

#include "../include/option.hpp"

rlog::options::options(const std::string &url, const std::string &log_name) {
    this->set_url(url);
    this->set_log_name(log_name);
}

void rlog::options::set_url(const std::string &url) {
    if (url.empty()) {
        throw std::runtime_error("The URL length can not be zero!");
    }
    this->url = url;
}

void rlog::options::set_log_name(const std::string &log_name) {
    if (log_name.empty()) {
        throw std::runtime_error("The log name length can not be zero!");
    }
    this->log_name = log_name;
}

std::string rlog::options::get_url() const noexcept {
    return this->url;
}

std::string rlog::options::get_log_name() const noexcept {
    return this->log_name;
}