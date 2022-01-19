#include <cctype>
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <locale>

int32_t str_to_number(std::string s) {
    std::locale loc;
    bool negative = false;
    for(u_int32_t i = 0; i < s.size(); i++) {
        if(!std::isdigit(s[i], loc)) {
            if(s[i] == '-' && i == 0) {
                negative = true;
            } else {
                throw "Not a number!";
            }
        }
    }
    std::istringstream iss(s);
    int32_t x;
    iss >> x;
    return x;
}

void exit_program() {
    std::cerr << "Nieprawidłowy numer!\n";
    exit(1);
}

int main() {
    int32_t n=0, year=0;
    bool leap = false;
    std::cout << "Podaj numer miesiąca: ";
    std::string tmp;
    std::cin >> tmp;
    try {
        n = str_to_number(tmp);
        if(n <= 0 || n > 12)
            exit_program();
    } catch(const char* msg) {
        exit_program();
    }
    std::cout << "Podaj rok: ";
    std::cin >> tmp;
    try {
        year = str_to_number(tmp);
    } catch(const char* msg) {
        exit_program();
    }
    if(year%4 == 0) {
        leap = true;
    }
    if(n == 2) {
        if(leap)
            std::cout << "29 dni\n";
        else {
            std::cout << "28 dni\n";
        }
    } else if(n == 1 || n == 3 || n == 5 || n == 7 || n == 8 || n == 10 || n == 12)
        std::cout << "31 dni\n";
    else
        std::cout << "30 dni\n";
}
