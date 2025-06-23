#include "InterfejsUzytkownika.h"
#include <limits>
#include <iomanip>

InterfejsUzytkownika::InterfejsUzytkownika()
    : m_sygnal(nullptr), m_model(nullptr), m_regulator(nullptr), m_petla(nullptr) {
}

void InterfejsUzytkownika::uruchom()
{
    std::cout << "=== INTERFEJS UKLADU REGULACJI ===" << std::endl;

    bool kontynuuj = true;
    while (kontynuuj)
    {
        wyswietlMenu();
        int wybor = pobierzWybor(1, 7);

        switch (wybor)
        {
        case 1:
            konfigurujSygnal();
            break;
        case 2:
            konfigurujModelARX();
            break;
        case 3:
            konfigurujRegulatorPID();
            break;
        case 4:
            generujISymuluj();
            break;
        case 5:
            kontynuuj = false;
            std::cout << "Koniec programu." << std::endl;
            break;
        case 6:
            zapiszSygnalDoPliku();
            break;
        case 7:
            wczytajSygnalZPliku();
            break;
        }
        std::cout << std::endl;
    }
}
void InterfejsUzytkownika::wyswietlMenu()
{
    std::cout << "=== MENU GLOWNE ===" << std::endl;
    std::cout << "1. Konfiguruj sygnal wejœciowy" << std::endl;
    std::cout << "2. Konfiguruj model ARX" << std::endl;
    std::cout << "3. Konfiguruj regulator PID" << std::endl;
    std::cout << "4. Generuj i symuluj odpowiedz ukladu" << std::endl;
    std::cout << "5. Wyjscie" << std::endl;
    std::cout << "6. Zapisz sygnal do pliku" << std::endl;
    std::cout << "7. Wczytaj sygnal z pliku" << std::endl;
    std::cout << "Wybierz opcje (1-7): ";
}

int InterfejsUzytkownika::pobierzWybor(int min, int max)
{
    int wybor;
    while (true)
    {
        std::cin >> wybor;
        if (std::cin.fail() || wybor < min || wybor > max)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Nieprawidlowy wybor. Podaj liczbe z zakresu " << min << "-" << max << ": ";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return wybor;
        }
    }
}

double InterfejsUzytkownika::pobierzLiczbe(const std::string& prompt)
{
    double liczba;
    while (true)
    {
        std::cout << prompt;
        std::cin >> liczba;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Nieprawidlowa wartosc. Podaj liczbe: ";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return liczba;
        }
    }
}

int InterfejsUzytkownika::pobierzLiczbeCalkowita(const std::string& prompt)
{
    int liczba;
    while (true)
    {
        std::cout << prompt;
        std::cin >> liczba;
        if (std::cin.fail() || liczba < 0)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Nieprawidlowa wartosc. Podaj liczbe calkowita >= 0: ";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return liczba;
        }
    }
}

void InterfejsUzytkownika::konfigurujSygnal()
{
    std::unique_ptr<Sygnal> nowySygnal;
    bool kontynuuj = true;

    // Jeœli nie ma jeszcze sygna³u bazowego, wymuœ jego wybór
    if (!m_sygnal) {
        double poziom = pobierzLiczbe("Podaj poziom sygnalu bazowego: ");
        nowySygnal = std::make_unique<SygnalBazowy>(poziom);
    }
    else {
        // Jeœli ju¿ jest sygna³, mo¿na go dekorowaæ dalej
        nowySygnal = std::move(m_sygnal);
    }

    while (kontynuuj) {
        std::cout << "\n=== DODAJ DEKORATOR SYGNALU ===" << std::endl;
        std::cout << "1. Trojkatny" << std::endl;
        std::cout << "2. Prostokatny" << std::endl;
        std::cout << "3. Sinusoidalny" << std::endl;
        std::cout << "4. Szum bialy" << std::endl;
        std::cout << "5. Ograniczenie amplitudy" << std::endl;
        std::cout << "6. Zakoncz konfiguracje" << std::endl;
        std::cout << "Wybierz opcje (1-6): ";

        int wybor = pobierzWybor(1, 6);
        switch (wybor)
        {
        case 1: {
            double amplituda = pobierzLiczbe("Podaj amplitude: ");
            int okres = pobierzLiczbeCalkowita("Podaj okres (liczba probek): ");
            nowySygnal = std::make_unique<SygnalTrojkatny>(nowySygnal.release(), amplituda, okres);
            break;
        }
        case 2: {
            double amplituda = pobierzLiczbe("Podaj amplitude: ");
            int okres = pobierzLiczbeCalkowita("Podaj okres (liczba probek): ");
            double wypelnienie = pobierzLiczbe("Podaj wypelnienie (0.0 - 1.0): ");
            while (wypelnienie < 0.0 || wypelnienie > 1.0) {
                std::cout << "Wypelnienie musi byc w zakresie 0.0 - 1.0!\n";
                wypelnienie = pobierzLiczbe("Podaj wypelnienie (0.0 - 1.0): ");
            }
            nowySygnal = std::make_unique<SygnalProstokatny>(nowySygnal.release(), amplituda, okres, wypelnienie);
            break;
        }
        case 3: {
            double amplituda = pobierzLiczbe("Podaj amplitude: ");
            double czestotliwosc = pobierzLiczbe("Podaj czestotliwosc [Hz]: ");
            double T = pobierzLiczbe("Podaj okres probkowania T [s]: ");
            nowySygnal = std::make_unique<SygnalSinusoidalny>(nowySygnal.release(), amplituda, czestotliwosc, T);
            break;
        }
        case 4: {
            double amplituda = pobierzLiczbe("Podaj amplitude szumu: ");
            nowySygnal = std::make_unique<SygnalBialySzum>(nowySygnal.release(), amplituda);
            break;
        }
        case 5: {
            double maxAmp = pobierzLiczbe("Podaj maksymalna amplitude: ");
            nowySygnal = std::make_unique<OgraniczenieAmplitudy>(nowySygnal.release(), maxAmp);
            break;
        }
        case 6:
            kontynuuj = false;
            break;
        }
    }

    m_sygnal = std::move(nowySygnal);
    std::cout << "Sygnal skonfigurowany.\n";
}

void InterfejsUzytkownika::zapiszSygnalDoPliku()
{
    if (!m_sygnal) {
        std::cout << "Najpierw skonfiguruj sygnal!" << std::endl;
        return;
    }
    std::string nazwaPliku;
    std::cout << "Podaj nazwê pliku do zapisu: ";
    std::getline(std::cin >> std::ws, nazwaPliku);

    std::ofstream out(nazwaPliku);
    if (!out) {
        std::cout << "Nie mozna otworzyc pliku do zapisu!" << std::endl;
        return;
    }
    if (m_sygnal) {
    m_sygnal->serialize(out);
    out << "END_SYGNAL\n";
    }
    if (m_model) {
        m_model->serialize(out);
        out << "END_MODEL\n";
    }

    if (m_regulator) {
        m_regulator->serialize(out);
        out << "END_PID\n";
    }

    std::cout << "Sygnal zapisany do pliku: " << nazwaPliku << std::endl;
}


void InterfejsUzytkownika::wczytajSygnalZPliku()
{
    std::string nazwaPliku;
    std::cout << "Podaj nazwê pliku do odczytu: ";
    std::getline(std::cin >> std::ws, nazwaPliku);

    std::ifstream in(nazwaPliku);
    if (!in) {
        std::cout << "Nie mozna otworzyc pliku do odczytu!" << std::endl;
        return;
    }

    // Wczytanie sygna³u
    Sygnal* wczytany = deserializeCalySygnal(in);
    if (!wczytany) {
        std::cout << "Blad podczas deserializacji sygna³u!" << std::endl;
        return;
    }

    m_sygnal.reset(wczytany);

    // Wczytanie modelu ARX
    m_model = ModelARX::deserialize(in);
    if (m_model) {
        std::cout << "[DEBUG] Model ARX wczytany z pliku" << std::endl;
    }
    else {
        std::cout << "[DEBUG] Nie uda³o siê wczytaæ modelu ARX" << std::endl;
    }

    m_regulator = RegulatorPID::deserialize(in);
    if (m_regulator) {
        std::cout << "[DEBUG] Regulator PID wczytany z pliku" << std::endl;
    }
    else {
        std::cout << "[DEBUG] Nie uda³o siê wczytaæ regulatora PID" << std::endl;
    }

    std::cout << "Sygnal i model wczytane z pliku: " << nazwaPliku << std::endl;
}

void InterfejsUzytkownika::konfigurujModelARX()
{
    std::cout << "\n=== KONFIGURACJA MODELU ARX ===" << std::endl;
    int nA = pobierzLiczbeCalkowita("Podaj rzad mianownika (liczba wspolczynnikow A): ");
    int nB = pobierzLiczbeCalkowita("Podaj rzad licznika (liczba wspolczynnikow B): ");
    std::vector<double> wspA(nA), wspB(nB);
    for (int i = 0; i < nA; ++i)
        wspA[i] = pobierzLiczbe("A[" + std::to_string(i) + "]: ");
    for (int i = 0; i < nB; ++i)
        wspB[i] = pobierzLiczbe("B[" + std::to_string(i) + "]: ");
    int opoznienie = pobierzLiczbeCalkowita("Podaj opoznienie: ");
    double mocZaklocenia = pobierzLiczbe("Podaj moc zaklocenia (0 = brak): ");

    m_model = std::make_shared<ModelARX>(wspA, wspB, opoznienie, mocZaklocenia);
    std::cout << "Model ARX skonfigurowany.\n";
}

void InterfejsUzytkownika::konfigurujRegulatorPID()
{
    std::cout << "\n=== KONFIGURACJA REGULATORA PID ===" << std::endl;
    double k = pobierzLiczbe("Podaj wzmocnienie k: ");
    double Ti = pobierzLiczbe("Podaj czas calkowania Ti: ");
    double Td = pobierzLiczbe("Podaj czas rozniczkowania Td: ");

    m_regulator = std::make_shared<RegulatorPID>(k, Ti, Td);
    std::cout << "Regulator PID skonfigurowany.\n";
}

void InterfejsUzytkownika::generujISymuluj()
{
    if (!m_sygnal || !m_model || !m_regulator) {
        std::cout << "Najpierw skonfiguruj sygnal, model ARX i regulator PID!" << std::endl;
        return;
    }

    int liczbaProbek = pobierzLiczbeCalkowita("Podaj liczbe probek do symulacji: ");
    std::vector<double> wejscie(liczbaProbek, 0.0);
    std::vector<double> wyjscie(liczbaProbek, 0.0);

    for (int k = 0; k < liczbaProbek; ++k) {
        wejscie[k] = m_sygnal->symuluj(k);
    }

    // Prosta pêtla zamkniêta: RegulatorPID -> ModelARX
    double poprzednieWyjscie = 0.0;
    for (int k = 0; k < liczbaProbek; ++k) {
        double uchyb = wejscie[k] - poprzednieWyjscie;
        double sterowanie = m_regulator->symuluj(uchyb);
        wyjscie[k] = m_model->symuluj(sterowanie);
        poprzednieWyjscie = wyjscie[k];
    }

    std::cout << "\nWyniki symulacji (krok, zadana, wyjscie):\n";
    std::cout << std::fixed << std::setprecision(4);
    for (int k = 0; k < liczbaProbek; ++k) {
        std::cout << std::setw(4) << k
            << std::setw(10) << wejscie[k]
            << std::setw(10) << wyjscie[k] << std::endl;
    }
}
