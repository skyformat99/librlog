//
// Created by giuseppe on 15/04/18.
//

#ifndef RLOG_RESULT_HPP
#define RLOG_RESULT_HPP

#include <curl/curl.h>
#include <string>

namespace remlog {
	class response {
	private:
		const std::string _response;
		const CURLcode code;
	public:
		explicit response(const std::string &&, const CURLcode);
		const CURLcode get_code() const noexcept;
		const std::string get_response() const noexcept;
	};
}

#endif //RLOG_RESULT_HPP
