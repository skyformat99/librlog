#include "client.hpp"
#include "stream.hpp"
#include "key_value.hpp"

#include <iostream>
#include <cstdlib>
#include <thread>
#include <sstream>
#include <chrono>

void function() {

    remlog::message::stream message_stream_builder;

    remlog::message::key_value<std::__thread_id> tid_msg("request_id", std::this_thread::get_id());
    remlog::message::key_value<std::string> hello_message("message", "Hello world!");
    remlog::message::key_value<std::string> log_name("log_name", "application.log");

    message_stream_builder << tid_msg << hello_message << log_name;

    remlog::client as_client;
    as_client.log("http://localhost:8080/test", message_stream_builder);
}

int main(int argc, char **argv) {
    const int n = 1;
    std::array<std::thread, n> pool;
    for (int i = 0; i < n; ++i) {
        pool[i] = std::move(std::thread(function));
    }
    for (int i = 0; i < n; ++i) {
        pool[i].join();
    }
    exit(EXIT_SUCCESS);
}