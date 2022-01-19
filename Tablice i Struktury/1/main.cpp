#include <algorithm>
#include <exception>
#include <iostream>
#include <array>
#include <stdexcept>
#include <utility>
#include <sstream>

class Board {
    enum place {
        e = 0,
        x = 1,
        o = 4
    };
//comment
    std::array<std::array<int, 3>, 3> board;

public:

    Board() {
        for(auto &el : board) {
            el.fill(0);
        }
    }

    int won() {
        // Checking rows
        for(auto const &el : board) {
            int sum = 0;
            for(auto const &el_in : el) {
                sum += el_in; 
            }
            if(sum == 3*x) {
                return x;
            } else if(sum == 3*o) {
                return o;
            }
        }

        // Checking columns
        std::array<int, 3> sum_col;
        sum_col.fill(0);
        for(auto const &el : board) {
            for(int i = 0; i < 3; ++i) {
                sum_col.at(i) += el.at(i);
            }
        }
        for(auto const &el : sum_col) {
            if(el == 3*x)
                return x;
            else if(el == 3*o)
                return o;
        }

        // Checking diagonals
        int first_diag = board.at(0).at(0) + board.at(1).at(1) + board.at(2).at(2);
        int second_diag = board.at(0).at(2) + board.at(1).at(1) + board.at(2).at(0);
        if(first_diag == 3*x || second_diag == 3*x)
            return x;
        else if(first_diag == 3*o || second_diag == 3*o)
            return o;

        return e;
    }

    void insert(std::pair<int, int> p, bool isX) {
        if(p.first > 2 || p.second > 2 || p.first < 0 || p.second < 0)
            throw std::out_of_range("Invalid parameters");
        if(board.at(p.first).at(p.second) != e)
            throw std::logic_error("Cell already used"); 

        board.at(p.first).at(p.second) = (isX) ? x : o; 
    }

    bool filled() {
        for(auto const &el : board) {
            for(auto const &el_in : el) {
                if(el_in == 0)
                    return false; 
            }
        }
        return true;
    }

    std::array<std::array<int, 3>, 3> get_board() {
        return board;
    }
};

void show_board(std::array<std::array<int, 3>, 3> const &b) {
    auto write_line = [&](std::array<int, 3> l) {
        for(auto const &el : l) {
            std::cout << '|';
            std::cout << (el == 0 ? ' ' : el == 1 ? 'X' : 'O');
        }
        std::cout << '|';
    };
    std::cout.fill('_');
    std::cout.width(8);
    std::cout << '\n';
    int s = 0;
    for(auto const &el : b) {
        s++;
        write_line(el);
        std::cout << '\n';
        if(s < 3) {
            std::cout << '|';
            for(int i = 0; i < 5; ++i) 
                std::cout << '-';
            std::cout << "|\n";
        }
    }
    for(int i = 0; i < 7; ++i)
        std::cout << "¯";
    std::cout << '\n';
}

int str_to_number(std::string const &s) {
    for(auto const &el : s) {
        if(!std::isdigit(el)) {
            throw "Not a number!";
        }
    }
    std::istringstream iss(s);
    int x;
    iss >> x;
    return x;
}

std::pair<int, int> get_pos(bool isX) {
    std::string tmp;
    int r, c;
    std::cout << "\n\n\nPlace " << (isX ? 'X' : 'O') << ":\n";
    for(;;) {
        std::cout << "Row: ";
        std::cin >> tmp;
        try {
            r = str_to_number(tmp);
            break;
        } catch(const std::exception &e) {
            std::cout << "Invalid input, try again\n";
        }
    }
    for(;;) {
        std::cout << "Column: ";
        std::cin >> tmp; 
        try {
            c = str_to_number(tmp);
            break;
        } catch(const std::exception &e) {
            std::cout << "Invalid input, try again\n";
        }
    }
    return std::make_pair(r, c);
}

int main() {
    Board board;
    bool isX = true;
    show_board(board.get_board());
    while(!board.filled() && board.won() == 0) {
        std::pair<int, int> rc = get_pos(isX);
        try {
            board.insert(std::make_pair(rc.first-1, rc.second-1), isX);
            isX = !isX;
        } catch(const std::out_of_range &oor) {
            std::cerr << "Invalid Parameters!\n";
        } catch(const std::logic_error &le) {
            std::cerr << le.what() << '\n';
        }
        show_board(board.get_board());
    }
    if(board.won() == 1) {
        std::cout << "X Won!\n";
    } else if(board.won() == 4) {
        std::cout << "O Won!\n";
    } else {
        std::cout << "Board filled up!\n";
    }
}