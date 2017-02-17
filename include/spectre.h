#ifndef SPECTRE_H
#define SPECTRE_H

#include <iostream>
#include <vector>

class Spectre
{
public:
    Spectre();
    Spectre(std::vector<float> wavelength, std::vector<float> amplitude);
    Spectre(const Spectre&);

    void setWavelengths(std::vector<float> wavelist);
    void setAmplitudes(std::vector<float> amplist);

    std::vector<float> getWavelengthList();
    std::vector<float> getAmplitudeList();

    float getWavelength(int i);
    float getAmplitude(int i);

    void printDataSpectrum();

private:

    std::vector<float> wavelengthList;
    std::vector<float> amplitudeList;
};

#endif // SPECTRE_H
