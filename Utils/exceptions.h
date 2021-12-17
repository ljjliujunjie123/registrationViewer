//
// Created by ZZY on 2021/11/30.
//
#ifndef UTILS_EXCEPTIONS_H
#define UTILS_EXCEPTIONS_H

#include<exception>
#include<stdexcept>

class NotFoundException: std::exception{
#ifdef __clang__
    const char *what() const _NOEXCEPT override {
        return "The requested item cannot be found";
    }
#endif
#ifdef _WIN32
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return "The requested item cannot be found";
    }
#endif
};

void checkNull(void* ptr);

#endif