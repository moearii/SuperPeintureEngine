#include "configxml.h"

ConfigXML::ConfigXML()
{

}

bool ConfigXML::loadFilesFromDirectory(char* directory)
{
    DIR* dir = opendir(directory);
    struct dirent* file = NULL;
    if(dir == NULL)
    {
        std::cerr << "Error while opening directory" << std::endl;
        return false;
    }
    int n = 0;
    while((file = readdir(dir)) != NULL)
    {
        if(strcmp(file->d_name, ".")==0 || strcmp(file->d_name,"..")==0)
        {
            n++;
        }
        else
        {
            char dir[256];
            char fil[256];
            strcpy(dir,directory);
            strcpy(fil,file->d_name);
            char* path =  strcat(dir,fil);

            QString qstr(path);
            loadDataFromFile(qstr);
        }
    }
    return true;
}

bool ConfigXML::loadDataFromFile(const QString &filename)
{
    QDomDocument document;

    // Read data from file
    QFile f(filename);
    if(!f.open(QIODevice::ReadOnly))
    {
        // Error while loading file
        std::cerr << "Error while loading file" << std::endl;
        return false;
    }

    // Set data into the QDocument before processing
    document.setContent(&f);
    f.close();

    // Read the root tag
    QDomElement root = document.documentElement();
    // Get root names and attributes
    QString type = root.tagName();

    if(type.toStdString() == "pigment")
    {
        parsePigment(root);
    }
    else if(type.toStdString() == "lumiere")
    {
        parseLight(root);
    }
    return true;
}

/* The pigment file must have the following structure:
 *
 * <pigment>
 * <label></label>
 * <amplitude wavelength = "">
 *      <absorption></absorption>
 *      <scattering></scattering>
 * </amplitude>
 * </pigment>
 *
 * Label: QString
 * Wavelength: QString convertie en Float
 * Absorption: Float
 * Scattering: Float
 * */
void ConfigXML::parsePigment(QDomElement &root)
{
    QDomElement label = root.firstChildElement("label");
    QString namePigment = parseNodeLabel(label);

    QDomElement amplitude = root.firstChildElement("amplitude");
    parseNodeAmplitudePigment(amplitude);

    pigmentList.push_back(Pigment(namePigment.toStdString(),Spectre(wavelengthList,absorptionSpectrum),Spectre(wavelengthList,scatteringSpectrum)));

    name.clear();
    absorptionSpectrum.clear();
    scatteringSpectrum.clear();
    wavelengthList.clear();
}

/* The light file must have the following structure:
 *
 * <light>
 * <label></label>
 * <k></k>
 * <amplitude wavelength="">/amplitude>
 * </light>
 *
 * Label: QString
 * CoefK: Float
 * Wavelength: QString convertie en Float
 * Amplitude: Float
 * */

void ConfigXML::parseLight(QDomElement &root)
{
    QDomElement label = root.firstChildElement("label");
    QString name = parseNodeLabel(label);

    QDomElement spectre = root.firstChildElement("amplitude");
    parseNodeAmplitudeLight(spectre);

    QDomElement coeff = root.firstChildElement("k");
    parseNodeCoefK(coeff);

    lightList.push_back(Light(name.toStdString(),coeffK,Spectre(wavelengthList,lightSpectrum)));

    coeffK = 0;
    name.clear();
    wavelengthList.clear();
    lightSpectrum.clear();
}

QString ConfigXML::parseNodeLabel(QDomElement &nodeLabel)
{
    if(nodeLabel.tagName() == "label")
        name = nodeLabel.firstChild().toText().data();
    return name;
}

void ConfigXML::parseNodeAmplitudePigment(QDomElement &nodeAmplitude)
{
    // Loop while there is a child
    while(!nodeAmplitude.isNull())
    {
        // Check if the child tage name is amplitude
        if(nodeAmplitude.tagName() == "amplitude")
        {
            // Read and display the component wavelength
            QString wavelength = nodeAmplitude.attribute("wavelength","value");
            wavelengthList.push_back(wavelength.toFloat());

            // Get the first child of the component
            QDomElement child = nodeAmplitude.firstChild().toElement();

            float absorption;
            float scattering;
            // Read each child of the component node
            while(!child.isNull())
            {
                // Read name and value
                if(child.tagName() == "absorption") absorption = child.firstChild().toText().data().toFloat();
                if(child.tagName() == "diffusion") scattering = child.firstChild().toText().data().toFloat();

                // Next child
                child = child.nextSibling().toElement();
            }
            absorptionSpectrum.push_back(absorption);
            scatteringSpectrum.push_back(scattering);
        }
        nodeAmplitude = nodeAmplitude.nextSibling().toElement();
    }
}


void ConfigXML::parseNodeAmplitudeLight(QDomElement &nodeAmplitude)
{
    // Check if the child tage name is amplitude
    while(nodeAmplitude.tagName() == "amplitude")
    {
        // Read and display the component wavelength
        QString wavelength = nodeAmplitude.attribute("wavelength","value");
        wavelengthList.push_back(wavelength.toFloat());

        float amplitude;
        amplitude = nodeAmplitude.firstChild().toText().data().toFloat();
        lightSpectrum.push_back(amplitude);
        nodeAmplitude = nodeAmplitude.nextSibling().toElement();
    }
}

float ConfigXML::parseNodeCoefK(QDomElement &nodeCoefK)
{
    if(nodeCoefK.tagName() == "k")
        coeffK = nodeCoefK.firstChild().toText().data().toFloat();
    return coeffK;
}

Pigment ConfigXML::getPigment(const QString& name)
{
    int i=0;
    while(name.toStdString().compare(pigmentList.at(i).getLabel()) != 0)
        i++;

    return pigmentList.at(i);
}

Light ConfigXML::getLight(const QString& name)
{
    int i=0;
    while(name.toStdString().compare(lightList.at(i).getLabel()) != 0)
        i++;

    return lightList.at(i);
}

std::vector<Pigment> ConfigXML::getPigmentList(){
    return pigmentList;
}

std::vector<Light> ConfigXML::getLightList(){
    return lightList;
}

bool ConfigXML::exportDataToFilePigment(const QString& directory, Spectre spectreAbsorption, Spectre spectreDiffusion)
{
    QFileInfo fileInfo(directory);
    QString filename = fileInfo.fileName();
    QDomDocument document;

    // Create the root element
    QDomElement root = document.createElement("pigment");

    // Adding the root element to the document
    document.appendChild(root);

    // Adding more elements
    QDomElement label = document.createElement("label");
    QString nameXML = filename.mid(0,filename.size()-4);
    label.appendChild(document.createTextNode(nameXML));
    root.appendChild(label);

    for(int i=0; i<spectreAbsorption.getWavelengthList().size(); ++i)
    {
        QDomElement amplitude = document.createElement("amplitude");
        amplitude.setAttribute("wavelength",spectreAbsorption.getWavelengthList().at(i));

        QDomElement absorption = document.createElement("absorption");
        std::string valueK = to_string(spectreAbsorption.getAmplitude(i));
        absorption.appendChild(document.createTextNode(QString::fromStdString(valueK)));

        QDomElement scattering = document.createElement("diffusion");
        std::string valueS = to_string(spectreDiffusion.getAmplitude(i));
        scattering.appendChild(document.createTextNode(QString::fromStdString(valueS)));

        root.appendChild(amplitude);
        amplitude.appendChild(absorption);
        amplitude.appendChild(scattering);
    }
    // Writing to a file
    QFile file(directory);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug("Error while writing file");
        return false;
    }
    else
    {
        QTextStream stream(&file);
        stream << document.toString();
        file.close();
        qDebug("Writing is done");
    }
    return true;
}
