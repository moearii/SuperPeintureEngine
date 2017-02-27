#ifndef SPECTRE_H
#define SPECTRE_H

#include <iostream>
#include <vector>

using namespace  std;

class Spectre
{
public:
    Spectre();
    Spectre(vector<float> wavelength, vector<float> amplitude);
    Spectre(const Spectre&);

    vector<float> getWavelengthList();
    vector<float> getAmplitudeList();
    float getWavelength(int i);
    float getAmplitude(int i);

    void setWavelengths(vector<float> wavelist);
    void setAmplitudes(vector<float> amplist);

private:
    vector<float> wavelengthList;
    vector<float> amplitudeList;
};

#endif // SPECTRE_H
