#include "light.h"

Light::Light(std::string label, float norm, Spectre light)
{
    labelLight = label;
    lightSpectrum = Spectre(light);
    k = norm;
}

Spectre Light::getSpectre(){
    return lightSpectrum;
}

float Light::getK(){
    return k;
}

std::string Light::getLabel(){
    return labelLight;
}
