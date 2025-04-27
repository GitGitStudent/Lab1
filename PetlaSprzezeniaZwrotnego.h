#ifndef PETLASPRZEZENIAZWROTNEGO_H
#define PETLASPRZEZENIAZWROTNEGO_H

#include "RegulatorPID.h"
#include "ModelARX.h"

/**
 * @brief Klasa reprezentujaca petle sprzezenia zwrotnego.
 *
 * Umozliwia symulacje dzialania ukladu regulacji opartego na regulatorze PID i modelu ARX.
 */
class PetlaSprzezeniaZwrotnego {
private:
    /**
     * @brief Przechowuje poprzednia wartosc wyjsciowa modelu.
     */
    double poprzedniaWartoscWyjscia;

public:
    /**
     * @brief Konstruktor klasy PetlaSprzezeniaZwrotnego.
     *
     * Inicjalizuje wartosci domyslne obiektu.
     */
    PetlaSprzezeniaZwrotnego();

    /**
     * @brief Wykonuje jedna iteracje petli sprzezenia zwrotnego.
     *
     * @param regulator Odniesienie do obiektu regulatora PID.
     * @param model Odniesienie do obiektu modelu ARX.
     * @param wartoscZadana Wartosc zadana, ktora uklad powinien osiagnac.
     * @return Aktualna wartosc wyjsciowa ukladu po zastosowaniu regulatora i modelu.
     */
    double operator()(RegulatorPID& regulator, ModelARX& model, double wartoscZadana);
};

#endif // PETLASPRZEZENIAZWROTNEGO_H