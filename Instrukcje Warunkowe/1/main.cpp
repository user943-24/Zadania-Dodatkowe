#include <iostream>
#include <sys/types.h>
#include <sstream>

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

int main() {
    int32_t x;
    std::cout << "Podaj number tygodnia (1-7): ";
    std::string tmp;
    std::cin >> tmp;
    try {
        x = str_to_number(tmp);
    } catch(const char *msg) {
        std::cerr << "Nieprawidłowa liczba\n";
        exit(1);
    }
    std::istringstream iss(tmp);
    iss >> x;
    switch(x) {
        case 1:
            std::cout << "Poniedziałek\n";
            break;
        case 2:
            std::cout << "Wtorek\n";
            break;
        case 3:
            std::cout << "Środa\n";
            break;
        case 4:
            std::cout << "Czwartek\n";
            break;
        case 5:
            std::cout << "Piątek\n";
            break;
        case 6:
            std::cout << "Sobota\n";
            break;
        case 7:
            std::cout << "Niedziela\n";
            break;
        default:
            std::cout << "Nieprawidłowa liczba\n";
    }
}
