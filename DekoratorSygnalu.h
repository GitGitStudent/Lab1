#ifndef DEKORATORSYGNALU_H
#define DEKORATORSYGNALU_H

#include "Sygnal.h"

/**
 * @file DekoratorSygnalu.h
 * @brief Deklaracja abstrakcyjnego dekoratora sygna�u.
 */

 /**
  * @class DekoratorSygnalu
  * @brief Abstrakcyjna klasa dekoratora dla sygna��w.
  *
  * Umo�liwia rozszerzanie funkcjonalno�ci obiekt�w klasy Sygnal
  * bez modyfikowania ich struktury, zgodnie z wzorcem projektowym Dekorator.
  */
class DekoratorSygnalu : public Sygnal {
protected:
    /**
     * @brief Wska�nik na dekorowany obiekt typu Sygnal.
     */
    Sygnal* komponent;

public:
    /**
     * @brief Konstruktor domy�lny inicjalizuj�cy komponent jako nullptr.
     */
    DekoratorSygnalu() : komponent(nullptr) {}

    /**
     * @brief Wirtualny destruktor usuwaj�cy zagnie�d�ony komponent.
     */
    virtual ~DekoratorSygnalu() {
        delete komponent;
    }
};

#endif // DEKORATORSYGNALU_H
