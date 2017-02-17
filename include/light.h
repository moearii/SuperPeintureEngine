#ifndef LIGHT_H
#define LIGHT_H

#include <vector>
#include <string>
#include <QString>

#include "spectre.h"

using namespace std;

class Light
{
public:
    Light(std::string label, float norm, Spectre light);

    Spectre getSpectre();
    float getK();
    std::string getLabel();

    //static Light getLightfromList(vector<Light> list, const QString& name);

    void printDataLight();

private:
    std::string labelLight;
    Spectre lightSpectrum;
    float k;
};

#endif // LIGHT_H
