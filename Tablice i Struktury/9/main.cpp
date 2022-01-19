#include <exception>
#include <iostream>
#include <sstream>
#include <map>

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

std::map<int, int> convert_to_nominals(int const &value) {
    std::map<int, int> res;
    int sum = 0;
    auto add_to_sum = [&](int const &v) {
        if(value - sum - v >= 0) {
            res.insert(std::make_pair(v, (value-sum)/v));
            sum += ((value-sum)/v)*v;
        }
    };
    add_to_sum(500);
    add_to_sum(200);
    add_to_sum(100);
    add_to_sum(50);
    add_to_sum(20);
    add_to_sum(10);
    add_to_sum(5);
    add_to_sum(2);
    add_to_sum(1);
    return res;
}

int main() {
    std::string tmp;
    std::cout << "Podaj kwotę w złotych:\n> ";
    std::cin >> tmp;
    int value;
    try {
        value = str_to_number(tmp);
    } catch(const std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    std::cout << "Twoje nominały to:\n";
    auto separated = convert_to_nominals(value);
    for(auto const &el : separated) {
        std::cout << el.first << " - " << el.second << " szt\n";
    }
}