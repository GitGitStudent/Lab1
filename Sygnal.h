#ifndef SYGNAL_H
#define SYGNAL_H

#include <string>
#include <fstream>

/**
 * @file Sygnal.h
 * @brief Definicja abstrakcyjnej klasy bazowej reprezentuj�cej sygna�.
 */

 /**
  * @class Sygnal
  * @brief Abstrakcyjna klasa bazowa dla wszystkich typ�w sygna��w.
  *
  * Klasa definiuje interfejs dla metod symulacji oraz serializacji.
  */
class Sygnal {
public:
    /**
     * @brief Wirtualny destruktor.
     */
    virtual ~Sygnal() = default;

    /**
     * @brief Wirtualna metoda do symulacji warto�ci sygna�u w danym kroku czasowym.
     *
     * @param n Numer kroku czasowego.
     * @return Warto�� sygna�u w danym kroku.
     */
    virtual double symuluj(int n) = 0;

    /**
     * @brief Wirtualna metoda do serializacji sygna�u do pliku.
     *
     * @param out Strumie� wyj�ciowy, do kt�rego zapisujemy dane.
     */
    virtual void serialize(std::ofstream& out) const = 0;
};

#endif // SYGNAL_H
