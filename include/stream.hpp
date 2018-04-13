//
// Created by Giuseppe Persico on 12/04/2018.
//

#ifndef RLOG_MESSAGE_HPP
#define RLOG_MESSAGE_HPP

#include <string>
#include <sstream>
#include <utility>

namespace rlog {
    namespace message {

        class stream {
        private:
            std::stringstream message_stream;
        protected:
            static std::string escape(const std::string &);
        public:

            class key {
            private:
                const std::string _key;
            public:
                friend std::string rlog::message::stream::escape(const std::string &);

                explicit key(std::string key) : _key(std::move(key)) {};
                std::string get() const {
                    return this->_key;
                }
            };

            stream() = default;
            std::string get_content() const noexcept;
            std::ostream &operator<<(const rlog::message::stream::key &key) {
                this->message_stream << key.get();
                return this->message_stream;
            }
        };
    }
}

#endif //RLOG_MESSAGE_HPP
