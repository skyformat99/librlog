#include <stdexcept>

#include "url.hpp"


void rlog::url::set_url(const std::string &url) {
	if (url.empty()) {
		throw std::runtime_error("Invalid remote url specified!");
	}
	this->_url = url;
}

rlog::url::url(const char *url) {
	std::string str_url(url);
	this->set_url(str_url);
}

rlog::url::url(const std::string &url) {
	this->set_url(url);
}

std::string rlog::url::get() const noexcept {
	return this->_url;
}

