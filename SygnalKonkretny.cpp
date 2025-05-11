#include "SygnalKonkretny.h"
#define M_PI 3.14159265358979323846

// Sygna³ sinusoidalny
SygnalSinusoidalny::SygnalSinusoidalny(Sygnal* komponent ,double amplituda, double czestotliwosc, double T)
    : komponent(komponent), amplituda(amplituda), czestotliwosc(czestotliwosc), T(T), omegaT(2 * M_PI * czestotliwosc * T) {
    poprzednie.push_back(0.0); // x(n-2)
    poprzednie.push_back(amplituda * std::sin(omegaT)); // x(n-1)
}

double SygnalSinusoidalny::symuluj(int n) {
	double wartoscBazowa = komponent->symuluj(n);
    double nowaWartosc = 2 * std::cos(omegaT) * poprzednie[1] - poprzednie[0];
    poprzednie.pop_front();
    poprzednie.push_back(nowaWartosc);
    return wartoscBazowa + nowaWartosc;
}

void SygnalSinusoidalny::serialize(std::ofstream& out) const {
    out << "SygnalSinusoidalny\n";
    out << "amplituda=" << amplituda << "\n";
    out << "czestotliwosc=" << czestotliwosc << "\n";
    out << "T=" << T << "\n";
    komponent->serialize(out);
}





// Sygna³ prostok¹tny
SygnalProstokatny::SygnalProstokatny(Sygnal* komponent, double amplituda, int okres, double wypelnienie)
    : komponent(komponent), amplituda(amplituda), okres(okres), wypelnienie(wypelnienie), krok(0) {
}

double SygnalProstokatny::symuluj(int n) {
    double wartoscBazowa = komponent->symuluj(n);
    double czasWOkresie = krok % okres;
    krok++;
    double wartoscProstokatna = (czasWOkresie < wypelnienie * okres) ? amplituda : 0.0;
    return wartoscBazowa + wartoscProstokatna;
}

void SygnalProstokatny::serialize(std::ofstream& out) const {
    out << "SygnalProstokatny\n";
    out << "amplituda=" << amplituda << "\n";
    out << "okres=" << okres << "\n";
    out << "wypelnienie=" << wypelnienie << "\n";
    komponent->serialize(out);
}



// Sygna³ trójk¹tny
SygnalTrojkatny::SygnalTrojkatny(Sygnal* komponent, double amplituda, int okres)
    : komponent(komponent), amplituda(amplituda), okres(okres), krok(0) {
}

double SygnalTrojkatny::symuluj(int n) {
	
    
    double wartoscBazowa = komponent->symuluj(n);
  
    double czasWOkresie = krok % okres;
    krok++;
    double wartoscTrojkatna = amplituda * (1.0 - 2.0 * fabs(czasWOkresie / static_cast<double>(okres) - 0.5));
    return wartoscBazowa + wartoscTrojkatna;
}

void SygnalTrojkatny::serialize(std::ofstream& out) const {
    out << "SygnalTrojkatny\n";
    out << "amplituda=" << amplituda << "\n";
    out << "okres=" << okres << "\n";
    komponent->serialize(out);
}


// Sygna³ bia³y szum
SygnalBialySzum::SygnalBialySzum(Sygnal* komponent, double amplituda)
    : komponent(komponent), amplituda(amplituda), rozklad(-amplituda, amplituda) {
}

double SygnalBialySzum::symuluj(int n) {
    double wartoscBazowa = komponent->symuluj(n);
    double wartoscSzum = rozklad(generator);
    return wartoscBazowa + wartoscSzum;
}

void SygnalBialySzum::serialize(std::ofstream& out) const {
    out << "SygnalBialySzum\n";
    out << "amplituda=" << amplituda << "\n";
    komponent->serialize(out);
}


