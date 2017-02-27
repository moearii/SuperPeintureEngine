#ifndef PIGMENT_H
#define PIGMENT_H

#include <iostream>
#include <vector>
#include <string>
#include <QString>

#include "spectre.h"

using namespace std;

class Pigment
{
public:
    Pigment(std::string label, Spectre absorption, Spectre scattering);

    std::string getLabel();
    Spectre getAbsorption();
    Spectre getScattering();

    void setLabel(std::string name);
    void setAbsorption(Spectre absorption);
    void setScattering(Spectre scattering);

    string labelPigment;
    Spectre absorptionSpectrum;
    Spectre scatteringSpectrum;
};

#endif // PIGMENT_H
