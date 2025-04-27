#include "PetlaSprzezeniaZwrotnego.h"

// Konstruktor
PetlaSprzezeniaZwrotnego::PetlaSprzezeniaZwrotnego() : poprzedniaWartoscWyjscia(0.0) {}

// Operator funktora
double PetlaSprzezeniaZwrotnego::operator()(RegulatorPID& regulator, ModelARX& model, double wartoscZadana) {
    
    double uchyb = wartoscZadana - poprzedniaWartoscWyjscia;
     
    // Symuluj dzia³anie regulatora
    //for (int i = 0;i < 2;i++) {
    double sterowanie = regulator.symuluj(uchyb);
    //}
    // Symuluj dzia³anie ModelARX
    poprzedniaWartoscWyjscia = model.symuluj(sterowanie);

    // Zwróæ wartoœæ regulowan¹
    return poprzedniaWartoscWyjscia;
}

