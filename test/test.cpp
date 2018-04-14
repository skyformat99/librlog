#include "rlog/client.hpp"
#include "rlog/stream.hpp"
#include "rlog/key_value.hpp"

#include <iostream>
#include <cstdlib>
#include <thread>
#include <vector>

std::vector<std::future<remlog::client::result>> futures;
std::mutex mutex;


void function() {

	remlog::url url("http://httpbin.org/post");
    remlog::message::stream message_stream_builder;

    remlog::message::key_value<std::thread::id> tid_msg("request_id", std::this_thread::get_id());
    remlog::message::key_value<std::string> hello_message("message", "Hello world!");
    remlog::message::key_value<std::string> log_name("log_name", "application.log");

    message_stream_builder << tid_msg << hello_message << log_name;

    remlog::client client;
    auto result = client.async_log(url, message_stream_builder);

    mutex.lock();
    futures.push_back(std::move(result));
    mutex.unlock();

}

int main(int argc, char **argv) {
    const int n = 2;
    std::array<std::thread, n> pool;
    for (int i = 0; i < n; ++i) {
        pool[i] = std::move(std::thread(function));
    }
    for (int i = 0; i < n; ++i) {
        pool[i].join();
    }

    for (int i = 0; i < n; ++i) {
        std::cout<< futures[i].get().second->str()<<std::endl;
    }
    exit(EXIT_SUCCESS);
}