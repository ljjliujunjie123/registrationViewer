//
// Created by ZZY on 2021/11/30.
//

#include<exception>

class NotFoundException: std::exception{
    const char *what() const _NOEXCEPT override {
        return "The requested item cannot be found";
    }
};
