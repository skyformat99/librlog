//
// Created by Giuseppe Persico on 12/04/2018.
//

#ifndef RLOG_LOGGER_HPP
#define RLOG_LOGGER_HPP

#include <mutex>
#include <future>

#include "stream.hpp"
#include "url.hpp"

namespace {
	using write_callback_ptr_type = size_t(*)(void *,size_t,size_t,void *);

	size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
		const size_t realsize = size * nmemb;
		auto const stream = static_cast<std::stringstream *>(userp);
		stream->write(static_cast<const char *>(contents), realsize);
		return realsize;
	}
}

namespace remlog {

    class client {
    public:
	    using result = std::pair<CURLcode, std::unique_ptr<std::stringstream>>;
	    virtual ~client() = default;
        client::result log(remlog::url &, remlog::message::stream &);
        std::future<client::result> async_log(remlog::url &, remlog::message::stream &);
    private:
	    class curl {
	    private:
		    std::once_flag global_init;
		    void init();
	    public:
		    curl();
		    ~curl() noexcept;
		    client::result log(std::string, std::string);
	    };
	    remlog::client::curl curl_client;
    };
}

#endif //RLOG_LOGGER_HPP
