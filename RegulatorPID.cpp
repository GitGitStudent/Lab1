#include "RegulatorPID.h"
#include <iostream>

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