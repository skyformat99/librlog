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
    protected:
        class curl_client {
        private:
            std::once_flag global_init_flag;
            CURL *handle;
            void init();
        public:
            curl_client();
            ~curl_client() noexcept;
            void log(const char *, const char *);
        };
    public:
        virtual ~client() = default;
        virtual void log(const std::string &, remlog::message::stream &);
    };

    class async_client : public client {
    public:
        async_client() : client() {}
        ~async_client() override = default;
        void log(const std::string &, remlog::message::stream &) override;
    };
}

#endif //RLOG_LOGGER_HPP
