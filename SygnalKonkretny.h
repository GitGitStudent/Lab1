#ifndef SYGNALKONKRETNY_H
#define SYGNALKONKRETNY_H

#include "DekoratorSygnalu.h"
#include "Sygnal.h"
#include <deque>
#include <random>
#include <cmath>
#include <fstream>

/**
 * @class SygnalSinusoidalny
 * @brief Dekorator generuj�cy sygna� sinusoidalny.
 */
class SygnalSinusoidalny : public DekoratorSygnalu {
private:
    Sygnal* komponent;              ///< Wska�nik na dekorowany sygna�.
    double amplituda;              ///< Amplituda sygna�u.
    double czestotliwosc;          ///< Cz�stotliwo�� sygna�u.
    double T;                      ///< Okres pr�bkowania.
    double omegaT;                 ///< Cz�stotliwo�� k�towa * T.
    std::deque<double> poprzednie; ///< Historia poprzednich warto�ci sygna�u.

public:
    /**
     * @brief Konstruktor sygna�u sinusoidalnego.
     * @param komponent Wska�nik na dekorowany sygna�.
     * @param amplituda Amplituda fali.
     * @param czestotliwosc Cz�stotliwo�� fali.
     * @param T Okres pr�bkowania.
     */
    SygnalSinusoidalny(Sygnal* komponent, double amplituda, double czestotliwosc, double T);

    /**
     * @brief Zwraca warto�� sygna�u sinusoidalnego w chwili n.
     * @param n Indeks pr�bki.
     * @return Warto�� sygna�u.
     */
    double symuluj(int n) override;

    /**
     * @brief Zapisuje konfiguracj� sygna�u do pliku.
     * @param out Strumie� wyj�ciowy.
     */
    void serialize(std::ofstream& out) const override;
};

/**
 * @class SygnalProstokatny
 * @brief Dekorator generuj�cy sygna� prostok�tny.
 */
class SygnalProstokatny : public DekoratorSygnalu {
private:
    Sygnal* komponent;    ///< Wska�nik na dekorowany sygna�.
    double amplituda;     ///< Amplituda sygna�u.
    int okres;            ///< Okres sygna�u.
    double wypelnienie;   ///< Wype�nienie sygna�u (0.0�1.0).
    int krok;             ///< Licznik pr�bek.

public:
    /**
     * @brief Konstruktor sygna�u prostok�tnego.
     * @param komponent Wska�nik na dekorowany sygna�.
     * @param amplituda Amplituda.
     * @param okres Okres.
     * @param wypelnienie Stosunek czasu trwania stanu wysokiego do okresu.
     */
    SygnalProstokatny(Sygnal* komponent, double amplituda, int okres, double wypelnienie);

    /**
     * @brief Oblicza warto�� sygna�u prostok�tnego dla pr�bki n.
     * @param n Indeks pr�bki.
     * @return Warto�� sygna�u.
     */
    double symuluj(int n) override;

    /**
     * @brief Zapisuje dane konfiguracji do pliku.
     * @param out Strumie� wyj�ciowy.
     */
    void serialize(std::ofstream& out) const override;
};

/**
 * @class SygnalTrojkatny
 * @brief Dekorator generuj�cy sygna� tr�jk�tny.
 */
class SygnalTrojkatny : public DekoratorSygnalu {
private:
    Sygnal* komponent;    ///< Wska�nik na dekorowany sygna�.
    double amplituda;     ///< Amplituda sygna�u.
    int okres;            ///< Okres sygna�u.
    int krok;             ///< Licznik pr�bek.

public:
    /**
     * @brief Konstruktor sygna�u tr�jk�tnego.
     * @param komponent Wska�nik na dekorowany sygna�.
     * @param amplituda Amplituda.
     * @param okres Okres.
     */
    SygnalTrojkatny(Sygnal* komponent, double amplituda, int okres);

    /**
     * @brief Zwraca warto�� sygna�u tr�jk�tnego w chwili n.
     * @param n Indeks pr�bki.
     * @return Warto�� sygna�u.
     */
    double symuluj(int n) override;

    /**
     * @brief Zapisuje konfiguracj� sygna�u do pliku.
     * @param out Strumie� wyj�ciowy.
     */
    void serialize(std::ofstream& out) const override;
};

/**
 * @class SygnalBialySzum
 * @brief Dekorator generuj�cy bia�y szum.
 */
class SygnalBialySzum : public DekoratorSygnalu {
private:
    Sygnal* komponent;                      ///< Wska�nik na dekorowany sygna�.
    double amplituda;                       ///< Zakres warto�ci bia�ego szumu.
    std::default_random_engine generator;   ///< Generator liczb pseudolosowych.
    std::uniform_real_distribution<double> rozklad; ///< Rozk�ad r�wnomierny.

public:
    /**
     * @brief Konstruktor dekoratora generuj�cego bia�y szum.
     * @param komponent Wska�nik na dekorowany sygna�.
     * @param amplituda Maksymalna warto�� szumu.
     */
    SygnalBialySzum(Sygnal* komponent, double amplituda);

    /**
     * @brief Zwraca warto�� sygna�u z dodanym bia�ym szumem w chwili n.
     * @param n Indeks pr�bki.
     * @return Warto�� sygna�u.
     */
    double symuluj(int n) override;

    /**
     * @brief Zapisuje konfiguracj� dekoratora do pliku.
     * @param out Strumie� wyj�ciowy.
     */
    void serialize(std::ofstream& out) const override;
};

#endif // SYGNALKONKRETNY_H
