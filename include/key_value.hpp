//
// Created by Giuseppe Persico on 13/04/2018.
//

#ifndef RLOG_KEY_HPP
#define RLOG_KEY_HPP

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
            void set_key(std::string &);
            void set_value(T &);
            std::string escape(std::string &);
        public:
            explicit key_value(std::string &, T &);
            explicit key_value(std::string, T &);
            explicit key_value(std::string &, T);
            explicit key_value(const char *, T &);
            explicit key_value(const char *, T);
            std::string get_pair() const noexcept;
            friend std::ostream &operator<<(std::ostream &stream, const remlog::message::key_value<T> &kvp) {
                stream << "&" << kvp.get_pair();
                return stream;
            }
        };

        template<class T>
        remlog::message::key_value<T>::key_value(std::string &key, T &value) {
            this->set_key(key);
            this->set_value(value);
        }

        template<class T>
        remlog::message::key_value<T>::key_value(std::string key, T &value) {
            this->set_key(key);
            this->set_value(value);
        }

        template<class T>
        remlog::message::key_value<T>::key_value(std::string &key, T value) {
            this->set_key(key);
            this->set_value(value);
        }

        template<class T>
        remlog::message::key_value<T>::key_value(const char *key, T &value) {
            std::string tmp(key);
            this->set_key(tmp);
            this->set_value(value);
        }

        template<class T>
        remlog::message::key_value<T>::key_value(const char *key, T value) {
            std::string tmp(key);
            this->set_key(tmp);
            this->set_value(value);
        }

        template<class T>
        std::string remlog::message::key_value<T>::get_pair() const noexcept {
            return this->key + "=" + this->value;
        }

        template<class T>
        void remlog::message::key_value<T>::set_key(std::string &key) {
            key.erase(std::remove(key.begin(), key.end(), ' '), key.end());
            this->key = key;
        }

        template<class T>
        void remlog::message::key_value<T>::set_value(T &value) {
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
