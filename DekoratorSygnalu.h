#ifndef DEKORATORSYGNALU_H
#define DEKORATORSYGNALU_H

#include "Sygnal.h"

/**
 * @file DekoratorSygnalu.h
 * @brief Deklaracja abstrakcyjnego dekoratora sygna³u.
 */

 /**
  * @class DekoratorSygnalu
  * @brief Abstrakcyjna klasa dekoratora dla sygna³ów.
  *
  * Umo¿liwia rozszerzanie funkcjonalnoœci obiektów klasy Sygnal
  * bez modyfikowania ich struktury, zgodnie z wzorcem projektowym Dekorator.
  */
class DekoratorSygnalu : public Sygnal {
protected:
    /**
     * @brief WskaŸnik na dekorowany obiekt typu Sygnal.
     */
    Sygnal* komponent;

public:
    /**
     * @brief Konstruktor domyœlny inicjalizuj¹cy komponent jako nullptr.
     */
    DekoratorSygnalu() : komponent(nullptr) {}

    /**
     * @brief Wirtualny destruktor usuwaj¹cy zagnie¿d¿ony komponent.
     */
    virtual ~DekoratorSygnalu() {
        delete komponent;
    }
};

#endif // DEKORATORSYGNALU_H
