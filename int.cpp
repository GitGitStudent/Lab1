/*
#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "PetlaSzeregowa.h"
#include "PetlaRownolegla.h"
#include "ModelARX.h"
#include "RegulatorPID.h"
#include "SygnalBazowy.h"
#include "SygnalKonkretny.h"

int main() {
    std::vector<double> wspA = { -0.4, 0.2 };
    std::vector<double> wspB = { 0.6, 0.3 };
    int opoznienie = 0;
    double mocZaklocenia = 0.0;

    auto regulator = std::make_shared<RegulatorPID>(0.5, 10.0, 0.1);
    auto model1 = std::make_shared<ModelARX>(wspA, wspB, opoznienie, mocZaklocenia);
    auto model2 = std::make_shared<ModelARX>(wspA, wspB, opoznienie, mocZaklocenia);
    auto model3 = std::make_shared<ModelARX>(wspA, wspB, opoznienie, mocZaklocenia);

    // Kompozyt równoleg³y: ModelARX (model1) || ModelARX (model2)
    auto rownolegleARX = std::make_shared<PetlaRownolegla>(TrybPetliUAR::Otwarta);
    rownolegleARX->dodaj(model1);
    rownolegleARX->dodaj(model2);

    // Kompozyt szeregowy: RegulatorPID -> (ModelARX || ModelARX), zamkniêta pêtla
    auto szeregowa = std::make_shared<PetlaSzeregowa>(TrybPetliUAR::Zamknieta);
    szeregowa->dodaj(regulator);
    szeregowa->dodaj(rownolegleARX);

    // Dodajemy model3 szeregowo na koñcu
    szeregowa->dodaj(model3);

    // Tworzenie zagnie¿d¿onych dekoratorów sygna³u
    Sygnal* sygnal = new SygnalTrojkatny(
        new SygnalBazowy(5.0),
        3.0, 15);

    std::vector<double> wejscie(200, 0.0);
    for (size_t k = 0; k < wejscie.size(); ++k) {
        wejscie[k] = sygnal->symuluj(static_cast<int>(k));
    }

    // Symulacja z model3
    std::vector<double> wyjscie_z_model3(200, 0.0);
    std::cout << "\nSymulacja z dodatkowym modelem szeregowo:\n";
    std::cout << std::setw(4) << "krok"
        << std::setw(10) << "zadana"
        << std::setw(15) << "wyjscie+model3" << std::endl;
    for (size_t k = 0; k < wejscie.size(); ++k) {
        wyjscie_z_model3[k] = szeregowa->symuluj(wejscie[k]);
        std::cout << std::setw(4) << k
            << std::setw(10) << wejscie[k]
            << std::setw(15) << wyjscie_z_model3[k] << std::endl;
    }

    // Usuñ model3 (ostatni sk³adnik szeregowej pêtli)
    szeregowa->usun(szeregowa->liczbaSkladnikow() - 1);

    // Symulacja bez model3
    std::vector<double> wyjscie_bez_model3(200, 0.0);
    std::cout << "\nSymulacja po usuniêciu modelu szeregowego:\n";
    std::cout << std::setw(4) << "krok"
        << std::setw(10) << "zadana"
        << std::setw(15) << "wyjscie" << std::endl;
    for (size_t k = 0; k < wejscie.size(); ++k) {
        wyjscie_bez_model3[k] = szeregowa->symuluj(wejscie[k]);
        std::cout << std::setw(4) << k
            << std::setw(10) << wejscie[k]
            << std::setw(15) << wyjscie_bez_model3[k] << std::endl;
    }

    delete sygnal;
    return 0;
}
*/
#include "InterfejsUzytkownika.h"

int main() {
    InterfejsUzytkownika interfejs;
    interfejs.uruchom();
    return 0;
}