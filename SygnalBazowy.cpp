#include "SygnalBazowy.h"
#include "SygnalKonkretny.h"
#include <iostream>

SygnalBazowy::SygnalBazowy(double poziom) 
    :  poziom(poziom) {}

double SygnalBazowy::symuluj(int n) {
    return poziom;
}

void SygnalBazowy::serialize(std::ofstream& out) const {
    out << "SygnalBazowy\n";
    out << "poziom=" << poziom << "\n";
}



