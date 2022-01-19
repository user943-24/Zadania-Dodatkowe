#include <exception>
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <array>

class Trojkat {
    unsigned a, b, c;
public:
    void wymiary() {
        std::cout << "a: " << a <<
            "\nb: " << b << "\nc: "
            << c << "\n";
    }

    void sprawdz() {
        std::array<unsigned, 3> arr {a, b, c};
        std::sort(arr.begin(), arr.end());

        for(auto &el : arr)
            el *= el;

        if(arr.at(0)+arr.at(1) == arr.at(2))
            std::cout << "Trójkąt jest prostokątny\n";
        else if(arr.at(0)+arr.at(1) < arr.at(2))
            std::cout << "Trójkąt jest rozwartokątny\n";
        else
            std::cout << "Trójkąt jest ostrokątny\n";
    }

    Trojkat(unsigned a, unsigned b, unsigned c) {
        if(a + b < c || a + c < b || b + c < a) {
            throw "Niepoprawne wymiary";
        }
        this->a = a;
        this->b = b;
        this->c = c;
    }
};

int main() {
    std::vector<Trojkat> triangles;
    auto safe_constructor = [&] (unsigned a, unsigned b, unsigned c) -> Trojkat {
        try {
            return Trojkat(a, b, c);
        } catch(const std::exception &e) {
            std::cerr << e.what() << "\n";
            exit(1);
        }
    };

    triangles.push_back(safe_constructor(3, 4, 5));
    triangles.push_back(safe_constructor(10, 10, 6));
    triangles.push_back(safe_constructor(20, 20, 30));

    for(auto &el : triangles) {
        el.wymiary();
        el.sprawdz();
        std::cout << "\n";
    }
}
