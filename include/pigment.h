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

    // Getter
    std::string getLabel();
    Spectre getAbsorption();
    Spectre getScattering();
    float getConcentration();

    // Setter
    void setLabel(std::string name);
    void setAbsorption(Spectre absorption);
    void setScattering(Spectre scattering);
    void setConcentration(float c);

    void printDataPigment();

    //static Pigment getPigmentfromList(vector<Pigment> list, const QString& name);

private:
    //Attributes
    std::string labelPigment;
    Spectre absorptionSpectrum;
    Spectre scatteringSpectrum;
    float concentration;
};

#endif // PIGMENT_H
