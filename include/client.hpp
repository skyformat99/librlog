//
// Created by Giuseppe Persico on 12/04/2018.
//

#ifndef RLOG_LOGGER_HPP
#define RLOG_LOGGER_HPP

#include <mutex>
#include <future>

#include "stream.hpp"
#include "url.hpp"
#include "response.hpp"

namespace {
	using write_callback_ptr_type = size_t(*)(void *,size_t,size_t,void *);

	template<class T>
	size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
		const size_t realsize = size * nmemb;
		auto const stream = static_cast<T *>(userp);
		stream->write(static_cast<const char *>(contents), realsize);
		return realsize;
	}
}

namespace remlog {


    class client {
    private:
	    class curl {
	    private:
		    std::once_flag global_init;
		    void init();
	    public:
		    curl();
		    ~curl() noexcept;
		    remlog::response log(std::string, std::string);
	    };

	    remlog::client::curl curl_client;
    public:
	    ~client() = default;
        remlog::response log(const remlog::url &, const remlog::message::stream &);
	    std::future<remlog::response> async_log(const remlog::url &, const remlog::message::stream &);
    };
}

#endif //RLOG_LOGGER_HPP
