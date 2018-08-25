#include "stream.hpp"


std::string rlog::message::stream::get() const noexcept {
    return this->message_stream.str();
}