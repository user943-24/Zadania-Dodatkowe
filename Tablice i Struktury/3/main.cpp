#include <iostream>
#include <sys/types.h>

struct Samochod {
    std::string marka;
    std::string model;
    uint16_t rok_produkcji;
    uint32_t przebieg;
    uint32_t cena_wyjsciowa;
    uint32_t cena_koncowa;
    Samochod(std::string mar, std::string mod, uint16_t rok, uint32_t prze) {
        marka = mar;
        model = mod;
        rok_produkcji = rok;
        przebieg = prze;
    }

    void ustaw_cene_wyjsciowa(uint32_t cena) {
        cena_wyjsciowa = cena;
    }

    uint32_t oblicz_cene_koncowa() {
        int32_t tmp = (2021-rok_produkcji)*10000;
        if(tmp > cena_wyjsciowa) {
            cena_koncowa = 0;
            return 0;
        }
        cena_koncowa = cena_wyjsciowa-tmp;
        tmp = przebieg*3;
        if(tmp > cena_koncowa) {
            cena_wyjsciowa = 0;
            return 0;
        }
        cena_koncowa -= tmp;
        return cena_koncowa;
    }
};

int main() {
    auto s1 = Samochod("one", "one", 2016, 10003);
    auto s2 = Samochod("two", "two", 1999, 100000);
    auto s3 = Samochod("three", "three", 2021, 1000);
    s1.ustaw_cene_wyjsciowa(260000);
    std::cout << s1.oblicz_cene_koncowa() << "\n";
    s2.ustaw_cene_wyjsciowa(500000);
    std::cout << s2.oblicz_cene_koncowa() << "\n";
    s3.ustaw_cene_wyjsciowa(100000);
    std::cout << s3.oblicz_cene_koncowa() << "\n";

}
