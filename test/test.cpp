#include "client.hpp"
#include "stream.hpp"
#include "kvp.hpp"

#include <iostream>
#include <cstdlib>
#include <thread>
#include <sstream>
#include <chrono>

void function() {
    std::stringstream tid_stream;
    tid_stream << std::this_thread::get_id();
    std::string tid_string = tid_stream.str();
    std::string message("Hello from " + tid_string);

    remlog::message::stream message_stream_builder;

    message_stream_builder
            << remlog::message::kvp("req_id", tid_string)
            << remlog::message::kvp("message", message)
            << remlog::message::kvp("log_name", "mylog");

    remlog::client client;
    client.log("http://localhost:8080/test", message_stream_builder);
}

int main(int argc, char **argv) {
    std::array<std::thread, 2> pool;
    for (int i = 0; i < 2; ++i) {
        pool[i] = std::move(std::thread(function));
    }
    for (int i = 0; i < 2; ++i) {
        pool[i].join();
    }
    exit(EXIT_SUCCESS);
}