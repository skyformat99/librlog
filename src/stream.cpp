//
// Created by Giuseppe Persico on 12/04/2018.
//

#include "../include/stream.hpp"

std::string remlog::message::stream::get_content() const noexcept {
    return this->message_stream.str();
}

std::ostream &remlog::message::stream::operator<<(const remlog::message::kvp &kvp) {
    this->message_stream << kvp.get_pair();
    return this->message_stream;
}