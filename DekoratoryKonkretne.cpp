#include "DekoratoryKonkretne.h"

// Dekorator ograniczaj�cy amplitud�
OgraniczenieAmplitudy::OgraniczenieAmplitudy(Sygnal* komponent ,double maksAmplituda)
    : komponent(komponent), maksAmplituda(maksAmplituda) {
}

double OgraniczenieAmplitudy::symuluj(int n) {
    double wartosc = komponent->symuluj(n);
    if (wartosc > maksAmplituda) return maksAmplituda;
    if (wartosc < -maksAmplituda) return -maksAmplituda;
    return wartosc;
}

void OgraniczenieAmplitudy::serialize(std::ofstream& out) const {
    out << "OgraniczenieAmplitudy\n";
    out << "maksAmplituda=" << maksAmplituda << "\n";
    komponent->serialize(out); // Delegacja serializacji do komponentu bazowego
}




