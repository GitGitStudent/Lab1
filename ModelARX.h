  #ifndef MODELARX_H
#define MODELARX_H

#include "ObiektSISO.h"
#include <vector>
#include <deque>
#include <random>
#include <string>

/**
 * @brief Klasa reprezentujaca model ARX.
 *
 * Model ARX sluzy do symulacji odpowiedzi ukladu dynamicznego z zakloceniami.
 */
class ModelARX : public ObiektSISO {
private:
    /**
     * @brief Wspolczynniki wielomianu A (mianownik).
     */
    std::vector<double> wspA;

    /**
     * @brief Wspolczynniki wielomianu B (licznik).
     */
    std::vector<double> wspB;

    /**
     * @brief Pamiec sygnalow wejsciowych.
     */
    std::deque<double> pamiecWejsc;

    /**
     * @brief Pamiec sygnalow wyjsciowych.
     */
    std::deque<double> pamiecWyjsc;

    /**
     * @brief Opoznienie transportowe.
     */
    unsigned int opoznienie;

    /**
     * @brief Moc zaklocenia (np. odchylenie standardowe).
     */
    double mocZaklocenia;

    /**
     * @brief Generator liczb losowych.
     */
    std::default_random_engine generator;

    /**
     * @brief Rozklad normalny zaklocen.
     */
    std::normal_distribution<double>* rozkladZaklocen;

public:
    /**
     * @brief Konstruktor tworzacy model ARX na podstawie wspolczynnikow i parametrow.
     *
     * @param wspA Wspolczynniki wielomianu A.
     * @param wspB Wspolczynniki wielomianu B.
     * @param opoznienie Opoznienie transportowe.
     * @param mocZaklocenia Moc zaklocenia.
     */
    ModelARX(const std::vector<double>& wspA, const std::vector<double>& wspB, int opoznienie, double mocZaklocenia);

    /**
     * @brief Konstruktor deserializujacy model ARX z pliku.
     *
     * @param filePath Sciezka do pliku z zapisanym modelem.
     */
    ModelARX(std::istream& in);

    /**
    * @brief Deserializuje obiekt ModelARX ze strumienia wejściowego.
     *
    * Tworzy nowy obiekt typu ModelARX na podstawie danych zapisanych w strumieniu,
    * takich jak parametry modelu czy liczba opóźnień.
    *
    * @param in Strumień wejściowy zawierający dane obiektu ModelARX.
    * @return Wskaźnik do nowo utworzonego obiektu ModelARX.
    */
    static std::shared_ptr<ModelARX> deserialize(std::istream& in);
    /**
     * @brief Destruktor zwalniajacy zasoby.
     */
    ~ModelARX();

    /**
     * @brief Symuluje odpowiedz modelu ARX na podstawie sygnalu wejsciowego.
     *
     * @param wejscie Wartosc sygnalu wejsciowego.
     * @return Wartosc sygnalu wyjsciowego.
     */
    double symuluj(double wejscie) override;

    /**
     * @brief Serializuje model ARX do pliku.
     *
     * @param filePath Sciezka do pliku, do ktorego zostanie zapisany model.
     */
    void serialize(std::ofstream& out) const;

    
};

#endif // MODELARX_H