#include "spectre.h"

Spectre::Spectre()
{

}

Spectre::Spectre(std::vector<float> wavelength, std::vector<float> amplitude)
{
    wavelengthList = wavelength;
    amplitudeList = amplitude;
}

Spectre::Spectre(const Spectre &copie)
{
    wavelengthList = copie.wavelengthList;
    amplitudeList = copie.amplitudeList;
}

void Spectre::setWavelengths(std::vector<float> wavelist){
    wavelengthList = wavelist;
}

void Spectre::setAmplitudes(std::vector<float> amplist){
    amplitudeList = amplist;
}

std::vector<float> Spectre::getWavelengthList(){
    return wavelengthList;
}

std::vector<float> Spectre::getAmplitudeList(){
    return amplitudeList;
}

float Spectre::getWavelength(int i){
    return wavelengthList[i];
}

float Spectre::getAmplitude(int i){
    return amplitudeList[i];
}

void Spectre::printDataSpectrum()
{
    std::cout << "Wavelength: " << wavelengthList.size() <<  " valeurs" << std::endl;
    for(std::vector<float>::iterator it = wavelengthList.begin(); it != wavelengthList.end(); ++it)
    {
        std::cout << (*it) << std::endl;
    }
    std::cout << "Amplitude: " << amplitudeList.size() <<  " valeurs" << std::endl;
    for(std::vector<float>::iterator it = amplitudeList.begin(); it != amplitudeList.end(); ++it)
    {
        std::cout << (*it) << std::endl;
    }
}
