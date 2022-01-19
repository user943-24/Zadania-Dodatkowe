#include <iostream>
#include <sstream>
#include <sys/types.h>

u_int32_t str_to_number(std::string s) {
    std::locale loc;
    for(u_int32_t i = 0; i < s.size(); i++) {
        if(!std::isdigit(s[i], loc)) {
            throw "Not a number!";
        }
    }
    std::istringstream iss(s);
    u_int32_t x;
    iss >> x;
    return x;
}

std::string christmas_tree(u_int32_t h) {
    std::ostringstream oss;
    u_int32_t w = 1;
    for(u_int32_t i = 0; i < h-2; i++) {
        w += 2;
    }
    for(u_int32_t i = 0; i < w; i++) {
        oss << "*";
    }
    oss << "\n";
    for(u_int32_t i = 0; i < h-2; i++) {
        for(u_int32_t j = 1; j <= w; j++) {
            if(j > w/2-i && j <= w-(w/2)+i)
                oss << " ";
            else
                oss << "*";
        }
        oss << "\n";
    }
    for(u_int32_t i = 0; i < w; i++) {
        oss << "*";
    }
    oss << "\n";
    return oss.str();
}

int main() {
    u_int32_t x;
    std::cout << "Podaj wysokość: ";
    std::string tmp;
    std::cin >> tmp;
    try {
        x = str_to_number(tmp);
    } catch(const char* msg) {
        std::cerr << "Nieprawidłowa liczba\n";
        exit(0);
    }
    std::cout << christmas_tree(x);
}
