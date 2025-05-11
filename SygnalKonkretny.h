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
 * @brief Dekorator generuj¹cy sygna³ sinusoidalny.
 */
class SygnalSinusoidalny : public DekoratorSygnalu {
private:
    Sygnal* komponent;              ///< WskaŸnik na dekorowany sygna³.
    double amplituda;              ///< Amplituda sygna³u.
    double czestotliwosc;          ///< Czêstotliwoœæ sygna³u.
    double T;                      ///< Okres próbkowania.
    double omegaT;                 ///< Czêstotliwoœæ k¹towa * T.
    std::deque<double> poprzednie; ///< Historia poprzednich wartoœci sygna³u.

public:
    /**
     * @brief Konstruktor sygna³u sinusoidalnego.
     * @param komponent WskaŸnik na dekorowany sygna³.
     * @param amplituda Amplituda fali.
     * @param czestotliwosc Czêstotliwoœæ fali.
     * @param T Okres próbkowania.
     */
    SygnalSinusoidalny(Sygnal* komponent, double amplituda, double czestotliwosc, double T);

    /**
     * @brief Zwraca wartoœæ sygna³u sinusoidalnego w chwili n.
     * @param n Indeks próbki.
     * @return Wartoœæ sygna³u.
     */
    double symuluj(int n) override;

    /**
     * @brief Zapisuje konfiguracjê sygna³u do pliku.
     * @param out Strumieñ wyjœciowy.
     */
    void serialize(std::ofstream& out) const override;
};

/**
 * @class SygnalProstokatny
 * @brief Dekorator generuj¹cy sygna³ prostok¹tny.
 */
class SygnalProstokatny : public DekoratorSygnalu {
private:
    Sygnal* komponent;    ///< WskaŸnik na dekorowany sygna³.
    double amplituda;     ///< Amplituda sygna³u.
    int okres;            ///< Okres sygna³u.
    double wypelnienie;   ///< Wype³nienie sygna³u (0.0–1.0).
    int krok;             ///< Licznik próbek.

public:
    /**
     * @brief Konstruktor sygna³u prostok¹tnego.
     * @param komponent WskaŸnik na dekorowany sygna³.
     * @param amplituda Amplituda.
     * @param okres Okres.
     * @param wypelnienie Stosunek czasu trwania stanu wysokiego do okresu.
     */
    SygnalProstokatny(Sygnal* komponent, double amplituda, int okres, double wypelnienie);

    /**
     * @brief Oblicza wartoœæ sygna³u prostok¹tnego dla próbki n.
     * @param n Indeks próbki.
     * @return Wartoœæ sygna³u.
     */
    double symuluj(int n) override;

    /**
     * @brief Zapisuje dane konfiguracji do pliku.
     * @param out Strumieñ wyjœciowy.
     */
    void serialize(std::ofstream& out) const override;
};

/**
 * @class SygnalTrojkatny
 * @brief Dekorator generuj¹cy sygna³ trójk¹tny.
 */
class SygnalTrojkatny : public DekoratorSygnalu {
private:
    Sygnal* komponent;    ///< WskaŸnik na dekorowany sygna³.
    double amplituda;     ///< Amplituda sygna³u.
    int okres;            ///< Okres sygna³u.
    int krok;             ///< Licznik próbek.

public:
    /**
     * @brief Konstruktor sygna³u trójk¹tnego.
     * @param komponent WskaŸnik na dekorowany sygna³.
     * @param amplituda Amplituda.
     * @param okres Okres.
     */
    SygnalTrojkatny(Sygnal* komponent, double amplituda, int okres);

    /**
     * @brief Zwraca wartoœæ sygna³u trójk¹tnego w chwili n.
     * @param n Indeks próbki.
     * @return Wartoœæ sygna³u.
     */
    double symuluj(int n) override;

    /**
     * @brief Zapisuje konfiguracjê sygna³u do pliku.
     * @param out Strumieñ wyjœciowy.
     */
    void serialize(std::ofstream& out) const override;
};

/**
 * @class SygnalBialySzum
 * @brief Dekorator generuj¹cy bia³y szum.
 */
class SygnalBialySzum : public DekoratorSygnalu {
private:
    Sygnal* komponent;                      ///< WskaŸnik na dekorowany sygna³.
    double amplituda;                       ///< Zakres wartoœci bia³ego szumu.
    std::default_random_engine generator;   ///< Generator liczb pseudolosowych.
    std::uniform_real_distribution<double> rozklad; ///< Rozk³ad równomierny.

public:
    /**
     * @brief Konstruktor dekoratora generuj¹cego bia³y szum.
     * @param komponent WskaŸnik na dekorowany sygna³.
     * @param amplituda Maksymalna wartoœæ szumu.
     */
    SygnalBialySzum(Sygnal* komponent, double amplituda);

    /**
     * @brief Zwraca wartoœæ sygna³u z dodanym bia³ym szumem w chwili n.
     * @param n Indeks próbki.
     * @return Wartoœæ sygna³u.
     */
    double symuluj(int n) override;

    /**
     * @brief Zapisuje konfiguracjê dekoratora do pliku.
     * @param out Strumieñ wyjœciowy.
     */
    void serialize(std::ofstream& out) const override;
};

#endif // SYGNALKONKRETNY_H
