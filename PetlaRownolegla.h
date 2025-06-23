#ifndef PETLA_RONWOLEGHA_H
#define PETLA_RONWOLEGHA_H

#include "PetlaUAR.h"

/**
 * @brief Klasa reprezentuj�ca r�wnoleg�e po��czenie obiekt�w w p�tli UAR.
 *
 * Dziedziczy po klasie PetlaUAR i implementuje jej funkcje w kontek�cie uk�adu r�wnoleg�ego.
 * Obiekty dodane do p�tli s� przetwarzane r�wnolegle � wej�cie trafia do wszystkich,
 * a ich wyj�cia s� sumowane.
 */
class PetlaRownolegla : public PetlaUAR {
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
     * @brief Symuluje dzia�anie p�tli r�wnoleg�ej.
     *
     * W trybie otwartym wej�cie jest podawane do wszystkich sk�adnik�w, a ich wyj�cia s� sumowane.
     * W trybie zamkni�tym sygna� steruj�cy mo�e zale�e� od poprzedniego wyj�cia.
     *
     * @param wejscie Sygna� wej�ciowy.
     * @return Zsumowany sygna� wyj�ciowy po przej�ciu przez wszystkie sk�adniki.
     */
    double symuluj(double wejscie) override;
};

#endif // PETLA_RONWOLEGHA_H
