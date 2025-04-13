#include "ModelARX.h"
#include <numeric> // Dodajemy dla std::inner_product
#include <fstream>
#include <sstream>
#include <stdexcept>

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
        rozkladZaklocen = nullptr;  // Nie tworzysz obiektu, je�li mocZaklocenia = 0
    }
}

// Konstruktor deserializuj�cy
ModelARX::ModelARX(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Nie mo�na otworzy� pliku do deserializacji.");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            if (key == "wspA") {
                std::istringstream vecStream(value);
                double num;
                wspA.clear();
                while (vecStream >> num) {
                    wspA.push_back(num);
                }
            }
            else if (key == "wspB") {
                std::istringstream vecStream(value);
                double num;
                wspB.clear();
                while (vecStream >> num) {
                    wspB.push_back(num);
                }
            }
            else if (key == "opoznienie") {
                opoznienie = std::stoi(value);
            }
            else if (key == "mocZaklocenia") {
                mocZaklocenia = std::stod(value);
            }
        }
    }

    pamiecWejsc.resize(wspB.size() + opoznienie, 0.0);
    pamiecWyjsc.resize(wspA.size(), 0.0);
    if (mocZaklocenia > 0.0) {
        rozkladZaklocen = new std::normal_distribution<double>(0.0, mocZaklocenia);
    }
    else {
        rozkladZaklocen = nullptr;
    }
}
// Destruktor
ModelARX::~ModelARX() {
    if (rozkladZaklocen != nullptr) {
        delete rozkladZaklocen;
    }
}
// Implementacja metody symuluj
double ModelARX::symuluj(double wejscie) {
    // Dodanie wej�cia do pami�ci z uwzgl�dnieniem op�nienia
    pamiecWejsc.push_front(wejscie);
    pamiecWejsc.pop_back();
    
    // Obliczenie wyj�cia na podstawie modelu ARX
    double wyjscie = 0.0;

    // Cz�� licznika (B) - iloczyn skalarny wspB i pamiecWejsc (z uwzgl�dnieniem op�nienia)
    wyjscie += std::inner_product(wspB.begin(), wspB.end(), pamiecWejsc.begin() + opoznienie, 0.0);

    // Cz�� mianownika (A) - iloczyn skalarny wspA i pamiecWyjsc
    wyjscie -= std::inner_product(wspA.begin(), wspA.end(), pamiecWyjsc.begin(), 0.0);

    // Dodanie zak��cenia
    if (rozkladZaklocen != nullptr) {
        // Generowanie zak��cenia na podstawie rozk�adu normalnego
        wyjscie += (*rozkladZaklocen)(generator);
    }

    // Aktualizacja pami�ci wyj��
    
    
    pamiecWyjsc.push_front(wyjscie);
    pamiecWyjsc.pop_back();

    return wyjscie;
}

// Metoda serializacji
void ModelARX::serialize(const std::string& filePath) const {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Nie mo�na otworzy� pliku do serializacji.");
    }

    file << "wspA=";
    for (const auto& val : wspA) {
        file << val << " ";
    }
    file << "\n";

    file << "wspB=";
    for (const auto& val : wspB) {
        file << val << " ";
    }
    file << "\n";

    file << "opoznienie=" << opoznienie << "\n";
    file << "mocZaklocenia=" << mocZaklocenia << "\n";

    file.close();
}