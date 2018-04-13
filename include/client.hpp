//
// Created by Giuseppe Persico on 12/04/2018.
//

#ifndef RLOG_LOGGER_HPP
#define RLOG_LOGGER_HPP

#include <mutex>
#include <curl/curl.h>

#include "../include/option.hpp"
#include "../include/stream.hpp"

namespace rlog {
    class client {
    private:
        std::once_flag curl_once_flag_init;

        void init_libcurl();
        CURL *get_curl_handle();
    public:
        client() noexcept;
        client(const client &) = delete;
        client& operator=(const client &) = delete;
        client(client &&) = delete;
        client& operator=(client &&) = delete;
        ~client() noexcept;

        nlohmann::json log_message(rlog::options &, rlog::message::stream &);
    };
}

#endif //RLOG_LOGGER_HPP
