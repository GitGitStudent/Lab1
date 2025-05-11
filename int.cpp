#include <iostream>
#include <fstream>
#include "SygnalBazowy.h"
#include "DekoratoryKonkretne.h"
#include "SygnalKonkretny.h"
#include "DeserializedCalySygnal.h"

int main() {
    // Tworzenie zagnie¿d¿onych dekoratorów
    Sygnal* sygnal = new SygnalSinusoidalny(
        new SygnalTrojkatny(
            new SygnalBialySzum(
                new SygnalBazowy(5.0),
                2.0),
            3.0, 15),
        5.0, 10, 0.5);
    /*
    // Dodawanie dekoratorów dynamicznie
    sygnal->dodajDekorator(new SygnalBialySzum(nullptr, 1.0)); // Dodanie kolejnego bia³ego szumu
    sygnal->dodajDekorator(new SygnalTrojkatny(nullptr, 2.0, 20)); // Dodanie kolejnego sygna³u trójk¹tnego
    
    */
    // Tworzenie sygna³u bazowego
    //Sygnal* sygnal = new SygnalBazowy(2.0);

    // Tworzenie dekoratora
    //sygnal = new SygnalTrojkatny(sygnal, 2.0, 10);
    
    // Dodanie sygna³u bazowego do dekoratora
    //sygnal = new SygnalTrojkatny(sygnal, 2.0, 10);

    // Symulacja sygna³u
    for (int n = 0; n < 100; ++n) {
        std::cout << "n = " << n << ", sygnal = " << sygnal->symuluj(n) << std::endl;
    }
    // Serializacja
    std::ofstream outFile("sygnal.txt");
    sygnal->serialize(outFile);
    outFile.close();

    // Deserializacja
    std::ifstream inFile("sygnal.txt");
    Sygnal* deserializedSygnal = deserializeCalySygnal(inFile);
    inFile.close();


    /*// Deserializacja
    std::ifstream inFile("sygnal.txt");
    Sygnal* deserializedSygnal = new SygnalBazowy(0.0); // Tymczasowy obiekt
    deserializedSygnal->deserialize(inFile);
    inFile.close();

     //Symulacja sygna³u po deserializacji
     std::cout << "Symulacja sygnalu po deserializacji:\n";
    for (int n = 0; n < 100; ++n) {
        std::cout << "n = " << n << ", sygnal = " << deserializedSygnal->symuluj(n) << std::endl;
    }*/
    // Symulacja sygna³u po deserializacji
    std::cout << "Symulacja sygna³u po deserializacji:\n";
    for (int n = 0; n < 100; ++n) {
        std::cout << "n = " << n << ", sygnal = " << deserializedSygnal->symuluj(n) << std::endl;
    }
    // Zwolnienie pamiêci
    
    delete sygnal;
    delete deserializedSygnal;

    return 0;
}


