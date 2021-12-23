//
// Created by ZZY on 2021/12/17.
//

#include "exceptions.h"

void checkNull(void *ptr) {
    if(ptr == nullptr) throw std::runtime_error("NullPtr retrieving from ControlWrapper");
}
