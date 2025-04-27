#ifndef OBIEKTSISO_H
#define OBIEKTSISO_H

/**
 * @brief Klasa bazowa reprezentujaca obiekt SISO (Single Input, Single Output).
 *
 * Jest to interfejs dla obiektow, ktore posiadaja pojedynczy sygnal wejsciowy i pojedynczy sygnal wyjsciowy.
 */
class ObiektSISO {
public:
    /**
     * @brief Wirtualny destruktor.
     */
    virtual ~ObiektSISO() = default;

    /**
     * @brief Metoda wirtualna do symulacji odpowiedzi obiektu na sygnal wejsciowy.
     *
     * @param wejscie Wartosc sygnalu wejsciowego.
     * @return Wartosc sygnalu wyjsciowego.
     */
    virtual double symuluj(double wejscie) = 0;
};

#endif // OBIEKTSISO_H