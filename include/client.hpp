//
// Created by Giuseppe Persico on 12/04/2018.
//

#ifndef RLOG_LOGGER_HPP
#define RLOG_LOGGER_HPP

#include <mutex>
#include <future>

#include "../include/json.hpp"
#include "../include/stream.hpp"

namespace remlog {

    class client {
    private:
        class curl_client {
        private:
            std::once_flag global_init;
            void init();
        public:
            curl_client();
            ~curl_client() noexcept;
            CURLcode log(std::string, std::string);
        };
        remlog::client::curl_client libcurl_client;
    protected:
        CURLcode _log_util(std::string &, remlog::message::stream &);
        std::future<CURLcode> _async_log_util(std::string, remlog::message::stream &);
    public:
        virtual ~client() = default;
        CURLcode log(std::string &, remlog::message::stream &);
        CURLcode log(const char *, remlog::message::stream &);
        std::future<CURLcode> async_log(std::string &, remlog::message::stream &);
        std::future<CURLcode> async_log(const char *, remlog::message::stream &);
    };
}

#endif //RLOG_LOGGER_HPP
