#include <iostream>
#include <sys/types.h>
#include <sstream>
#include <utility>
#include <cmath>

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

std::pair<bool, u_int32_t> prime_number(u_int32_t a) {
    double b = (double)a;
    b = sqrt(b);
    if(a == 2 || a == 3)
        return std::make_pair(true, 0);
    if(a == 0 || a == 1 || a%2 == 0)
        return std::make_pair(false, 0);
    u_int32_t i = 3;
    u_int32_t loops = 0;
    while(i < b) {
        loops++;
        if(a%i == 0)
            return std::make_pair(false, loops);
        i += 2;
    }
    return std::make_pair(true, loops);
}

int main() {
    u_int32_t prime;
    std::cout << "Podaj liczbe: ";
    std::string tmp;
    std::cin >> tmp;
    u_int32_t loops = tmp.size();
    try {
        prime = str_to_number(tmp);
    } catch(const char *msg) {
        std::cerr << "Nieprawidłowa liczba\n";
        exit(1);
    }
    auto answer = prime_number(prime);
    if(answer.first)
        std::cout << "Liczba pierwsza\n";
    else {
        std::cout << "Liczba nie jest pierwsza\n";
    }
    std::cout << "Program wykonał " << loops+answer.second << " iteracji pętli\n";
    std::cout << loops <<
        " iteracji było wymaganych do sprawdzenia poprawności wprowadzonych danych\n";
    std::cout << answer.second <<
        " iteracji było wymaganych do sprawdzenia czy liczba jest pierwsza\n";
}
