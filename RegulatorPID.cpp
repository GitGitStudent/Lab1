#include "RegulatorPID.h"
#include <iostream>
#include <numeric> // Dodajemy dla std::inner_product
#include <fstream>
#include <sstream>
#include <stdexcept>


RegulatorPID::RegulatorPID(double k)
    : k(k), Ti(0.0), Td(0.0), sumaUchybow(0.0), poprzedniUchyb(0.0) {
}

RegulatorPID::RegulatorPID(double k, double Ti)
    : k(k), Ti(Ti), Td(0.0), sumaUchybow(0.0), poprzedniUchyb(0.0) {
}

RegulatorPID::RegulatorPID(double k, double Ti, double Td)
    : k(k), Ti(Ti), Td(Td), sumaUchybow(0.0), poprzedniUchyb(0.0) {
}

bool RegulatorPID::czyWartoscDodatnia(double wartosc) {
    return wartosc >= 0.0;
}

void RegulatorPID::setK(double k) {
    if (czyWartoscDodatnia(k)) {
        this->k = k;
    }
    else {
        std::cerr << "Blad: k musi byc dodatnie.\n";
    }
}

void RegulatorPID::setTi(double Ti) {
    if (czyWartoscDodatnia(Ti)) {
        this->Ti = Ti;
	}
    else {
        std::cerr << "Blad: Ti musi byc dodatnie.\n";
    }
}

void RegulatorPID::setTd(double Td) {
    if (czyWartoscDodatnia(Td)) {
        this->Td = Td;
	}
    else {
        std::cerr << "Blad: Td musi byc dodatnie.\n";
    }
}

double RegulatorPID::symuluj(double uchyb) {
    double P = k * uchyb;

    double I = 0.0;
    if (Ti > 0.0) {
        sumaUchybow += uchyb;
        I = (1.0 / Ti) * sumaUchybow;
    }

    double D = 0.0;
    if (Td > 0.0) {
        D = Td * (uchyb - poprzedniUchyb);
    }

    poprzedniUchyb = uchyb;

    return P + I + D;
}

void RegulatorPID::reset() {
    sumaUchybow = 0.0;
    poprzedniUchyb = 0.0;
}

void RegulatorPID::serialize(std::ostream& out) const {
    out << "k=" << k << "\n";
    out << "Ti=" << Ti << "\n";
    out << "Td=" << Td << "\n";
}

std::shared_ptr<RegulatorPID> RegulatorPID::deserialize(std::istream& in) {
    std::string line;
    double k = 0.0, Ti = 0.0, Td = 0.0;
    bool startReading = false;

    // Cofamy strumieñ na pocz¹tek pliku
    in.clear();
    in.seekg(0);
    if (in.fail()) {
        std::cerr << "[ERROR] Nie mo¿na cofn¹æ strumienia do pocz¹tku!" << std::endl;
        return nullptr;
    }

    // Szukamy "END_MODEL"
    while (std::getline(in, line)) {
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        if (line == "END_MODEL") {
            startReading = true;
            break;
        }
    }

    if (!startReading) {
        std::cerr << "[ERROR] Nie znaleziono END_MODEL w pliku." << std::endl;
        return nullptr;
    }

    // Czytamy a¿ do "END_PID"
    while (std::getline(in, line)) {
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        if (line == "END_PID") break;

        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            try {
                if (key == "k") k = std::stod(value);
                else if (key == "Ti") Ti = std::stod(value);
                else if (key == "Td") Td = std::stod(value);
            }
            catch (...) {
                std::cerr << "[WARNING] B³¹d parsowania wartoœci: " << key << " = " << value << std::endl;
            }
        }
    }

    return std::make_shared<RegulatorPID>(k, Ti, Td);
}