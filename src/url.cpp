//
// Created by giuseppe on 14/04/18.
//

#include <stdexcept>
#include "url.hpp"

void remlog::url::set_url(const std::string &url) {
	if (url.empty()) {
		throw std::runtime_error("Invalid remote url specified!");
	}
	this->_url = url;
}

remlog::url::url(const char *url) {
	std::string str_url(url);
	this->set_url(str_url);
}

remlog::url::url(const std::string &url) {
	this->set_url(url);
}

std::string remlog::url::get() const noexcept {
	return this->_url;
}

