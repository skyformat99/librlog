//
// Created by Giuseppe Persico on 12/04/2018.
//

#ifndef RLOG_LOGGER_HPP
#define RLOG_LOGGER_HPP

#include <mutex>
#include <curl/curl.h>

#include "../include/json.hpp"
#include "../include/stream.hpp"

namespace remlog {
    class client {
    private:
        class libcurl {
        private:
            std::once_flag global_init_flag;
            CURL *handle;
            void init();
        public:
            libcurl();
            ~libcurl() noexcept;
            void log(const char *, const char *);
        };
    public:
        nlohmann::json log(const std::string &, remlog::message::stream &);
    };
}

#endif //RLOG_LOGGER_HPP
