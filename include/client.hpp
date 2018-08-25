/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 - Giuseppe Persico
 * File - client.hpp
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef RLOG_CLIENT_HPP
#define RLOG_CLIENT_HPP

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

namespace rlog {

    class client {
    private:
	    class curl {
	    private:
		    std::once_flag global_init;
		    void init();
	    public:
		    curl();
		    curl(const curl &) = delete;
            curl& operator=(const curl&) = delete;
		    ~curl() noexcept;
		    rlog::response log(std::string, std::string);
	    };

	    rlog::client::curl curl_client;
    public:
        client() = default;
	    ~client() = default;
	    client(const client &) = delete;
	    client& operator=(const client &) = delete;
        rlog::response log(const rlog::url &, const rlog::message::stream &);
	    std::future<rlog::response> async_log(const rlog::url &, const rlog::message::stream &);
    };
}

#endif //RLOG_CLIENT_HPP
