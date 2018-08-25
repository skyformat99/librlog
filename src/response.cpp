#include <response.hpp>


rlog::response::response(const std::string &&response, const CURLcode code) :
		server_response(response), code(code) {};

const CURLcode rlog::response::get_code() const noexcept {
	return this->code;
}

const std::string rlog::response::get_server_response() const noexcept {
	return this->server_response;
}