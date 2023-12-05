#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <exception>
#include <stdexcept>
#include <string>


class BaseException : public std::exception {
protected:
    const std::string msg_;
public:
    BaseException(const std::string& msg) : msg_(msg) {
    }
    const char* what() const noexcept {
        return msg_.c_str();
    }
};


class TypeError : public BaseException {
public:
    const static std::string info_;
    TypeError(const std::string& msg) : BaseException(msg) { };
};


class NotFound : public BaseException {
public:
    const static std::string info_;
    NotFound(const std::string& msg) : BaseException(msg) { };
};


class SyntaxError : public BaseException {
public:
    const static std::string info_;
    SyntaxError(const std::string& msg) : BaseException(msg) { };
};

class ValueError : public BaseException {
public:
    const static std::string info_;
    ValueError(const std::string& msg) : BaseException(msg) { };
};

class OutOfRange : public BaseException {
public:
    const static std::string info_;
    OutOfRange(const std::string& msg) : BaseException(msg) { };
};

class DivisionByZero : public BaseException {
public:
    const static std::string info_;
    DivisionByZero(const std::string& msg) : BaseException(msg) { };
};

#endif
