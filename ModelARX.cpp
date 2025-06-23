#include "ModelARX.h"
#include <numeric> // Dodajemy dla std::inner_product
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

// Konstruktor
ModelARX::ModelARX(const std::vector<double>& wspA, const std::vector<double>& wspB, int opoznienie, double mocZaklocenia)
    : wspA(wspA), wspB(wspB), opoznienie(opoznienie), mocZaklocenia(mocZaklocenia)
    {
    pamiecWejsc.resize(wspB.size() + opoznienie, 0.0);
    pamiecWyjsc.resize(wspA.size(), 0.0);
    if (mocZaklocenia > 0.0) {
        rozkladZaklocen = new std::normal_distribution<double>(0.0, mocZaklocenia);
    }
    else {
        rozkladZaklocen = nullptr;  // Nie tworzysz obiektu, jeœli mocZaklocenia = 0
    }
}

// Konstruktor deserializuj¹cy
ModelARX::ModelARX(std::istream& in) 
        : opoznienie(0), mocZaklocenia(0.0) {
    std::string line;
    std::cout << "[DEBUG] Rozpoczynam deserializacjê ModelARX" << std::endl;
    while (std::getline(in, line)) {
        std::cout << "[DEBUG] Odczytana linia: '" << line << "'" << std::endl;
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            std::cout << "[DEBUG] Klucz: '" << key << "', Wartoœæ: '" << value << "'" << std::endl;
            if (key == "wspA") {
                std::istringstream vecStream(value);
                double num;
                wspA.clear();
                while (vecStream >> num) {
                    wspA.push_back(num);
                    std::cout << "[DEBUG] Dodano do wspA: " << num << std::endl;
                }
            }
            else if (key == "wspB") {
                std::istringstream vecStream(value);
                double num;
                wspB.clear();
                while (vecStream >> num) {
                    wspB.push_back(num);
                    std::cout << "[DEBUG] Dodano do wspB: " << num << std::endl;
                }
            }
            else if (key == "opoznienie") {
                opoznienie = std::stoi(value);
                std::cout << "[DEBUG] Ustawiono opoznienie: " << opoznienie << std::endl;
            }
            else if (key == "mocZaklocenia") {
                mocZaklocenia = std::stod(value);
                std::cout << "[DEBUG] Ustawiono mocZaklocenia: " << mocZaklocenia << std::endl;
            }
        }
        if (line == "END_MODEL") {
            std::cout << "[DEBUG] Zakoñczono deserializacjê ModelARX (END_MODEL)" << std::endl;
            break;
        }
    }
    pamiecWejsc.resize(wspB.size() + opoznienie, 0.0);
    pamiecWyjsc.resize(wspA.size(), 0.0);
    if (mocZaklocenia > 0.0)
        rozkladZaklocen = new std::normal_distribution<double>(0.0, mocZaklocenia);
    else
        rozkladZaklocen = nullptr;
    std::cout << "[DEBUG] Rozmiar wspA: " << wspA.size() << ", wspB: " << wspB.size() << std::endl;
}


// Destruktor
ModelARX::~ModelARX() {
    if (rozkladZaklocen != nullptr) {
        delete rozkladZaklocen;
    }
}
// Implementacja metody symuluj
double ModelARX::symuluj(double wejscie) {
    // Dodanie wejœcia do pamiêci z uwzglêdnieniem opóŸnienia
    pamiecWejsc.push_front(wejscie);
    pamiecWejsc.pop_back();
    
    // Obliczenie wyjœcia na podstawie modelu ARX
    double wyjscie = 0.0;

    // Czêœæ licznika (B) - iloczyn skalarny wspB i pamiecWejsc (z uwzglêdnieniem opóŸnienia)
    wyjscie += std::inner_product(wspB.begin(), wspB.end(), pamiecWejsc.begin() + opoznienie, 0.0);

    // Czêœæ mianownika (A) - iloczyn skalarny wspA i pamiecWyjsc
    wyjscie -= std::inner_product(wspA.begin(), wspA.end(), pamiecWyjsc.begin(), 0.0);

    // Dodanie zak³ócenia
    if (rozkladZaklocen != nullptr) {
        // Generowanie zak³ócenia na podstawie rozk³adu normalnego
        wyjscie += (*rozkladZaklocen)(generator);
    }

    // Aktualizacja pamiêci wyjœæ
    
    
    pamiecWyjsc.push_front(wyjscie);
    pamiecWyjsc.pop_back();

    return wyjscie;
}

// Metoda serializacji
void ModelARX::serialize(std::ofstream& out) const {
    out << "wspA=";
    for (const auto& val : wspA) out << val << " ";
    out << "\n";
    out << "wspB=";
    for (const auto& val : wspB) out << val << " ";
    out << "\n";
    out << "opoznienie=" << opoznienie << "\n";
    out << "mocZaklocenia=" << mocZaklocenia << "\n";
    //out << "END_MODEL\n";
}

std::shared_ptr<ModelARX> ModelARX::deserialize(std::istream& in) {
    std::string line;
    std::vector<double> wspA, wspB;
    int opoznienie = 0;
    double mocZaklocenia = 0.0;
    bool found = false;

    in.clear();
    if (in.seekg(0), in.fail()) {
        std::cerr << "[ERROR] Nie mo¿na cofn¹æ strumienia!" << std::endl;
        return nullptr;
    }

    bool zaczacParsowanie = false;

    while (std::getline(in, line)) {
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        if (!zaczacParsowanie) {
            if (line == "END_SYGNAL") {
                zaczacParsowanie = true;
            }
            continue;
        }

        if (line == "END_MODEL") {
            found = true;
            break;
        }

        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            if (key == "wspA") {
                std::istringstream vecStream(value);
                double num;
                wspA.clear();
                while (vecStream >> num) wspA.push_back(num);
            }
            else if (key == "wspB") {
                std::istringstream vecStream(value);
                double num;
                wspB.clear();
                while (vecStream >> num) wspB.push_back(num);
            }
            else if (key == "opoznienie") {
                opoznienie = std::stoi(value);
            }
            else if (key == "mocZaklocenia") {
                mocZaklocenia = std::stod(value);
            }
        }
    }

    if (found) {
        // [DEBUG] ModelARX poprawnie zdeserializowany.
        return std::make_shared<ModelARX>(wspA, wspB, opoznienie, mocZaklocenia);
    }
    else {
        // [DEBUG] Nie znaleziono modelu ARX w pliku.
        return nullptr;
    }
}