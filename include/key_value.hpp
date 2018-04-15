//
// Created by Giuseppe Persico on 13/04/2018.
//

#ifndef RLOG_KEY_HPP
#define RLOG_KEY_HPP

#include <iostream>
#include <string>
#include <ostream>
#include <sstream>
#include <algorithm>
#include <curl/curl.h>

namespace remlog {
    namespace message {

        template<class T>
        class key_value {
        private:
            std::string key;
            std::string value;
        protected:
            void set_key(const std::string &);
            void set_value(const T &);
            std::string escape(std::string &);
        public:
	        explicit key_value(const std::string &, const T &);
	        explicit key_value(const std::string &&, const T &);
	        explicit key_value(const std::string &, const T &&);
	        explicit key_value(const std::string &&, const T &&);
	        std::string get() const noexcept;

            friend std::ostream &operator<<(std::ostream &stream, const remlog::message::key_value<T> &kvp) {
                stream << "&" << kvp.get();
                return stream;
            }
        };

        template<class T>
        remlog::message::key_value<T>::key_value(const std::string &key, const T &value) {
            this->set_key(key);
            this->set_value(value);
        }

	    template<class T>
	    remlog::message::key_value<T>::key_value(const std::string &&key, const T &value) {
        	this->set_key(key);
		    this->set_value(value);
	    }

	    template<class T>
	    remlog::message::key_value<T>::key_value(const std::string &key, const T &&value) {
		    this->set_key(key);
		    this->set_value(value);
	    }

	    template<class T>
	    remlog::message::key_value<T>::key_value(const std::string &&key, const T &&value) {
		    this->set_key(key);
		    this->set_value(value);
	    }

        template<class T>
        std::string remlog::message::key_value<T>::get() const noexcept {
            return this->key + "=" + this->value;
        }

        template<class T>
        void remlog::message::key_value<T>::set_key(const std::string &key) {
        	std::string _key(key);
        	auto key_end = _key.end();
	        _key.erase(std::remove(_key.begin(), key_end, ' '), key_end);
	        this->key = key;
        }

        template<class T>
        void remlog::message::key_value<T>::set_value(const T &value) {
            std::stringstream ss;
            ss << value;
            std::string temp_value(std::move(ss.str()));
            this->value = this->escape(temp_value);
        }

        template<class T>
        std::string remlog::message::key_value<T>::escape(std::string &val) {
            char *escaped_content = curl_easy_escape(nullptr, val.c_str(), 0);
            if (escaped_content == nullptr) {
                throw std::runtime_error("Attempt to write a null pointer into message stream!");
            }
            std::string escaped_string(escaped_content);
            curl_free(escaped_content);
            return escaped_string;
        }
    }
}

#endif //RLOG_KEY_HPP
