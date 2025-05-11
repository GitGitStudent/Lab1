#ifndef DEKORATORYKONKRETNE_H
#define DEKORATORYKONKRETNE_H

#include "DekoratorSygnalu.h"
#include <cmath>
#include <fstream>

/**
 * @class OgraniczenieAmplitudy
 * @brief Dekorator ograniczaj�cy amplitud� sygna�u do podanej warto�ci maksymalnej.
 *
 * Klasa dziedziczy po DekoratorSygnalu i ogranicza warto�� sygna�u wyj�ciowego
 * do zakresu [-maksAmplituda, maksAmplituda].
 */
class OgraniczenieAmplitudy : public DekoratorSygnalu {
private:
    /**
     * @brief Wska�nik na dekorowany komponent sygna�u.
     */
    Sygnal* komponent;

    /**
     * @brief Maksymalna dopuszczalna warto�� amplitudy.
     */
    double maksAmplituda;

public:
    /**
     * @brief Konstruktor dekoratora ograniczaj�cego amplitud�.
     * @param komponent Wska�nik na sygna�, kt�ry ma by� dekorowany.
     * @param maksAmplituda Maksymalna warto�� amplitudy.
     */
    OgraniczenieAmplitudy(Sygnal* komponent, double maksAmplituda);

    /**
     * @brief Zwraca warto�� sygna�u przy zadanym indeksie pr�bki z ograniczeniem amplitudy.
     * @param n Indeks pr�bki.
     * @return Ograniczona warto�� sygna�u.
     */
    double symuluj(int n) override;

    /**
     * @brief Zapisuje konfiguracj� dekoratora do pliku.
     * @param out Strumie� wyj�ciowy.
     */
    void serialize(std::ofstream& out) const override;
};

#endif // DEKORATORYKONKRETNE_H
