#include <iostream>
#include <string>
#include <map>
#include <string>
#include <vector>

bool str_to_number(std::string s) {
    std::locale loc;
    for(u_int16_t i = 0; i < s.size(); i++) {
        if(!std::isdigit(s[i], loc)) {
            return false;
        }
    }
    return true;
}

struct Contact {
    std::string phone_number;
    std::string username;
    uint32_t call_counter;
    Contact(std::string pn, std::string un) {
        phone_number = pn;
        username = un;
        call_counter = 0;
    }
    Contact();
    bool operator==(Contact& c) {
        return (this->phone_number == c.phone_number);
    }
};

struct HashContact {
    std::string operator()(Contact& c) {
        return c.phone_number;
    }
};

bool find(std::vector<Contact> pb, std::string pn) {
    for(auto const el : pb) {
        if(el.phone_number == pn) {
            return true;
        }
    }
    return false;
}

void insert(std::vector<Contact> *pb, std::string pn, std::string un) {
    if(find((*pb), pn)) {
        std::cout << "Number already exists!\n";
        throw "Invalid number\n";
    }
    if(str_to_number(pn)) {
        Contact tmp(pn, un);
        (*pb).push_back(tmp);
    } else {
        throw "Invalid number\n";
    }
}

void show(std::vector<Contact> pb) {
    for(auto const el : pb) {
        std::cout << "[" << el.phone_number << ", " <<
            el.username << ", call counter: " << el.call_counter << "]\n";
    }
}

void search(std::vector<Contact> *pn, std::string s) {
    for(auto const el : *pn) {
        if(el.phone_number == s) {
            std::cout << "[" << el.phone_number << ", " <<
                el.username << ", call counter: " << el.call_counter << "]\n";
            return;
        }
    }
    std::cout << "There's no such number in the phonebook\n";
}


void remove(std::vector<Contact> *pb, std::string s) {
    if(!find((*pb), s)) {
        throw "Number doesn't exist";
    }
    std::vector<Contact>::iterator it = (*pb).begin();
    for(auto &el : *pb) {
        if(el.phone_number == s) {
            (*pb).erase(it);
        }
        it++;
    }
}

void call(std::vector<Contact> *pb, std::string us) {
    for(auto &el : *pb) {
        if(el.username == us) {
            el.call_counter++;
            return;
        }
    }
    throw "No contact with such username";
}

int main() {
    std::vector<Contact> phonebook;
    for(;;) {
        std::cout << "1 - Show Phonebook\n"
            "2 - Find number\n"
            "3 - Insert number\n"
            "4 - Remove number\n"
            "5 - Call\n"
            "0 - Exit\n"
            "> ";
        std::string tmp;
        std::string tmp2;
        std::getline(std::cin, tmp);
        if(!str_to_number(tmp)) {
            std::cout << "Invalid input\n\n";
            continue;
        }
        uint32_t x = std::stoi(tmp);
        switch(x) {
            case 1:
                show(phonebook);
                break;
            case 2:
                std::cout << "Number to search: ";
                std::getline(std::cin, tmp);
                search(&phonebook, tmp);
                break;
            case 3:
                std::cout << "Number and username to insert: ";
                std::getline(std::cin, tmp);
                std::getline(std::cin, tmp2);
                try {
                    insert(&phonebook, tmp, tmp2);
                } catch(const char *msg) {
                    std::cerr << msg << "\n";
                    continue;
                }
                break;
            case 4:
                std::cout << "Number to remove: ";
                std::getline(std::cin, tmp);
                try {
                    remove(&phonebook, tmp);
                } catch(const char *msg) {
                    std::cerr << msg << "\n";
                    continue;
                }
                break;
            case 5:
                std::cout << "Username to call: ";
                std::getline(std::cin, tmp);
                try {
                    call(&phonebook, tmp);
                } catch(const char *msg) {
                    std::cerr << msg << "\n";
                    continue;
                }
                break;
            case 0:
                exit(0);
                break;
            default:
                std::cout << "Invalid Choice\n";
                continue;
        }
    }
}
