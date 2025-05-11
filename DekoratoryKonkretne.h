#ifndef DEKORATORYKONKRETNE_H
#define DEKORATORYKONKRETNE_H

#include "DekoratorSygnalu.h"
#include <cmath>
#include <fstream>

/**
 * @class OgraniczenieAmplitudy
 * @brief Dekorator ograniczaj¹cy amplitudê sygna³u do podanej wartoœci maksymalnej.
 *
 * Klasa dziedziczy po DekoratorSygnalu i ogranicza wartoœæ sygna³u wyjœciowego
 * do zakresu [-maksAmplituda, maksAmplituda].
 */
class OgraniczenieAmplitudy : public DekoratorSygnalu {
private:
    /**
     * @brief WskaŸnik na dekorowany komponent sygna³u.
     */
    Sygnal* komponent;

    /**
     * @brief Maksymalna dopuszczalna wartoœæ amplitudy.
     */
    double maksAmplituda;

public:
    /**
     * @brief Konstruktor dekoratora ograniczaj¹cego amplitudê.
     * @param komponent WskaŸnik na sygna³, który ma byæ dekorowany.
     * @param maksAmplituda Maksymalna wartoœæ amplitudy.
     */
    OgraniczenieAmplitudy(Sygnal* komponent, double maksAmplituda);

    /**
     * @brief Zwraca wartoœæ sygna³u przy zadanym indeksie próbki z ograniczeniem amplitudy.
     * @param n Indeks próbki.
     * @return Ograniczona wartoœæ sygna³u.
     */
    double symuluj(int n) override;

    /**
     * @brief Zapisuje konfiguracjê dekoratora do pliku.
     * @param out Strumieñ wyjœciowy.
     */
    void serialize(std::ofstream& out) const override;
};

#endif // DEKORATORYKONKRETNE_H
