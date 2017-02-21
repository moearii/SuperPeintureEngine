#include "pigment.h"

Pigment::Pigment(std::string label, Spectre absorption, Spectre scattering)
{
    labelPigment = label;
    absorptionSpectrum = Spectre(absorption);
    scatteringSpectrum = Spectre(scattering);
}

std::string Pigment::getLabel()
{
    return labelPigment;
}

Spectre Pigment::getAbsorption()
{
    return absorptionSpectrum;
}

Spectre Pigment::getScattering()
{
    return scatteringSpectrum;
}

void Pigment::setLabel(std::string label)
{
    labelPigment = label;
}

void Pigment::setAbsorption(Spectre absorption)
{
    absorptionSpectrum = Spectre(absorption);
}

void Pigment::setScattering(Spectre scattering)
{
    scatteringSpectrum = Spectre(scattering);
}

void Pigment::printDataPigment()
{
    std::cout << "\nNom pigment: " << labelPigment << std::endl;
    absorptionSpectrum.printDataSpectrum();
    scatteringSpectrum.printDataSpectrum();
}
