#ifndef CONFIGXML_H
#define CONFIGXML_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include <QtXml/qdom.h>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <qtextstream.h>

#include "dirent.h"

#include "pigment.h"
#include "light.h"

using namespace std;

class ConfigXML
{
public:
    ConfigXML();

    bool loadFilesFromDirectory(char* directory);
    bool loadDataFromFile(const QString& filename);

    void parsePigment(QDomElement& root);
    void parseLight(QDomElement& root);

    QString parseNodeLabel(QDomElement& nodeLabel);
    void parseNodeAmplitudePigment(QDomElement& nodeAmplitude);
    void parseNodeAmplitudeLight(QDomElement& nodeAmplitude);
    float parseNodeCoefK(QDomElement& nodeCoefK);

    bool exportDataToFilePigment(const QString& filename, Spectre spectreAbsorption, Spectre spectreDiffusion);

    Pigment getPigment(const QString& name);
    Light getLight(const QString& name);

    vector<Pigment> getPigmentList();
    vector<Light> getLightList();

private:
    QString name;
    // Pigments attributes
    vector<float> absorptionSpectrum;
    vector<float> scatteringSpectrum;
    vector<float> lightSpectrum;
    vector<float> wavelengthList;
    // Lights attributes
    float coeffK;
    vector<float> hiSamples;
    vector<int> lambdaSamples;

    vector<Pigment> pigmentList;
    vector<Light> lightList;
};

#endif // CONFIGXML_H
