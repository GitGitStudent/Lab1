#ifndef PETLA_SZEREGOWA_H
#define PETLA_SZEREGOWA_H

#include "PetlaUAR.h"

/**
 * @brief Klasa reprezentuj�ca szeregowe po��czenie obiekt�w w p�tli UAR.
 *
 * Dziedziczy po klasie PetlaUAR i implementuje jej funkcje w kontek�cie uk�adu szeregowego.
 * Obiekty dodane do p�tli s� przetwarzane kolejno � wyj�cie jednego jest wej�ciem kolejnego.
 */
class PetlaSzeregowa : public PetlaUAR {
public:
    /**
     * @brief Konstruktor dziedzicz�cy z klasy PetlaUAR.
     *
     * Pozwala na inicjalizacj� trybu pracy p�tli (Otwarta/Zamknieta).
     */
    using PetlaUAR::PetlaUAR;

    /**
     * @brief Ustawia tryb pracy p�tli (otwarta lub zamkni�ta).
     *
     * @param tryb Nowy tryb pracy p�tli.
     */
    void ustawTrybPetli(TrybPetliUAR tryb) override;

    /**
     * @brief Zwraca aktualny tryb pracy p�tli.
     *
     * @return Tryb pracy p�tli.
     */
    TrybPetliUAR pobierzTrybPetli() const override;

    /**
     * @brief Dodaje nowy obiekt do ko�ca p�tli.
     *
     * @param obiekt Wska�nik do obiektu dziedzicz�cego po ObiektSISO.
     */
    void dodaj(std::shared_ptr<ObiektSISO> obiekt) override;

    /**
     * @brief Dodaje nowy obiekt w okre�lone miejsce w p�tli.
     *
     * @param obiekt Wska�nik do obiektu dziedzicz�cego po ObiektSISO.
     * @param indeks Indeks, pod kt�rym ma zosta� dodany obiekt.
     */
    void dodaj(std::shared_ptr<ObiektSISO> obiekt, size_t indeks) override;

    /**
     * @brief Usuwa obiekt z p�tli o podanym indeksie.
     *
     * @param indeks Indeks obiektu do usuni�cia.
     */
    void usun(size_t indeks) override;

    /**
     * @brief Zwraca liczb� sk�adnik�w w p�tli.
     *
     * @return Liczba obiekt�w dodanych do p�tli.
     */
    size_t liczbaSkladnikow() const override;

    /**
     * @brief Symuluje dzia�anie p�tli szeregowej.
     *
     * W trybie otwartym sygna� wej�ciowy przechodzi przez wszystkie sk�adniki szeregowo.
     * W trybie zamkni�tym poprzednie wyj�cie jest traktowane jako sprz�enie zwrotne.
     *
     * @param wejscie Sygna� wej�ciowy.
     * @return Sygna� wyj�ciowy po przej�ciu przez wszystkie sk�adniki.
     */
    double symuluj(double wejscie) override;
};

#endif // PETLA_SZEREGOWA_H
