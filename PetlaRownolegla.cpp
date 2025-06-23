#include "PetlaRownolegla.h"

void PetlaRownolegla::ustawTrybPetli(TrybPetliUAR tryb) {
    trybPetli = tryb;
}

TrybPetliUAR PetlaRownolegla::pobierzTrybPetli() const {
    return trybPetli;
}

void PetlaRownolegla::dodaj(std::shared_ptr<ObiektSISO> obiekt) {
    skladniki.push_back(obiekt);
}

void PetlaRownolegla::dodaj(std::shared_ptr<ObiektSISO> obiekt, size_t indeks) {
    if (indeks > skladniki.size()) indeks = skladniki.size();
    skladniki.insert(skladniki.begin() + indeks, obiekt);
}

void PetlaRownolegla::usun(size_t indeks) {
    if (indeks < skladniki.size()) {
        skladniki.erase(skladniki.begin() + indeks);
    }
}

size_t PetlaRownolegla::liczbaSkladnikow() const {
    return skladniki.size();
}

double PetlaRownolegla::symuluj(double wejscie) {
    if (skladniki.empty()) return 0.0;
    double uchyb = wejscie;
    if (trybPetli == TrybPetliUAR::Zamknieta) {
        uchyb = wejscie - poprzednieWyjscie;
    }
    double suma = 0.0;
    for (auto& obiekt : skladniki) {
        suma += obiekt->symuluj(uchyb);
    }
    if (trybPetli == TrybPetliUAR::Zamknieta) {
        poprzednieWyjscie = suma;
    }
    return suma;
}
