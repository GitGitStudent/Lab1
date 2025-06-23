#ifndef INTERFEJSUZYTKOWNIKA_H
#define INTERFEJSUZYTKOWNIKA_H

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include "SygnalBazowy.h"
#include "SygnalKonkretny.h"
#include "DekoratoryKonkretne.h"
#include "DeserializedCalySygnal.h"
#include "ModelARX.h"
#include "RegulatorPID.h"
#include "PetlaSzeregowa.h"
#include "PetlaRownolegla.h"

/**
 * @brief Klasa reprezentuj¹ca interfejs u¿ytkownika aplikacji.
 *
 * Umo¿liwia konfiguracjê sygna³u, modelu ARX oraz regulatora PID,
 * a tak¿e ich symulacjê i zapis/odczyt sygna³ów do/z pliku.
 */
class InterfejsUzytkownika
{
private:
    /**
     * @brief Obiekt sygna³u wybranego przez u¿ytkownika.
     */
    std::unique_ptr<Sygnal> m_sygnal;

    /**
     * @brief WskaŸnik do modelu ARX.
     */
    std::shared_ptr<ModelARX> m_model;

    /**
     * @brief WskaŸnik do regulatora PID.
     */
    std::shared_ptr<RegulatorPID> m_regulator;

    /**
     * @brief WskaŸnik do pêtli szeregowej (struktur UAR).
     */
    std::shared_ptr<PetlaSzeregowa> m_petla;

    /**
     * @brief Wyœwietla menu g³ówne.
     */
    void wyswietlMenu();

    /**
     * @brief Konfiguruje sygna³ u¿ytkownika (bazowy + dekoratory).
     */
    void konfigurujSygnal();

    /**
     * @brief Konfiguruje model ARX.
     */
    void konfigurujModelARX();

    /**
     * @brief Konfiguruje regulator PID.
     */
    void konfigurujRegulatorPID();

    /**
     * @brief Generuje sygna³, przeprowadza symulacjê i wyœwietla wyniki.
     */
    void generujISymuluj();

    /**
     * @brief Pobiera wybór liczbowy od u¿ytkownika z okreœlonego zakresu.
     *
     * @param min Minimalna wartoœæ wyboru.
     * @param max Maksymalna wartoœæ wyboru.
     * @return Wybrana liczba ca³kowita.
     */
    int pobierzWybor(int min, int max);

    /**
     * @brief Pobiera liczbê rzeczywist¹ od u¿ytkownika.
     *
     * @param prompt Komunikat wyœwietlany u¿ytkownikowi.
     * @return Wprowadzona liczba rzeczywista.
     */
    double pobierzLiczbe(const std::string& prompt);

    /**
     * @brief Pobiera liczbê ca³kowit¹ od u¿ytkownika.
     *
     * @param prompt Komunikat wyœwietlany u¿ytkownikowi.
     * @return Wprowadzona liczba ca³kowita.
     */
    int pobierzLiczbeCalkowita(const std::string& prompt);

public:
    /**
     * @brief Konstruktor domyœlny interfejsu u¿ytkownika.
     */
    InterfejsUzytkownika();

    /**
     * @brief Zapisuje aktualny sygna³ do pliku.
     */
    void zapiszSygnalDoPliku();

    /**
     * @brief Wczytuje sygna³ z pliku.
     */
    void wczytajSygnalZPliku();

    /**
     * @brief Uruchamia g³ówn¹ pêtlê programu.
     */
    void uruchom();
};

#endif // INTERFEJSUZYTKOWNIKA_H
