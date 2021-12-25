//
// Created by ZZY on 2021/12/25.
//
#include "strings.h"

bool startsWith(const std::string &s, std::string prefix) {
    return s.rfind(prefix, 0) == 0;
}
