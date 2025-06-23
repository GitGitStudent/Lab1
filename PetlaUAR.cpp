#include "PetlaUAR.h"

PetlaUAR::PetlaUAR(TypKompozycjiUAR typ, TrybPetliUAR tryb)
    : typKompozycji(typ), trybPetli(tryb), poprzednieWyjscie(0.0) {
}

void PetlaUAR::ustawTrybPetli(TrybPetliUAR tryb) {
    trybPetli = tryb;
}

TrybPetliUAR PetlaUAR::pobierzTrybPetli() const {
    return trybPetli;
}

void PetlaUAR::dodaj(std::shared_ptr<ObiektSISO> obiekt) {
    skladniki.push_back(obiekt);
}

void PetlaUAR::dodaj(std::shared_ptr<ObiektSISO> obiekt, size_t indeks) {
    if (indeks > skladniki.size()) indeks = skladniki.size();
    skladniki.insert(skladniki.begin() + indeks, obiekt);
}

void PetlaUAR::usun(size_t indeks) {
    if (indeks < skladniki.size()) {
        skladniki.erase(skladniki.begin() + indeks);
    }
}

double PetlaUAR::symuluj(double wejscie) {
    if (skladniki.empty()) return 0.0;

    double sygnal = wejscie;
    double wyjscie = 0.0;

    if (typKompozycji == TypKompozycjiUAR::Szeregowa) {
        // Tryb zamkniêty: uchyb na wejœcie pierwszego obiektu
        if (trybPetli == TrybPetliUAR::Zamknieta) {
            sygnal = wejscie - poprzednieWyjscie;
        }
        for (auto& obiekt : skladniki) {
            sygnal = obiekt->symuluj(sygnal);
        }
        wyjscie = sygnal;
        if (trybPetli == TrybPetliUAR::Zamknieta) {
            poprzednieWyjscie = wyjscie;
        }
        return wyjscie;
    }
    else if (typKompozycji == TypKompozycjiUAR::Rownolegla) {
        // Tryb zamkniêty: uchyb na wejœcie ka¿dego obiektu
        double uchyb = wejscie;
        if (trybPetli == TrybPetliUAR::Zamknieta) {
            uchyb = wejscie - poprzednieWyjscie;
        }
        double suma = 0.0;
        for (auto& obiekt : skladniki) {
            suma += obiekt->symuluj(uchyb);
        }
        wyjscie = suma;
        if (trybPetli == TrybPetliUAR::Zamknieta) {
            poprzednieWyjscie = wyjscie;
        }
        return wyjscie;
    }

    // Domyœlnie (nieznany typ kompozycji)
    return 0.0;
}

size_t PetlaUAR::liczbaSkladnikow() const {
    return skladniki.size();
}
