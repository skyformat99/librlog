//
// Created by Giuseppe Persico on 13/04/2018.
//

#ifndef RLOG_KEY_HPP
#define RLOG_KEY_HPP

#include <string>
#include <ostream>

namespace rlog {
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
            static std::ostream &another_one(std::ostream &);
            explicit kvp(std::string &, std::string &) noexcept;
            explicit kvp(const char *, const char *) noexcept;
            std::string get_pair() const noexcept;
        };
    }
}

#endif //RLOG_KEY_HPP
