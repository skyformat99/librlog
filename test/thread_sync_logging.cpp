//
// Created by giuseppe on 15/04/18.
// This example shows how to log events synchronously from multiple threads
//

#include "rlog/client.hpp"
#include "rlog/stream.hpp"
#include "rlog/key_value.hpp"

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

// If we want to put every response in a vector, this must be thread safe.
std::mutex mutex;
std::vector<remlog::response> responses;


void first_worker(const remlog::url &url) {
	// Create a stream builder.
	remlog::message::stream message_stream_builder;

	// Create something to write on the stream.
	std::thread::id thread_id = std::this_thread::get_id();
	remlog::message::key_value<std::string> message("message", "This is the first event from the first worker");
	remlog::message::key_value<std::thread::id> request_id("request_id", thread_id);

	// The stream accepts a key-value pair, where you can specify a key and its value.
	message_stream_builder << message << request_id;

	// Istantiate the client. This is thread safe, so you could pass it as parameter.
	remlog::client client;
	remlog::response response = client.log(url, message_stream_builder);

	// Add the response in the global vector.
	mutex.lock();
	responses.emplace_back(response);
	mutex.unlock();
}

void second_worker(const remlog::url &url) {
	// Create a stream builder.
	remlog::message::stream message_stream_builder;

	// Create something to write on the stream.
	std::thread::id thread_id = std::this_thread::get_id();
	remlog::message::key_value<std::string> message("message", "This is the second event from the second worker");
	remlog::message::key_value<std::thread::id> request_id("request_id", thread_id);

	// The stream accepts a key-value pair, where you can specify a key and its value.
	message_stream_builder << message << request_id;

	// Istantiate the client. This is thread safe, so you could pass it as parameter.
	remlog::client client;
	remlog::response response = client.log(url, message_stream_builder);

	// Add the response in the global vector.
	mutex.lock();
	responses.emplace_back(response);
	mutex.unlock();
}

int main(int argc, char **argv) {
	// The url is the same for both threads, but in your application could be different.
	remlog::url url("http://localhost:8080/test");

	// Create the threads and join them.
	std::thread worker_1(first_worker, url);
	std::thread worker_2(second_worker, url);

	worker_1.join();
	worker_2.join();

	for (auto const &response : responses) {
		std::cout << "CODE: " << response.get_code() << " MESSAGE: " << response.get_response() << std::endl;
	}
	return 0;
}
