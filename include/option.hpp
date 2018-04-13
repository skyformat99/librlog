//
// Created by Giuseppe Persico on 12/04/2018.
//

#ifndef RLOG_OPTION_HPP
#define RLOG_OPTION_HPP

#include <string>
#include "../include/json.hpp"

namespace rlog {
    class options {
    private:
        std::string url;
        std::string log_name;
    protected:
        void set_url(const std::string &);
        void set_log_name(const std::string &);
    public:
        explicit options(const std::string &, const std::string &);
        std::string get_url() const noexcept;
        std::string get_log_name() const noexcept;
    };
}

#endif //RLOG_OPTION_HPP
