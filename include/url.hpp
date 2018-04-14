//
// Created by giuseppe on 14/04/18.
//

#ifndef RLOG_URL_HPP
#define RLOG_URL_HPP

#include <string>

namespace remlog {
	class url {
	private:
		std::string _url;
	protected:
		void set_url(const std::string &);
	public:
		explicit url(const std::string &);
		explicit url(const char *);
		url(const url &) = default;
		url(url &&) = default;
		std::string get() const noexcept;
	};
}

#endif //RLOG_URL_HPP
