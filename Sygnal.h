#ifndef SYGNAL_H
#define SYGNAL_H

#include <string>
#include <fstream>

/**
 * @file Sygnal.h
 * @brief Definicja abstrakcyjnej klasy bazowej reprezentuj¹cej sygna³.
 */

 /**
  * @class Sygnal
  * @brief Abstrakcyjna klasa bazowa dla wszystkich typów sygna³ów.
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
     * @brief Wirtualna metoda do symulacji wartoœci sygna³u w danym kroku czasowym.
     *
     * @param n Numer kroku czasowego.
     * @return Wartoœæ sygna³u w danym kroku.
     */
    virtual double symuluj(int n) = 0;

    /**
     * @brief Wirtualna metoda do serializacji sygna³u do pliku.
     *
     * @param out Strumieñ wyjœciowy, do którego zapisujemy dane.
     */
    virtual void serialize(std::ofstream& out) const = 0;
};

#endif // SYGNAL_H
