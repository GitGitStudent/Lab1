#ifndef OBIEKTSISO_H
#define OBIEKTSISO_H

class ObiektSISO {
public:
    virtual ~ObiektSISO() = default;

    // Metoda wirtualna do symulacji
    virtual double symuluj(double wejscie) = 0;
};

#endif // OBIEKTSISO_H