#include <cstddef>
#include <iostream>
#include <vector>
#include <ctime>
#include <functional>

typedef struct Pacjent {
    std::string login;
    std::string haslo;
    std::string nazwisko;
    std::vector<tm> tablica_dat_szczepien;
    Pacjent(std::string l, std::string p, std::string n) {
        login = l;
        nazwisko = n;
        haslo = p;
    }
    Pacjent() {
        login = "";
        nazwisko = "";
        haslo = "";
    }
    void nowa_data(int y, int m, int d) {
        tm ltm;
        ltm.tm_mday = d;
        ltm.tm_mon = m+1;
        ltm.tm_year = 1900+y;
        tablica_dat_szczepien.push_back(ltm);
    }
} Pacjent;

Pacjent rejestruj(std::string l, std::string p, std::string n) {
    return Pacjent(l, p, n);
}

Pacjent &zaloguj(
    std::vector<std::reference_wrapper<Pacjent>> vec,
    std::string l, std::string p, bool &log) {
    for(auto &el : vec) {
        if(std::ref(el).get().login == l && el.get().haslo == p) {
            log = true;
            return el;
        }
    }
    throw "Brak pacjenta";
}

void wyloguj(bool &log) {
   log = false;
}

void wypisz(const Pacjent &p) {
    if(p.tablica_dat_szczepien.size() == 0) {
        std::cout << "Brak szczepień\n";
        return;
    }
    for(auto const &el : p.tablica_dat_szczepien) {
        std::cout << el.tm_mday << "."
            << el.tm_mon << "."
            << el.tm_year << "\n";
    }
}

bool czyMoge(Pacjent &p) {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    tm *lltm = &p.tablica_dat_szczepien.at(p.tablica_dat_szczepien.size()-1);
    switch(p.tablica_dat_szczepien.size()) {
        case 0:
            return true;
        case 1:
            if(1900+ltm->tm_year - lltm->tm_year > 0)
                return true;
            else if(ltm->tm_mon - lltm->tm_mon > 0)
                return true;
            else
                return false;
        default:
            if(1900+ltm->tm_year - lltm->tm_year > 0)
                return true;
            else if(ltm->tm_mon - lltm->tm_mon > 5)
                return true;
            else
                return false;
    }
}

void zaszczep(Pacjent &p) {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    p.nowa_data(ltm->tm_year, ltm->tm_mon, ltm->tm_mday);
}

bool czyWaznyCertyfikat(Pacjent &p) {
    if(p.tablica_dat_szczepien.size() >= 2) {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        tm *lltm = &p.tablica_dat_szczepien.at(p.tablica_dat_szczepien.size()-1);
        if(ltm->tm_year - lltm->tm_year < 1) {
            return true;
        }
    }
    return false;
}

int main() {
    std::vector<std::reference_wrapper<Pacjent>> vec;

    bool logged_in = false;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::string tmp;

    auto ptmp = rejestruj("", "", "");
    Pacjent &current = std::ref(ptmp);

    for(;;) {
        if(!logged_in) {
            std::cout << "1) Zaloguj\n"
                "2) Zarejestruj\n"
                "0) Wyjdź\n"
                "\n> ";
            std::cin >> tmp;
            if(tmp == "1") {
                std::string l, p;
                std::cout << "Podaj login: ";
                std::cin >> l;
                std::cout << "Podaj hasło: ";
                std::cin >> p;
                try {
                    current = zaloguj(vec, l, p, logged_in);
                    std::cout << "Zalogowano!\n";
                    std::cout << "Witaj " << current.nazwisko << "\n";
                } catch(char const *msg) {
                    std::cout << msg << "\n";
                }
            } else if(tmp == "2") {
                std::string l, p, n;
                std::cin.ignore();

                std::cout << "Podaj login: ";
                std::getline(std::cin, l);
                std::cout << "Podaj hasło: ";
                std::getline(std::cin, p);
                std::cout << "Podaj imie: ";
                std::getline(std::cin, n);

                auto r = rejestruj(l, p, n);
                vec.push_back(std::ref(r));
            } else if(tmp == "0") {
                exit(0);
            } else {
                std::cout << "Niepoprawny wybór!\n";
            }
        } else {
            std::cout << "1) Pokaż daty szczepień\n"
                "2) Sprawdź czy mogę się zaszczepić\n"
                "3) Zaszczep\n"
                "4) Sprawdź ważność certyfikatu\n"
                "5) Wyloguj\n"
                "0) Wyjdź\n"
                "\n> ";
            std::cin >> tmp;
            if(tmp == "1")
                wypisz(current);
            else if(tmp == "2") {
                if(czyMoge(current))
                    std::cout << "Można się szczepić\n";
                else
                    std::cout << "Nie można się szczepić\n";
            }
            else if(tmp == "3") {
                zaszczep(current);
                std::cout << "Dodano date szczepienia!\n";
            } else if(tmp == "4") {
                if(czyWaznyCertyfikat(current))
                    std::cout << "Certyfikat ważny\n";
                else
                    std::cout << "Certyfikat nieważny\n";
            } else if(tmp == "5")
                wyloguj(logged_in);
            else if(tmp == "0")
                exit(0);
        }
    }
}
