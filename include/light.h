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
    Light(string label, float norm, Spectre light);

    Spectre getSpectre();
    float getK();
    string getLabel();

private:
    string labelLight;
    Spectre lightSpectrum;
    float k;
};

#endif // LIGHT_H
