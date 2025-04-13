#ifndef MODELARX_H
#define MODELARX_H

#include "ObiektSISO.h"
#include <vector>
#include <deque>
#include <random>
#include <string>

class ModelARX : public ObiektSISO {
private:
    std::vector<double> wspA; // Współczynniki wielomianu A (mianownik)
    std::vector<double> wspB; // Współczynniki wielomianu B (licznik)
    std::deque<double> pamiecWejsc; // Pamięć sygnałów wejściowych
    std::deque<double> pamiecWyjsc; // Pamięć sygnałów wyjściowych
    int opoznienie; // Opóźnienie transportowe
    double mocZaklocenia; // Moc zakłócenia (np. odchylenie standardowe)
    std::default_random_engine generator;
    std::normal_distribution<double>* rozkladZaklocen;

public:
    // Konstruktor
    ModelARX(const std::vector<double>& wspA, const std::vector<double>& wspB, int opoznienie, double mocZaklocenia);
    
    // Konstruktor deserializujący
    ModelARX(const std::string& filePath);

    // Destruktor
    ~ModelARX();

    // Implementacja metody symuluj
    double symuluj(double wejscie) override;

    // Metoda serializacji
    void serialize(const std::string& filePath) const;
};

#endif // MODELARX_H
