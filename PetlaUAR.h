#ifndef PETLA_UAR_H
#define PETLA_UAR_H

#include "ObiektSISO.h"
#include <vector>
#include <memory>

/**
 * @brief Typ wyliczeniowy reprezentuj¹cy tryb pracy pêtli UAR.
 */
enum class TrybPetliUAR {
    Otwarta,   ///< Pêtla otwarta – sygna³ wejœciowy bez sprzê¿enia zwrotnego.
    Zamknieta  ///< Pêtla zamkniêta – sygna³ wejœciowy uwzglêdnia sprzê¿enie zwrotne.
};

/**
 * @brief Klasa abstrakcyjna reprezentuj¹ca pêtlê UAR (Uk³ad Automatycznej Regulacji).
 *
 * Dziedziczy po klasie ObiektSISO. Umo¿liwia dynamiczne dodawanie i usuwanie obiektów (np. regulatora, obiektu regulacji),
 * zmianê trybu pracy pêtli oraz symulacjê dzia³ania uk³adu.
 */
class PetlaUAR : public ObiektSISO {
public:
    /**
     * @brief Konstruktor inicjalizuj¹cy tryb pracy pêtli.
     *
     * @param tryb Tryb pracy pêtli (domyœlnie: Otwarta).
     */
    PetlaUAR(TrybPetliUAR tryb = TrybPetliUAR::Otwarta)
        : trybPetli(tryb), poprzednieWyjscie(0.0) {
    }

    /**
     * @brief Wirtualny destruktor.
     */
    virtual ~PetlaUAR() = default;

    /**
     * @brief Ustawia nowy tryb pracy pêtli (otwarta lub zamkniêta).
     *
     * @param tryb Nowy tryb pracy pêtli.
     */
    virtual void ustawTrybPetli(TrybPetliUAR tryb) = 0;

    /**
     * @brief Zwraca aktualny tryb pracy pêtli.
     *
     * @return Tryb pracy pêtli.
     */
    virtual TrybPetliUAR pobierzTrybPetli() const = 0;

    /**
     * @brief Dodaje nowy obiekt do pêtli.
     *
     * @param obiekt WskaŸnik do obiektu dziedzicz¹cego po ObiektSISO.
     */
    virtual void dodaj(std::shared_ptr<ObiektSISO> obiekt) = 0;

    /**
     * @brief Dodaje nowy obiekt do pêtli na okreœlonej pozycji.
     *
     * @param obiekt WskaŸnik do obiektu dziedzicz¹cego po ObiektSISO.
     * @param indeks Pozycja, na któr¹ zostanie dodany obiekt.
     */
    virtual void dodaj(std::shared_ptr<ObiektSISO> obiekt, size_t indeks) = 0;

    /**
     * @brief Usuwa obiekt z pêtli o podanym indeksie.
     *
     * @param indeks Indeks obiektu do usuniêcia.
     */
    virtual void usun(size_t indeks) = 0;

    /**
     * @brief Symuluje dzia³anie ca³ej pêtli UAR dla podanego wejœcia.
     *
     * @param wejscie Wartoœæ sygna³u wejœciowego.
     * @return Wartoœæ sygna³u wyjœciowego po przetworzeniu przez pêtlê.
     */
    virtual double symuluj(double wejscie) = 0;

    /**
     * @brief Zwraca liczbê obiektów sk³adowych w pêtli.
     *
     * @return Liczba obiektów (np. regulatorów, obiektów regulacji) w pêtli.
     */
    virtual size_t liczbaSkladnikow() const = 0;

protected:
    /**
     * @brief Wektor przechowuj¹cy obiekty sk³adowe pêtli UAR.
     */
    std::vector<std::shared_ptr<ObiektSISO>> skladniki;

    /**
     * @brief Aktualny tryb pracy pêtli (otwarta lub zamkniêta).
     */
    TrybPetliUAR trybPetli;

    /**
     * @brief Poprzednia wartoœæ wyjœcia pêtli (u¿ywana w trybie zamkniêtym).
     */
    double poprzednieWyjscie;
};

#endif // PETLA_UAR_H
