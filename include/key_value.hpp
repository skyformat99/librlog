/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 - Giuseppe Persico
 * File - key_value.hpp
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef RLOG_KEY_VALUE_HPP
#define RLOG_KEY_VALUE_HPP

#include <iostream>
#include <string>
#include <ostream>
#include <sstream>
#include <algorithm>
#include <curl/curl.h>


namespace rlog {
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

            friend std::ostream &operator<<(std::ostream &stream, const rlog::message::key_value<T> &kvp) {
                stream << "&" << kvp.get();
                return stream;
            }
        };

        template<class T>
        rlog::message::key_value<T>::key_value(const std::string &key, const T &value) {
            this->set_key(key);
            this->set_value(value);
        }

	    template<class T>
	    rlog::message::key_value<T>::key_value(const std::string &&key, const T &value) {
        	this->set_key(key);
		    this->set_value(value);
	    }

	    template<class T>
	    rlog::message::key_value<T>::key_value(const std::string &key, const T &&value) {
		    this->set_key(key);
		    this->set_value(value);
	    }

	    template<class T>
	    rlog::message::key_value<T>::key_value(const std::string &&key, const T &&value) {
		    this->set_key(key);
		    this->set_value(value);
	    }

        template<class T>
        std::string rlog::message::key_value<T>::get() const noexcept {
            return this->key + "=" + this->value;
        }

        template<class T>
        void rlog::message::key_value<T>::set_key(const std::string &key) {
        	std::string _key(key);
        	auto key_end = _key.end();
	        _key.erase(std::remove(_key.begin(), key_end, ' '), key_end);
	        this->key = key;
        }

        template<class T>
        void rlog::message::key_value<T>::set_value(const T &value) {
            std::stringstream ss;
            ss << value;
            std::string temp_value(std::move(ss.str()));
            this->value = this->escape(temp_value);
        }

        template<class T>
        std::string rlog::message::key_value<T>::escape(std::string &val) {
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

#endif //RLOG_KEY_VALUE_HPP
