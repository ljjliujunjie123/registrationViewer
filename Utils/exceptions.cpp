//
// Created by ZZY on 2021/11/30.
//

#include<exception>

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
