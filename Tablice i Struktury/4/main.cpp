#include <cstdint>
#include <iostream>
#include <array>
#include <sstream>

uint32_t str_to_number(std::string s) {
    std::locale loc;
    for(uint32_t i = 0; i < s.size(); i++) {
        if(!std::isdigit(s[i], loc)) {
            throw "Not a number!";
        }
    }
    std::istringstream iss(s);
    uint32_t x;
    iss >> x;
    return x;
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        std::cerr << "Nieprawidłowa ilość argumentów\n";
        exit(1);
    }
    uint32_t h;
    try {
        h = str_to_number(argv[1]);
    } catch(const char* msg) {
        std::cerr << "Nieprawidłowy argument\n";
        exit(1);
    }
    std::array<uint32_t, 10000> pascal{0};
    uint32_t current=0;
    for(uint32_t i=0; i < h; ++i) {
        for(uint32_t j=0; j < i+1; ++j) {
            if(j == 0 || j == i) {
                std::cout << "1 ";
                pascal[current] = 1;
            } else {
                pascal[current] = pascal[current-i-1] + pascal[current-i];
                std::cout << pascal[current] << " ";
            }
            current++;
        }
        std::cout << "\n";
    }
}
