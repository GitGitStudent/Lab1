#ifndef PETLA_RONWOLEGHA_H
#define PETLA_RONWOLEGHA_H

#include "PetlaUAR.h"

class PetlaRownolegla : public PetlaUAR {
public:
    using PetlaUAR::PetlaUAR;

    void ustawTrybPetli(TrybPetliUAR tryb) override;
    TrybPetliUAR pobierzTrybPetli() const override;

    void dodaj(std::shared_ptr<ObiektSISO> obiekt) override;
    void dodaj(std::shared_ptr<ObiektSISO> obiekt, size_t indeks) override;
    void usun(size_t indeks) override;
    size_t liczbaSkladnikow() const override;

    double symuluj(double wejscie) override;
};

#endif // PETLA_RONWOLEGHA_H
