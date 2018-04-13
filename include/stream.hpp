//
// Created by Giuseppe Persico on 12/04/2018.
//

#ifndef RLOG_MESSAGE_HPP
#define RLOG_MESSAGE_HPP

#include <string>
#include <sstream>

#include "../include/message.hpp"

namespace rlog {
    namespace message {

        class stream {
        private:
            std::stringstream message_stream;
        public:
            stream() = default;
            std::string get_content() const noexcept;
            std::ostream &operator<<(const rlog::message::kvp &);
        };
    }
}

#endif //RLOG_MESSAGE_HPP
