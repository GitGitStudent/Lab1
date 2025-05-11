#ifndef DESERIALIZE_CALY_SYGNAL_H
#define DESERIALIZE_CALY_SYGNAL_H

#include <fstream>
#include "Sygnal.h"
#include "SygnalBazowy.h"
#include "DekoratoryKonkretne.h"
#include "SygnalKonkretny.h"

/**
 * @file deserializeCalySygnal.h
 * @brief Deklaracja funkcji do deserializacji ca�ego �a�cucha sygna�u.
 */

 /**
  * @brief Deserializuje ca�y sygna� z pliku wej�ciowego.
  *
  * Funkcja odczytuje dane z pliku i rekonstruuje pe�n� struktur� sygna�u,
  * w tym dekoratory i sygna� bazowy.
  *
  * @param in Referencja do strumienia wej�ciowego (plikowego).
  * @return Wska�nik na zdeserializowany obiekt typu Sygnal.
  */
Sygnal* deserializeCalySygnal(std::ifstream& in);

#endif // DESERIALIZE_CALY_SYGNAL_H
