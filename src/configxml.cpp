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
        //std::cout << "--> Chargement fichier pigment... " << std::endl;
        parsePigment(root);
    }
    else if(type.toStdString() == "lumiere")
    {
        //std::cout << "--> Chargement fichier lumiere..." << std::endl;
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
 * <amplitude wavelength="">>/amplitude>
 * </light>
 *
 * */

/* The light file must have the following structure:
 *
 * <light>
 * <label></label>
 * <lambdai>
 *      <sample></sample>
 *      <sample></sample>
 *      <sample></sample>
 * </lambdai>
 * <hi>
 *      <sample></sample>
 *      <sample></sample>
 *      <sample></sample>
 * </hi>
 * <coef_K></coef_K>
 * <spectre>
 *      <amplitude></amplitude>
 *      <amplitude></amplitude>
 *      <amplitude></amplitude>
 * </spectre>
 * </light>
 *
 * Label: QString
 * Lambdai: liste de sample en Int
 * Hi: liste de sample en Float
 * CoefK: Float
 * Spectre: liste d'amplitude en Float
 * */
void ConfigXML::parseLight(QDomElement &root)
{
    QDomElement label = root.firstChildElement("label");
    QString name = parseNodeLabel(label);

    QDomElement spectre = root.firstChildElement("amplitude");
    parseNodeAmplitudeLight(spectre);

    QDomElement coeff = root.firstChildElement("k");
    parseNodeCoefK(coeff);

    /** 1ere version format fichier lumiere
    QDomElement lambdai = root.firstChildElement("lambda_i");
    parseNodeLambda(lambdai);

    QDomElement hi = root.firstChildElement("hi");
    parseNodeHi(hi);

    QDomElement spectre = root.firstChildElement("spectre");
    parseNodeSpectre(spectre); */

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

std::vector<int> ConfigXML::parseNodeLambda(QDomElement &nodeLambdai)
{
    // Check if the child tage name is lambda_i
    if(nodeLambdai.tagName() == "lambda_i")
    {
        // Get the first child of the component
        QDomElement child = nodeLambdai.firstChild().toElement();

        int sample;
        // Read each child of the component node
        while(!child.isNull())
        {
            // Read name and value
            if(child.tagName() == "sample") sample = child.firstChild().toText().data().toInt();
            // Next child
            child = child.nextSibling().toElement();
            lambdaSamples.push_back(sample);
        }
    }
    nodeLambdai = nodeLambdai.nextSibling().toElement();

    return lambdaSamples;
}

std::vector<float> ConfigXML::parseNodeHi(QDomElement &nodeHi)
{
    // Check if the child tage name is hi
    if(nodeHi.tagName() == "hi")
    {
        // Get the first child of the component
        QDomElement child = nodeHi.firstChild().toElement();

        int sample;
        // Read each child of the component node
        while(!child.isNull())
        {
            // Read name and value
            if(child.tagName() == "sample") sample = child.firstChild().toText().data().toFloat();
            // Next child
            child = child.nextSibling().toElement();
            hiSamples.push_back(sample);
        }
    }
    nodeHi = nodeHi.nextSibling().toElement();

    return hiSamples;
}

std::vector<float> ConfigXML::parseNodeSpectre(QDomElement &nodeSpectre)
{
    // Check if the child tage name is spectre
    if(nodeSpectre.tagName() == "spectre")
    {
        // Get the first child of the component
        QDomElement child = nodeSpectre.firstChild().toElement();

        float amplitude;
        // Read each child of the component node
        while(!child.isNull())
        {
            // Read name and value
            if(child.tagName() == "amplitude") amplitude = child.firstChild().toText().data().toFloat();
            // Next child
            child = child.nextSibling().toElement();
            lightSpectrum.push_back(amplitude);
        }
    }
    nodeSpectre = nodeSpectre.nextSibling().toElement();

    return lightSpectrum;
}

bool ConfigXML::exportDataToFilePigment(const QString& filename)
{
    QDomDocument document;

    // Create the root element
    QDomElement root = document.createElement("pigment");

    // Adding the root element to the document
    document.appendChild(root);

    // Adding more elements
    QDomElement label = document.createElement("label");
    label.appendChild(document.createTextNode(name));
    root.appendChild(label);

    for(int i=0; i<wavelengthList.size(); ++i)
    {
        QDomElement amplitude = document.createElement("amplitude");
        amplitude.setAttribute("wavelength",wavelengthList.at(i));

        QDomElement absorption = document.createElement("absorption");
        std::string valueK = to_string(absorptionSpectrum.at(i));
        absorption.appendChild(document.createTextNode(QString::fromStdString(valueK)));

        QDomElement scattering = document.createElement("diffusion");
        std::string valueS = to_string(scatteringSpectrum.at(i));
        scattering.appendChild(document.createTextNode(QString::fromStdString(valueS)));

        root.appendChild(amplitude);
        amplitude.appendChild(absorption);
        amplitude.appendChild(scattering);
    }
    // Writing to a file
    QFile file(filename);
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
