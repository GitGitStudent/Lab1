#ifndef PETLA_UAR_H
#define PETLA_UAR_H

#include "ObiektSISO.h"
#include <vector>
#include <memory>

/**
 * @brief Typ wyliczeniowy reprezentuj�cy tryb pracy p�tli UAR.
 */
enum class TrybPetliUAR {
    Otwarta,   ///< P�tla otwarta � sygna� wej�ciowy bez sprz�enia zwrotnego.
    Zamknieta  ///< P�tla zamkni�ta � sygna� wej�ciowy uwzgl�dnia sprz�enie zwrotne.
};

/**
 * @brief Klasa abstrakcyjna reprezentuj�ca p�tl� UAR (Uk�ad Automatycznej Regulacji).
 *
 * Dziedziczy po klasie ObiektSISO. Umo�liwia dynamiczne dodawanie i usuwanie obiekt�w (np. regulatora, obiektu regulacji),
 * zmian� trybu pracy p�tli oraz symulacj� dzia�ania uk�adu.
 */
class PetlaUAR : public ObiektSISO {
public:
    /**
     * @brief Konstruktor inicjalizuj�cy tryb pracy p�tli.
     *
     * @param tryb Tryb pracy p�tli (domy�lnie: Otwarta).
     */
    PetlaUAR(TrybPetliUAR tryb = TrybPetliUAR::Otwarta)
        : trybPetli(tryb), poprzednieWyjscie(0.0) {
    }

    /**
     * @brief Wirtualny destruktor.
     */
    virtual ~PetlaUAR() = default;

    /**
     * @brief Ustawia nowy tryb pracy p�tli (otwarta lub zamkni�ta).
     *
     * @param tryb Nowy tryb pracy p�tli.
     */
    virtual void ustawTrybPetli(TrybPetliUAR tryb) = 0;

    /**
     * @brief Zwraca aktualny tryb pracy p�tli.
     *
     * @return Tryb pracy p�tli.
     */
    virtual TrybPetliUAR pobierzTrybPetli() const = 0;

    /**
     * @brief Dodaje nowy obiekt do p�tli.
     *
     * @param obiekt Wska�nik do obiektu dziedzicz�cego po ObiektSISO.
     */
    virtual void dodaj(std::shared_ptr<ObiektSISO> obiekt) = 0;

    /**
     * @brief Dodaje nowy obiekt do p�tli na okre�lonej pozycji.
     *
     * @param obiekt Wska�nik do obiektu dziedzicz�cego po ObiektSISO.
     * @param indeks Pozycja, na kt�r� zostanie dodany obiekt.
     */
    virtual void dodaj(std::shared_ptr<ObiektSISO> obiekt, size_t indeks) = 0;

    /**
     * @brief Usuwa obiekt z p�tli o podanym indeksie.
     *
     * @param indeks Indeks obiektu do usuni�cia.
     */
    virtual void usun(size_t indeks) = 0;

    /**
     * @brief Symuluje dzia�anie ca�ej p�tli UAR dla podanego wej�cia.
     *
     * @param wejscie Warto�� sygna�u wej�ciowego.
     * @return Warto�� sygna�u wyj�ciowego po przetworzeniu przez p�tl�.
     */
    virtual double symuluj(double wejscie) = 0;

    /**
     * @brief Zwraca liczb� obiekt�w sk�adowych w p�tli.
     *
     * @return Liczba obiekt�w (np. regulator�w, obiekt�w regulacji) w p�tli.
     */
    virtual size_t liczbaSkladnikow() const = 0;

protected:
    /**
     * @brief Wektor przechowuj�cy obiekty sk�adowe p�tli UAR.
     */
    std::vector<std::shared_ptr<ObiektSISO>> skladniki;

    /**
     * @brief Aktualny tryb pracy p�tli (otwarta lub zamkni�ta).
     */
    TrybPetliUAR trybPetli;

    /**
     * @brief Poprzednia warto�� wyj�cia p�tli (u�ywana w trybie zamkni�tym).
     */
    double poprzednieWyjscie;
};

#endif // PETLA_UAR_H
