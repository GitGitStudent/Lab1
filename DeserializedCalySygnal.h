#ifndef DESERIALIZE_CALY_SYGNAL_H
#define DESERIALIZE_CALY_SYGNAL_H

#include <fstream>
#include "Sygnal.h"
#include "SygnalBazowy.h"
#include "DekoratoryKonkretne.h"
#include "SygnalKonkretny.h"

/**
 * @file deserializeCalySygnal.h
 * @brief Deklaracja funkcji do deserializacji ca³ego ³añcucha sygna³u.
 */

 /**
  * @brief Deserializuje ca³y sygna³ z pliku wejœciowego.
  *
  * Funkcja odczytuje dane z pliku i rekonstruuje pe³n¹ strukturê sygna³u,
  * w tym dekoratory i sygna³ bazowy.
  *
  * @param in Referencja do strumienia wejœciowego (plikowego).
  * @return WskaŸnik na zdeserializowany obiekt typu Sygnal.
  */
Sygnal* deserializeCalySygnal(std::ifstream& in);

#endif // DESERIALIZE_CALY_SYGNAL_H
