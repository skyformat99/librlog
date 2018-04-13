#include "option.hpp"
#include "client.hpp"
#include "stream.hpp"
#include "message.hpp"

#include <iostream>
#include <cstdlib>

int main(int argc, char **argv) {
    rlog::message::stream message_stream_builder;
    message_stream_builder << rlog::message::kvp("message","Hello World!") << rlog::message::kvp::another_one;

    std::cout<<message_stream_builder.get_content()<<std::endl;

    rlog::client client;
    rlog::options options("http://localhost:8080/test", "log");
    client.log_message(options, message_stream_builder);

    exit(EXIT_SUCCESS);
}