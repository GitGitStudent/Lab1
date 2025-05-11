#ifndef SYGNALBAZOWY_H
#define SYGNALBAZOWY_H

#include "Sygnal.h"

/**
 * @class SygnalBazowy
 * @brief Klasa reprezentuj�ca sygna� bazowy, b�d�cy podstaw� dla dekorator�w.
 *
 * Sygna� bazowy generuje sta�� warto�� okre�lon� przez u�ytkownika.
 * Mo�e by� u�ywany jako pocz�tkowy komponent dla dekorator�w sygna��w.
 */
class SygnalBazowy : public Sygnal {
private:
    double poziom; ///< Sta�y poziom sygna�u bazowego.

public:
    /**
     * @brief Konstruktor sygna�u bazowego.
     * @param poziom Sta�y poziom, kt�ry ma by� generowany przez sygna�.
     */
    SygnalBazowy(double poziom);

    /**
     * @brief Zwraca warto�� sygna�u bazowego w chwili n.
     * @param n Indeks pr�bki (ignorowany, bo warto�� jest sta�a).
     * @return Sta�a warto�� poziomu sygna�u.
     */
    double symuluj(int n) override;

    /**
     * @brief Zapisuje konfiguracj� sygna�u bazowego do pliku.
     * @param out Strumie� wyj�ciowy.
     */
    void serialize(std::ofstream& out) const override;
};

#endif // SYGNALBAZOWY_H
