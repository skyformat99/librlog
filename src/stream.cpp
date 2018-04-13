//
// Created by Giuseppe Persico on 12/04/2018.
//

#include "../include/stream.hpp"

std::string rlog::message::stream::get_content() const noexcept {
    return this->message_stream.str();
}

std::ostream &rlog::message::stream::operator<<(const rlog::message::kvp &kvp) {
    this->message_stream << kvp.get_pair();
    return this->message_stream;
}

