//
// Created by Giuseppe Persico on 12/04/2018.
//

#include "../include/stream.hpp"

std::string remlog::message::stream::get() const noexcept {
    return this->message_stream.str();
}