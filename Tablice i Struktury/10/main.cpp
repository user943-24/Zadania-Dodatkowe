#include <exception>
#include <iostream>
#include <array>
#include <sstream>

enum types {
    a, b, c, d
};

std::array<int, 10> type_a(int n, int t) {
    std::array<int, 10> ret_arr;
    ret_arr.fill(0);
    for(int i = 0; i < n; ++i) {
        ret_arr.at(i) = t+1+i;
    }
    return ret_arr;
}

std::array<int, 10> type_b(int n, int t) {
    std::array<int, 10> ret_arr;
    ret_arr.fill(0);
    for(int i = n-(t+1); i < n; ++i) {
        ret_arr.at(i) = 1+(i-(n-(t+1)));
    }
    return ret_arr;
}

std::array<int, 10> type_d(int n, int t) {
    std::array<int, 10> ret_arr;
    ret_arr.fill(0);
    for(int i = 0; i < n; ++i) {
        ret_arr.at(i) = (n-i-t >= 0) ? n-i-t : 0;
    }
    return ret_arr;
}

int str_to_number(std::string const &s) {
    for(auto const &el : s) {
        if(!std::isdigit(el)) {
            throw "Nieprawidłowa liczba";
        }
    }
    std::istringstream iss(s);
    int x;
    iss >> x;
    return x;
}

int main() {
    std::array<std::array<int, 10>, 10> arr;
    for(auto &el : arr) {
        el.fill(0);
    }
    std::string type;
    std::string tmp;
    int value;
    std::cout << "Podaj wariant macierzy (a, b, c, d):\n> ";
    std::cin >> type;
    std::cout << "Podaj rozmiar macierzy (1-10)\n> ";
    std::cin >> tmp;
    try {
        value = str_to_number(tmp);
    } catch(const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    if(type == "a") {
        for(int i = 0; i < value; ++i) {
            arr.at(i) = type_a(value, i);
        }
    } else if(type == "b") {
        for(int i = 0; i < value; ++i) {
            arr.at(i) = type_b(value, i);
        }
    } else if(type == "d") {
        for(int i = 0; i < value; ++i) {
            arr.at(i) = type_d(value, i);
        }
    }

    for(int i = 0; i < value; ++i) {
        for(int j = 0; j < value; ++j) {
            std::cout << arr.at(i).at(j) << " ";
        }
        std::cout << '\n';
    }
}