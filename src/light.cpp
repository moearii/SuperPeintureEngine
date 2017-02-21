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

/*Light Light::getLightfromList(vector<Light> list, const QString& name){
    int i=0;
    while(name.toStdString().compare(list.at(i).getLabel()) != 0)
        i++;

    return list.at(i);
}
*/

void Light::printDataLight()
{
    std::cout << "\nNom lumiere: " << labelLight << std::endl;
    lightSpectrum.printDataSpectrum();
}

