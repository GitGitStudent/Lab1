#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#define DEBUG

#include "RegulatorPID.h"
#include "ModelARX.h"
#include "PetlaSprzezeniaZwrotnego.h"

#ifdef DEBUG

//Funkcje pomocnicze dla testów:

void raportBleduSekwencji(std::vector<double>& spodz, std::vector<double>& fakt)
{
	constexpr size_t PREC = 3;
	std::cerr << std::fixed << std::setprecision(PREC);
	std::cerr << "  Spodziewany:\t";
	for (auto& el : spodz)
		std::cerr << el << ", ";
	std::cerr << "\n  Faktyczny:\t";
	for (auto& el : fakt)
		std::cerr << el << ", ";
	std::cerr << std::endl << std::endl;
}

bool porownanieSekwencji(std::vector<double>& spodz, std::vector<double>& fakt)
{
	constexpr double TOL = 1e-3;	// tolerancja dla porównań zmiennoprzecinkowych
	bool result = fakt.size() == spodz.size();
	for (int i = 0; result && i < fakt.size(); i++)
		result = fabs(fakt[i] - spodz[i]) < TOL;
	return result;
}

void test_RegulatorP_brakPobudzenia()
{
	//Sygnatura testu:
	std::cerr << "RegP (k = 0.5) -> test zerowego pobudzenia: ";
	try
	{
		// Przygotowanie danych:
		RegulatorPID instancjaTestowa(0.5);
		constexpr size_t LICZ_ITER = 30;
		std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu (tu same 0)
		std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy (tu same 0)
		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

		// Symulacja modelu:

		for (int i = 0; i < LICZ_ITER; i++)
			faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

		// Walidacja poprawności i raport:
		if (porownanieSekwencji(spodzSygWy, faktSygWy))
			std::cerr << "OK!\n";
		else
		{
			std::cerr << "FAIL!\n";
			raportBleduSekwencji(spodzSygWy, faktSygWy);
		}
	}
	catch (...)
	{
		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
	}
}

void test_RegulatorP_skokJednostkowy()
{
	//Sygnatura testu:
	std::cerr << "RegP (k = 0.5) -> test skoku jednostkowego: ";

	try
	{
		// Przygotowanie danych:
		RegulatorPID instancjaTestowa(0.5);
		constexpr size_t LICZ_ITER = 30;
		std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu 
		std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy 
		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

		// Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
		for (int i = 0; i < LICZ_ITER; i++)
			sygWe[i] = !!i;
		spodzSygWy = { 0.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };

		// Symulacja modelu:
		for (int i = 0; i < LICZ_ITER; i++)
			faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

		// Walidacja poprawności i raport:
		if (porownanieSekwencji(spodzSygWy, faktSygWy))
			std::cerr << "OK!\n";
		else
		{
			std::cerr << "FAIL!\n";
			raportBleduSekwencji(spodzSygWy, faktSygWy);
		}
	}
	catch (...)
	{
		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
	}
}

void test_RegulatorPI_skokJednostkowy_1()
{
	//Sygnatura testu:
	std::cerr << "RegPI (k = 0.5, TI = 1.0) -> test skoku jednostkowego nr 1: ";

	try
	{
		// Przygotowanie danych:
		RegulatorPID instancjaTestowa(0.5,1.0);
		constexpr size_t LICZ_ITER = 30;
		std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu 
		std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy 
		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

		// Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
		for (int i = 0; i < LICZ_ITER; i++)
			sygWe[i] = !!i;
		spodzSygWy = { 0, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 16.5, 17.5, 18.5, 19.5, 20.5, 21.5, 22.5, 23.5, 24.5, 25.5, 26.5, 27.5, 28.5, 29.5 };

		// Symulacja modelu:
		for (int i = 0; i < LICZ_ITER; i++)
			faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

		// Walidacja poprawności i raport:
		if (porownanieSekwencji(spodzSygWy, faktSygWy))
			std::cerr << "OK!\n";
		else
		{
			std::cerr << "FAIL!\n";
			raportBleduSekwencji(spodzSygWy, faktSygWy);
		}
	}
	catch (...)
	{
		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
	}
}

void test_RegulatorPI_skokJednostkowy_2()
{
	//Sygnatura testu:
	std::cerr << "RegPI (k = 0.5, TI = 10.0) -> test skoku jednostkowego nr 2: ";

	try
	{
		// Przygotowanie danych:
		RegulatorPID instancjaTestowa(0.5, 10.0);
		constexpr size_t LICZ_ITER = 30;
		std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu 
		std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy 
		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

		// Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
		for (int i = 0; i < LICZ_ITER; i++)
			sygWe[i] = !!i;
		spodzSygWy = { 0, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3, 3.1, 3.2, 3.3, 3.4 };

		// Symulacja modelu:
		for (int i = 0; i < LICZ_ITER; i++)
			faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

		// Walidacja poprawności i raport:
		if (porownanieSekwencji(spodzSygWy, faktSygWy))
			std::cerr << "OK!\n";
		else
		{
			std::cerr << "FAIL!\n";
			raportBleduSekwencji(spodzSygWy, faktSygWy);
		}
	}
	catch (...)
	{
		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
	}
}

void test_RegulatorPID_skokJednostkowy()
{
	//Sygnatura testu:
	std::cerr << "RegPID (k = 0.5, TI = 10.0, TD = 0.2) -> test skoku jednostkowego: ";

	try
	{
		// Przygotowanie danych:
		RegulatorPID instancjaTestowa(0.5, 10.0, 0.2);
		constexpr size_t LICZ_ITER = 30;
		std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu 
		std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy 
		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

		// Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
		for (int i = 0; i < LICZ_ITER; i++)
			sygWe[i] = !!i;
		spodzSygWy = { 0, 0.8, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3, 3.1, 3.2, 3.3, 3.4 };

		// Symulacja modelu:
		for (int i = 0; i < LICZ_ITER; i++)
			faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

		// Walidacja poprawności i raport:
		if (porownanieSekwencji(spodzSygWy, faktSygWy))
			std::cerr << "OK!\n";
		else
		{
			std::cerr << "FAIL!\n";
			raportBleduSekwencji(spodzSygWy, faktSygWy);
		}
	}
	catch (...)
	{
		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
	}
}

using namespace std;

int main()
{
	test_RegulatorP_brakPobudzenia();
	test_RegulatorP_skokJednostkowy();
	test_RegulatorPI_skokJednostkowy_1();
	test_RegulatorPI_skokJednostkowy_2();
	test_RegulatorPID_skokJednostkowy();

}

#endif

#ifdef MAIN

using namespace std;

int main()
{
	
	RegulatorPID regulator1(1.0, 1.0, 1.0);

	std::cout << "Test 1: Poprawne wartosci\n";
	regulator1.setK(2.5);     // OK
	regulator1.setTi(3.0);    // OK
	regulator1.setTd(0.5);    // OK

	std::cout << "Test 2: Bledne wartosci\n";
	regulator1.setK(-1.0);    // powinno wypisac blad
	regulator1.setTi(-1.0);    // powinno wypisac blad
	regulator1.setTd(-0.7);   // powinno wypisac blad

	RegulatorPID regulator(0.5, 1.0, 0.1); // k=0.5, Ti=1.0, Td=0.1
	ModelARX model({ -0.4, 0.2 }, { 0.6, 0.3 }, 0, 0.0); // wspA, wspB, opoznienie, mocZaklocenia

	
	PetlaSprzezeniaZwrotnego petla;


	int LICZBA_KROKOW = 100;
	double wartoscZadana = 1.0; 
	std::cout << "Symulacja petli sprezenia zwrotnego:\n";
	for (int i = 0; i < LICZBA_KROKOW; ++i) {
		double wartoscRegulowana = petla(regulator, model, wartoscZadana);
		std::cout << "Krok " << i + 1 << ": Wartosc regulowana = " << wartoscRegulowana << "\n";
		if (i == 50) {
			regulator.reset();
		}
	}
	return 0;
}
#endif

