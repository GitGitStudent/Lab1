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
 * @brief Klasa reprezentuj�ca interfejs u�ytkownika aplikacji.
 *
 * Umo�liwia konfiguracj� sygna�u, modelu ARX oraz regulatora PID,
 * a tak�e ich symulacj� i zapis/odczyt sygna��w do/z pliku.
 */
class InterfejsUzytkownika
{
private:
    /**
     * @brief Obiekt sygna�u wybranego przez u�ytkownika.
     */
    std::unique_ptr<Sygnal> m_sygnal;

    /**
     * @brief Wska�nik do modelu ARX.
     */
    std::shared_ptr<ModelARX> m_model;

    /**
     * @brief Wska�nik do regulatora PID.
     */
    std::shared_ptr<RegulatorPID> m_regulator;

    /**
     * @brief Wska�nik do p�tli szeregowej (struktur UAR).
     */
    std::shared_ptr<PetlaSzeregowa> m_petla;

    /**
     * @brief Wy�wietla menu g��wne.
     */
    void wyswietlMenu();

    /**
     * @brief Konfiguruje sygna� u�ytkownika (bazowy + dekoratory).
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
     * @brief Generuje sygna�, przeprowadza symulacj� i wy�wietla wyniki.
     */
    void generujISymuluj();

    /**
     * @brief Pobiera wyb�r liczbowy od u�ytkownika z okre�lonego zakresu.
     *
     * @param min Minimalna warto�� wyboru.
     * @param max Maksymalna warto�� wyboru.
     * @return Wybrana liczba ca�kowita.
     */
    int pobierzWybor(int min, int max);

    /**
     * @brief Pobiera liczb� rzeczywist� od u�ytkownika.
     *
     * @param prompt Komunikat wy�wietlany u�ytkownikowi.
     * @return Wprowadzona liczba rzeczywista.
     */
    double pobierzLiczbe(const std::string& prompt);

    /**
     * @brief Pobiera liczb� ca�kowit� od u�ytkownika.
     *
     * @param prompt Komunikat wy�wietlany u�ytkownikowi.
     * @return Wprowadzona liczba ca�kowita.
     */
    int pobierzLiczbeCalkowita(const std::string& prompt);

public:
    /**
     * @brief Konstruktor domy�lny interfejsu u�ytkownika.
     */
    InterfejsUzytkownika();

    /**
     * @brief Zapisuje aktualny sygna� do pliku.
     */
    void zapiszSygnalDoPliku();

    /**
     * @brief Wczytuje sygna� z pliku.
     */
    void wczytajSygnalZPliku();

    /**
     * @brief Uruchamia g��wn� p�tl� programu.
     */
    void uruchom();
};

#endif // INTERFEJSUZYTKOWNIKA_H
