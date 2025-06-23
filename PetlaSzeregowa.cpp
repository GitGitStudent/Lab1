#include "PetlaSzeregowa.h"

void PetlaSzeregowa::ustawTrybPetli(TrybPetliUAR tryb) {
    trybPetli = tryb;
}

TrybPetliUAR PetlaSzeregowa::pobierzTrybPetli() const {
    return trybPetli;
}

void PetlaSzeregowa::dodaj(std::shared_ptr<ObiektSISO> obiekt) {
    skladniki.push_back(obiekt);
}

void PetlaSzeregowa::dodaj(std::shared_ptr<ObiektSISO> obiekt, size_t indeks) {
    if (indeks > skladniki.size()) indeks = skladniki.size();
    skladniki.insert(skladniki.begin() + indeks, obiekt);
}

void PetlaSzeregowa::usun(size_t indeks) {
    if (indeks < skladniki.size()) {
        skladniki.erase(skladniki.begin() + indeks);
    }
}

size_t PetlaSzeregowa::liczbaSkladnikow() const {
    return skladniki.size();
}

double PetlaSzeregowa::symuluj(double wejscie) {
    if (skladniki.empty()) return 0.0;
    double sygnal = wejscie;
    if (trybPetli == TrybPetliUAR::Zamknieta) {
        sygnal = wejscie - poprzednieWyjscie;
    }
    for (auto& obiekt : skladniki) {
        sygnal = obiekt->symuluj(sygnal);
    }
    if (trybPetli == TrybPetliUAR::Zamknieta) {
        poprzednieWyjscie = sygnal;
    }
    return sygnal;
}
