#include <iostream>
#include <set>
#include <cctype>
#include <string>
#include <sstream>

std::string to_lower_case(std::string s) {
    std::string tmp{0};
    for(auto element : s) {
        tmp.push_back(tolower(element));
    }
    return tmp;
}

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

struct dictionary {
    std::set<std::string> words;
    void menu() {
        while(true) {
            std::cout << "1 - Add Word\n"
                "2 - Remove Word\n"
                "3 - Find Word\n"
                "4 - Show Contents\n"
                "0 - Exit\n";
            uint16_t x;
            std::string tmp;
            std::cin >> tmp;
            try {
                x = str_to_number(tmp);
            } catch(const char* msg) {
                std::cout << "Not a valid number\n";
                continue;
            }
            switch(x) {
                case 1:
                    std::cout << "Word to insert: ";
                    std::cin >> tmp;
                    insert_word(to_lower_case(tmp));
                    break;
                case 2:
                    std::cout << "Word to remove: ";
                    std::cin >> tmp;
                    remove_word(to_lower_case(tmp));
                    break;
                case 3:
                    std::cout << "Word to find: ";
                    std::cin >> tmp;
                    if(find_word(to_lower_case(tmp))) {
                        std::cout << "Word exist in the dictionary\n";
                    } else {
                        std::cout << "There is no such word in the dictionary\n";
                    }
                    break;
                case 4:
                    show();
                    break;
                case 0:
                    exit(0);
                default:
                    std::cout << "Invalid choice\n";
                    continue;
            }
        }
    }
    void insert_word(std::string s) {
        if(words.count(s) == 1) {
            std::cout << "Word already exist in the dictionary\n";
            return;
        }
        words.insert(s);
    }
    void remove_word(std::string s) {
        if(words.count(s) == 0) {
            std::cout << "There's no such word in the dictionary\n";
            return;
        } else {
            words.erase(s);
        }
    }
    bool find_word(std::string s) {
        return words.count(s) == 1;
    }
    void show() {
        std::set<std::string>::iterator it = words.begin();
        for(; it != words.end(); ++it) {
            std::cout << "[" << *it << "]\n";
        }
    }
};

int main() {
    auto dict = dictionary{};
    dict.menu();
}
