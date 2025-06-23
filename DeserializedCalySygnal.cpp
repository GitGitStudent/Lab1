#include "DeserializedCalySygnal.h"
#include "iostream"
Sygnal* deserializeCalySygnal(std::ifstream& in) {
    std::string line;
    std::vector<std::string> lines;

    // Wczytaj wszystkie linie do wektora
    while (std::getline(in, line)) {
        if (line == "END") break;
        lines.push_back(line);
    }

    Sygnal* sygnal = nullptr;

    // 1. ZnajdŸ i utwórz sygna³ bazowy
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i] == "SygnalBazowy") {
            double poziom = std::stod(lines[i + 1].substr(7));
            sygnal = new SygnalBazowy(poziom);
            break;
        }
    }
    if (!sygnal) return nullptr;

    // 2. Nak³adaj dekoratory w ustalonej kolejnoœci, jeœli wystêpuj¹ w pliku

    // Trojkatny
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i] == "SygnalTrojkatny") {
            double a = std::stod(lines[i + 1].substr(10));
            double o = std::stod(lines[i + 2].substr(6));
            sygnal = new SygnalTrojkatny(sygnal, a, o);
            break;
        }
    }
    // Prostokatny
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i] == "SygnalProstokatny") {
            double a = std::stod(lines[i + 1].substr(10));
            double o = std::stod(lines[i + 2].substr(6));
            double w = std::stod(lines[i + 3].substr(12));
            sygnal = new SygnalProstokatny(sygnal, a, o, w);
            break;
        }
    }
    // OgraniczenieAmplitudy
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i] == "OgraniczenieAmplitudy") {
            double m = std::stod(lines[i + 1].substr(14));
            sygnal = new OgraniczenieAmplitudy(sygnal, m);
            break;
        }
    }
    // Sinusoidalny
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i] == "SygnalSinusoidalny") {
            double a = std::stod(lines[i + 1].substr(10));
            double o = std::stod(lines[i + 2].substr(14));
            double t = std::stod(lines[i + 3].substr(2));
            sygnal = new SygnalSinusoidalny(sygnal, a, o, t);
            break;
        }
    }
    // Szum
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i] == "SygnalBialySzum") {
            double a = std::stod(lines[i + 1].substr(10));
            sygnal = new SygnalBialySzum(sygnal, a);
            break;
        }
    }

    return sygnal;
}


