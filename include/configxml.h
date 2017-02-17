#ifndef CONFIGXML_H
#define CONFIGXML_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include <QtXml/qdom.h>
#include <QFile>
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
    std::vector<int> parseNodeLambda(QDomElement& nodeLambdai);
    std::vector<float> parseNodeHi(QDomElement& nodeHi);
    float parseNodeCoefK(QDomElement& nodeCoefK);
    std::vector<float> parseNodeSpectre(QDomElement& nodeSpectre);

    // TODO: export data to xmlfiles
    bool exportDataToFilePigment(const QString& filename);

    Pigment getPigment(const QString& name);
    Light getLight(const QString& name);

    std::vector<Pigment> getPigmentList();
    std::vector<Light> getLightList();

    QString name;
    // Pigments attributes
    std::vector<float> absorptionSpectrum;
    std::vector<float> scatteringSpectrum;
    std::vector<float> lightSpectrum;
    std::vector<float> wavelengthList;
    // Lights attributes
    float coeffK;
    std::vector<float> hiSamples;
    std::vector<int> lambdaSamples;

    std::vector<Pigment> pigmentList;
    std::vector<Light> lightList;
};

#endif // CONFIGXML_H
