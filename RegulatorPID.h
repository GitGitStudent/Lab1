#ifndef REGULATORPID_H
#define REGULATORPID_H

#include "ObiektSISO.h"

/**
 * @brief Klasa reprezentujaca regulator PID.
 *
 * Dziedziczy po klasie ObiektSISO i implementuje funkcje symulujaca dzialanie regulatora PID.
 */
class RegulatorPID : public ObiektSISO {
private:
    /**
     * @brief Wzmocnienie proporcjonalne (P).
     */
    double k;

    /**
     * @brief Czas calkowania (I).
     */
    double Ti;

    /**
     * @brief Czas rozniczkowania (D).
     */
    double Td;

    /**
     * @brief Suma uchybow uzywana w skladniku calkujacyzm.
     */
    double sumaUchybow;

    /**
     * @brief Poprzedni uchyb uzywany w skladniku rozniczkujacym.
     */
    double poprzedniUchyb;

public:
    /**
     * @brief Konstruktor ustawiajacy wzmocnienie proporcjonalne.
     *
     * @param k Wartosc wzmocnienia proporcjonalnego.
     */
    RegulatorPID(double k);

    /**
     * @brief Konstruktor ustawiajacy wzmocnienie proporcjonalne i czas calkowania.
     *
     * @param k Wartosc wzmocnienia proporcjonalnego.
     * @param Ti Czas calkowania.
     */
    RegulatorPID(double k, double Ti);

    /**
     * @brief Konstruktor ustawiajacy wzmocnienie proporcjonalne, czas calkowania i czas rozniczkowania.
     *
     * @param k Wartosc wzmocnienia proporcjonalnego.
     * @param Ti Czas calkowania.
     * @param Td Czas rozniczkowania.
     */
    RegulatorPID(double k, double Ti, double Td);

    /**
     * @brief Ustawia nowe wzmocnienie proporcjonalne.
     *
     * @param k Nowa wartosc wzmocnienia proporcjonalnego.
     */
    void setK(double k);

    /**
     * @brief Ustawia nowy czas calkowania.
     *
     * @param Ti Nowa wartosc czasu calkowania.
     */
    void setTi(double Ti);

    /**
     * @brief Ustawia nowy czas rozniczkowania.
     *
     * @param Td Nowa wartosc czasu rozniczkowania.
     */
    void setTd(double Td);

    /**
     * @brief Symuluje dzialanie regulatora PID na podstawie podanego uchybu.
     *
     * @param uchyb Aktualna wartosc uchybu.
     * @return Obliczona wartosc sterowania.
     */
    double symuluj(double uchyb) override;

    /**
     * @brief Resetuje stan wewnetrzny regulatora (sume uchybow i poprzedni uchyb).
     */
    void reset();

    /**
     * @brief Sprawdza, czy wartosc jest dodatnia.
     *
     * @param wartosc Wartosc do sprawdzenia.
     * @return true jesli wartosc jest dodatnia, false w przeciwnym wypadku.
     */
    bool czyWartoscDodatnia(double wartosc);
};

#endif // REGULATORPID_H