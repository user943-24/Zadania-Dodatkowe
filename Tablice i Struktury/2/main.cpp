#include <iostream>
#include <set>
#include <random>
#include <sys/types.h>
#include <functional>
#include <sstream>

u_int16_t str_to_number(std::string s) {
    std::locale loc;
    for(u_int16_t i = 0; i < s.size(); i++) {
        if(!std::isdigit(s[i], loc)) {
            throw "Not a number!";
        }
    }
    std::istringstream iss(s);
    u_int16_t x;
    iss >> x;
    return x;
}

int main(int argc, char *argv[]) {
    if(argc > 12) {
        std::cout << "Za dużo podanych liczb\n";
        exit(1);
    }

    std::set<u_int16_t> numbers;
    for(u_int16_t i = 1; i < argc; ++i) {
        std::string tmp = argv[i];
        u_int16_t tmp_number;
        try {
            tmp_number = str_to_number(tmp);
            if(tmp_number < 0 || tmp_number > 10) {
                throw("number out of range");
            }
        } catch(const char *msg) {
            std::cerr << "Błędne dane\n";
            exit(1);
        }
        if(numbers.count(tmp_number) == 1) {
            std::cout << "Podane liczby nie mogą się powtarzać\n";
            exit(1);
        }
        numbers.insert(tmp_number);
    }

    std::set<u_int16_t> rnd_numbers;
    std::mt19937 engine;
    std::uniform_int_distribution<u_int16_t> distribution(1, 10);
    engine.seed(std::random_device{}());
    auto roll = std::bind(distribution, engine);

    for(;;) {
        if(rnd_numbers.size() == numbers.size())
            break;
        u_int64_t tmp = roll();
        rnd_numbers.insert(tmp);
        engine.seed(std::random_device{}());

    }
    std::cout << "Wylosowane liczby to ";
    for(std::set<u_int16_t>::iterator rnd_it=rnd_numbers.begin();
        rnd_it != rnd_numbers.end(); ++rnd_it) {
        std::cout << *rnd_it << " ";
    }
    std::cout << "\n";
    int counter = 1;
    for(std::set<u_int16_t>::iterator it=numbers.begin(); it !=numbers.end(); ++it) {
        if(rnd_numbers.count(*it) == 1) {
            counter++;
        }
    }
    std::cout << "Trafiłeś " << counter << " z " << numbers.size() << "\n";
}
