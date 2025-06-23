#ifndef PETLA_RONWOLEGHA_H
#define PETLA_RONWOLEGHA_H

#include "PetlaUAR.h"

/**
 * @brief Klasa reprezentuj¹ca równoleg³e po³¹czenie obiektów w pêtli UAR.
 *
 * Dziedziczy po klasie PetlaUAR i implementuje jej funkcje w kontekœcie uk³adu równoleg³ego.
 * Obiekty dodane do pêtli s¹ przetwarzane równolegle – wejœcie trafia do wszystkich,
 * a ich wyjœcia s¹ sumowane.
 */
class PetlaRownolegla : public PetlaUAR {
public:
    /**
     * @brief Konstruktor dziedzicz¹cy z klasy PetlaUAR.
     *
     * Pozwala na inicjalizacjê trybu pracy pêtli (Otwarta/Zamknieta).
     */
    using PetlaUAR::PetlaUAR;

    /**
     * @brief Ustawia tryb pracy pêtli (otwarta lub zamkniêta).
     *
     * @param tryb Nowy tryb pracy pêtli.
     */
    void ustawTrybPetli(TrybPetliUAR tryb) override;

    /**
     * @brief Zwraca aktualny tryb pracy pêtli.
     *
     * @return Tryb pracy pêtli.
     */
    TrybPetliUAR pobierzTrybPetli() const override;

    /**
     * @brief Dodaje nowy obiekt do koñca pêtli.
     *
     * @param obiekt WskaŸnik do obiektu dziedzicz¹cego po ObiektSISO.
     */
    void dodaj(std::shared_ptr<ObiektSISO> obiekt) override;

    /**
     * @brief Dodaje nowy obiekt w okreœlone miejsce w pêtli.
     *
     * @param obiekt WskaŸnik do obiektu dziedzicz¹cego po ObiektSISO.
     * @param indeks Indeks, pod którym ma zostaæ dodany obiekt.
     */
    void dodaj(std::shared_ptr<ObiektSISO> obiekt, size_t indeks) override;

    /**
     * @brief Usuwa obiekt z pêtli o podanym indeksie.
     *
     * @param indeks Indeks obiektu do usuniêcia.
     */
    void usun(size_t indeks) override;

    /**
     * @brief Zwraca liczbê sk³adników w pêtli.
     *
     * @return Liczba obiektów dodanych do pêtli.
     */
    size_t liczbaSkladnikow() const override;

    /**
     * @brief Symuluje dzia³anie pêtli równoleg³ej.
     *
     * W trybie otwartym wejœcie jest podawane do wszystkich sk³adników, a ich wyjœcia s¹ sumowane.
     * W trybie zamkniêtym sygna³ steruj¹cy mo¿e zale¿eæ od poprzedniego wyjœcia.
     *
     * @param wejscie Sygna³ wejœciowy.
     * @return Zsumowany sygna³ wyjœciowy po przejœciu przez wszystkie sk³adniki.
     */
    double symuluj(double wejscie) override;
};

#endif // PETLA_RONWOLEGHA_H
