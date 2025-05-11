#ifndef SYGNALBAZOWY_H
#define SYGNALBAZOWY_H

#include "Sygnal.h"

/**
 * @class SygnalBazowy
 * @brief Klasa reprezentuj¹ca sygna³ bazowy, bêd¹cy podstaw¹ dla dekoratorów.
 *
 * Sygna³ bazowy generuje sta³¹ wartoœæ okreœlon¹ przez u¿ytkownika.
 * Mo¿e byæ u¿ywany jako pocz¹tkowy komponent dla dekoratorów sygna³ów.
 */
class SygnalBazowy : public Sygnal {
private:
    double poziom; ///< Sta³y poziom sygna³u bazowego.

public:
    /**
     * @brief Konstruktor sygna³u bazowego.
     * @param poziom Sta³y poziom, który ma byæ generowany przez sygna³.
     */
    SygnalBazowy(double poziom);

    /**
     * @brief Zwraca wartoœæ sygna³u bazowego w chwili n.
     * @param n Indeks próbki (ignorowany, bo wartoœæ jest sta³a).
     * @return Sta³a wartoœæ poziomu sygna³u.
     */
    double symuluj(int n) override;

    /**
     * @brief Zapisuje konfiguracjê sygna³u bazowego do pliku.
     * @param out Strumieñ wyjœciowy.
     */
    void serialize(std::ofstream& out) const override;
};

#endif // SYGNALBAZOWY_H
