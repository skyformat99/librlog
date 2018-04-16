//
// Created by giuseppe on 15/04/18.
//

#include <response.hpp>

remlog::response::response(const std::string &&response, const CURLcode code) :
		server_response(response), code(code) {};

const CURLcode remlog::response::get_code() const noexcept {
	return this->code;
}
const std::string remlog::response::get_server_response() const noexcept {
	return this->server_response;
}