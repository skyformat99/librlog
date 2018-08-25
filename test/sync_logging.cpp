//
// Created by Giuseppe on 15/04/18.
// This example shows how to log an event synchronously.
//

#include "rlog/client.hpp"
#include "rlog/stream.hpp"
#include "rlog/key_value.hpp"

#include <iostream>


int main(int argc, char **argv) {

	// Create a stream builder.
	rlog::message::stream message_stream_builder;

	// The stream accepts a key-value pair, where you can specify a key and its value.
	message_stream_builder << rlog::message::key_value<std::string>("message", "Hello world!");

	// Istantiate the client and the remote url
	rlog::client client;
	rlog::url url("http://localhost:8080/test");

	// Now simply log the event.
	rlog::response result = client.log(url, message_stream_builder);

	// Print the server response code and the entire response.
	std::cout << "CODE: " << result.get_code() << " RESPONSE: " << result.get_response() << std::endl;
	return 0;
}
