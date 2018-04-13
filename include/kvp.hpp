//
// Created by Giuseppe Persico on 13/04/2018.
//

#ifndef RLOG_KEY_HPP
#define RLOG_KEY_HPP

#include <string>
#include <ostream>

namespace remlog {
    namespace message {

        class kvp {
        private:
            std::string key;
            std::string value;
        protected:
            void set_key(std::string &) noexcept;
            void set_key(const char *) noexcept;
            void set_value(std::string &) noexcept;
            void set_value(const char *) noexcept;
            std::string escape(std::string &);
        public:
            explicit kvp(std::string &, std::string &) noexcept;
            explicit kvp(const char *, const char *) noexcept;
            explicit kvp(std::string &, const char *) noexcept;
            explicit kvp(const char *, std::string &) noexcept;
            std::string get_pair() const noexcept;

            friend std::ostream &operator<<(std::ostream &stream, const remlog::message::kvp &kvp) {
                stream << "&" << kvp.get_pair();
                return stream;
            }

        };
    }
}

#endif //RLOG_KEY_HPP
