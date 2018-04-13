#include "option.hpp"
#include "client.hpp"
#include "stream.hpp"
#include "kvp.hpp"

#include <iostream>
#include <cstdlib>
#include <thread>
#include <sstream>

void function() {
    auto myid = std::this_thread::get_id();
    std::stringstream ss;
    ss << myid;
    std::string tid = ss.str();
    std::string msg = "message";

    rlog::message::stream message_stream_builder;
    message_stream_builder << rlog::message::kvp(msg, tid);

    rlog::client client;
    rlog::options options("http://localhost:8080/test", "log");

    client.log_message(options, message_stream_builder);

}

int main(int argc, char **argv) {

    rlog::client client;
    rlog::options options("http://localhost:8080/test", "log");

    std::array<std::thread, 50> pool;

    for (int i = 0; i < 50; ++i) {
        pool[i] = std::move(std::thread(function));
    }

    for (int i = 0; i < 50; ++i) {
        pool[i].join();
    }

    exit(EXIT_SUCCESS);
}