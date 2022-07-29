#ifndef __MISC_HPP__
#define __MISC_HPP__

#include <cstdlib>
#include <cstdio>

#include <string>
#include <vector>

namespace util {

#if defined(DEBUG_MODE)
#define LOG(msg)    printf("[%d.%s] %s\n", __LINE__, __func__, msg)
#else   // DEBUG_MODE
#define LOG(msg)    printf("%s\n", msg)
#endif  // DEBUG_MODE

#define NEWLINE()   printf("\n")

inline std::vector<int> rng_integers(int size, int min=0, int max=RAND_MAX) {
    std::vector<int> buffer;

    for (auto i = 0; i < size; i++) {
        buffer.push_back((rand() % (max - min)) + min);
    }

    return buffer;
}

inline int rng_integer(int min=-(RAND_MAX - 1), int max=RAND_MAX) {
    return ((rand() % (max - min)) + min);
}

inline std::string arr2str(const std::vector<int> &buffer) {
    std::string ret("[");

    for(auto val : buffer) {
        ret += std::to_string(val) + " ";
    }

    if (!buffer.empty()) {
        ret = ret.substr(0, ret.length() - 1);
    }

    return ret + "]";
}

inline std::string arr2str(const std::vector<int> &&buffer) {
    std::string ret("[");

    for(auto val : buffer) {
        ret += std::to_string(val) + " ";
    }

    if (!buffer.empty()) {
        ret = ret.substr(0, ret.length() - 1);
    }

    return ret + "]";
}

}   // namespace util

#endif // __MISC_HPP__
