#include "option.hpp"
#include "client.hpp"
#include "../include/stream.hpp"

#include <iostream>
#include <cstdlib>

int main(int argc, char **argv) {
    rlog::message::stream message_builder;


    message_builder << rlog::message::stream::key("message");


    std::cout<<message_builder.get_content()<<std::endl;

    rlog::client client;

    rlog::options options("http://localhost:8080/test", "log");
    client.log_message(options, message_builder);

    exit(EXIT_SUCCESS);
}