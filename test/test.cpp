#include "rlog/client.hpp"
#include "rlog/stream.hpp"
#include "rlog/key_value.hpp"

#include <iostream>
#include <cstdlib>
#include <thread>
#include <vector>
#include <array>
#include <chrono>

std::vector<std::future<remlog::response>> futures;
std::mutex mutex;

class person {
private:
	std::string name;
	std::string surname;
public:
	explicit person(const std::string &name, const std::string &surname) {
		this->name = name;
		this->surname = surname;
	};
	friend std::ostream &operator<<(std::ostream &stream, const person &obj) {
		stream << obj.name << " " << obj.surname;
		return stream;
	}
};


void function(const remlog::url &url) {

    remlog::message::stream message_stream_builder;

    auto tid = std::this_thread::get_id();
    std::string key = "request_id";

    person x("giuseppe", "persico");

    remlog::message::key_value<std::thread::id> tid_msg(key, tid);
    remlog::message::key_value<std::string> hello_message("message", "Hello world!");
    remlog::message::key_value<std::string> log_name("log_name", "application.log");
    remlog::message::key_value<person> class_object("person_class", x);

    message_stream_builder << tid_msg << hello_message << log_name << class_object;

    remlog::client client;
    auto result = client.async_log(url, message_stream_builder);

    mutex.lock();
    futures.push_back(std::move(result));
	std::cout<<"URL: "<<url.get()<<" MESSAGE: "<< message_stream_builder.get()<<std::endl;
	mutex.unlock();
}

int main(int argc, char **argv) {
    const int n = 10;
    std::array<std::thread, n> pool;
    remlog::url url("http://localhost:8080/test");

    for (auto &worker : pool) {
    	worker = std::move(std::thread(function, url));
    	std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    for (auto &worker : pool) {
    	worker.join();
    }

    for (int i = 0; i < n; ++i) {
    	std::cout<< futures[i].get().get_response() << std::endl;
    }

    exit(EXIT_SUCCESS);
}