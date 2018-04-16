//
// Created by giuseppe on 15/04/18.
// This example shows how to log an event asynchronously.
//

#include "rlog/client.hpp"
#include "rlog/stream.hpp"
#include "rlog/key_value.hpp"

#include <iostream>

int main(int argc, char **argv) {

	// Create a stream builder.
	remlog::message::stream message_stream_builder;

	// The stream accepts a key-value pair, where you can specify a key and its value.
	message_stream_builder << remlog::message::key_value<std::string>("message", "Hello world!");

	// Istantiate the client and the remote url
	remlog::client client;
	remlog::url url("http://localhost:8080/test");

	// Now simply log the event using the async_log method. This method returns a std::future object.
	std::future<remlog::response> future_response = client.async_log(url, message_stream_builder);

	// Do whatever you have to here ... computations and stuff ...

	// At certain point you call the future get method, that will return the response.
	remlog::response response = future_response.get();

	// Print the server response code and the entire response.
	std::cout << "CODE: " << response.get_code() << std::endl <<
			  " RESPONSE: " << response.get_response() << std::endl;

    return 0;
}
