#include "pigment.h"

Pigment::Pigment(string label, Spectre absorption, Spectre scattering)
{
    labelPigment = label;
    absorptionSpectrum = Spectre(absorption);
    scatteringSpectrum = Spectre(scattering);
}

string Pigment::getLabel()
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

void Pigment::setLabel(string label)
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
