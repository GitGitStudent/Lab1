#include "DeserializedCalySygnal.h"
#include "iostream"
Sygnal* deserializeCalySygnal(std::ifstream& in) {
    std::string line;
    Sygnal* sygnal = nullptr;

    // Bazowy
    while (std::getline(in, line)) {
        if (line == "SygnalBazowy") {
            double poziom;
            std::getline(in, line); // "poziom=2.5"
            poziom = std::stod(line.substr(7));
            sygnal = new SygnalBazowy(poziom);
           
            break;
        }
    }
    in.clear(); 
    in.seekg(0); 
    // Dekoratory
    while (std::getline(in, line)) {
        
        if (line == "SygnalTrojkatny") {
            double a, o;
            std::getline(in, line); // amplituda
            a = std::stod(line.substr(10));
            std::getline(in, line); // okres
            o = std::stod(line.substr(6));
            sygnal = new SygnalTrojkatny(sygnal, a, o);
            
        }
        else if (line == "SygnalProstokatny") {
            double a, o, w;
            std::getline(in, line); // amplituda
            a = std::stod(line.substr(10));
            std::getline(in, line); // okres
            o = std::stod(line.substr(6));
            std::getline(in, line); // wypelnienie
            w = std::stod(line.substr(12));
            sygnal = new SygnalProstokatny(sygnal, a, o, w);
        }
        else if (line == "OgraniczenieAmplitudy") {
            std::getline(in, line); // maksAmplituda
            double m = std::stod(line.substr(14));
            sygnal = new OgraniczenieAmplitudy(sygnal, m);
        }
		else if (line == "SygnalSinusoidalny") {
			double a, o, t;
			std::getline(in, line); // amplituda
			a = std::stod(line.substr(10));
			std::getline(in, line); // czestotliwosc
			o = std::stod(line.substr(14));
			std::getline(in, line); // T
			t = std::stod(line.substr(2));
			sygnal = new SygnalSinusoidalny(sygnal, a, o, t);
		}
		else if (line == "SygnalBialySzum") {
			double a;
			std::getline(in, line); // amplituda
			a = std::stod(line.substr(10));
			sygnal = new SygnalBialySzum(sygnal, a);
		}
        else if (line == "END") {
            break;
        }
    }

    return sygnal;
}
