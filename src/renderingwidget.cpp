#include "renderingwidget.h"

#include <QCoreApplication>
#include <QKeyEvent>

RenderingWidget::RenderingWidget(const QGLFormat & format, QWidget * parent)
    : QGLWidget(format, parent){

}

RenderingWidget::~RenderingWidget(){
    pipe_cpu->~Pipeline();
    pipe_gpu->~Pipeline();
}

void RenderingWidget::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glViewport(0,0,width(),height());

    pipe_cpu = new Pipeline_CPU();
    pipe_gpu = new Pipeline_GPU();


    ConfigXML parseur;

    /** Indiquer le chemin vers les fichiers pigments */
    parseur.loadFilesFromDirectory("../pigments/");

    /*
    std::cout << "Nombre de pigments charges: " << parseur.pigmentList.size()  << "\n" << std::endl;
    for(std::vector<Pigment>::iterator it = parseur.pigmentList.begin(); it != parseur.pigmentList.end(); ++it)
        (*it).printDataPigment();
    */

    /** Indiquer le chemin vers les fichiers lumieres */
    parseur.loadFilesFromDirectory("../lumieres/");

    /*
    std::cout << "Nombre de lumieres chargees: " << parseur.lightList.size() << std::endl;
    for(std::vector<Light>::iterator it = parseur.lightList.begin(); it != parseur.lightList.end(); ++it)
        (*it).printDataLight();
    */

    pigments = parseur.getPigmentList();
    lumieres = parseur.getLightList();

    slider_concentration = 1.f;
    label_pigment1 = "ac";
    label_pigment2 = "ac";
    lightLabel = "D65";
    resultat = glm::vec3(0.0f, 0.0f, 0.0f);
}

void RenderingWidget::resizeGL(int w, int h) {
    glEnable(GL_DEPTH_TEST);
    glViewport(0,0,w,h);
}

void RenderingWidget::paintGL() {

    pipe_cpu->run_full_samples(
                getPigmentfromLabel(label_pigment1),
                getPigmentfromLabel(label_pigment2),
                slider_concentration,
                getLightfromLabel(lightLabel),
                resultat);

    glClearColor(resultat.x, resultat.y, resultat.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

Pigment * RenderingWidget::getPigmentfromLabel(const QString& name){
    int i=0;
    while(name.toStdString().compare(pigments.at(i).getLabel()) != 0)
        i++;

    return &(pigments.at(i));
}

Light * RenderingWidget::getLightfromLabel(const QString& name){
    int i=0;
    while(name.toStdString().compare(lumieres.at(i).getLabel()) != 0)
        i++;

    return &(lumieres.at(i));
}

QColor RenderingWidget::getResultat(){
    return QColor(resultat.x * 255, resultat.y * 255, resultat.z * 255);
    //return QColor();
}

glm::vec3 RenderingWidget::getResultatFloatPrecision(){
    return resultat;
}

vector<QString> RenderingWidget::getPigmentsLabels(){
    vector<QString> list;
    for(int i = 0; i < pigments.size(); i++){
        list.push_back(QString(pigments[i].getLabel().c_str()));
    }
    return list;
}

void RenderingWidget::setLabel_pigment1(QString label){
    label_pigment1 = label;
}

void RenderingWidget::setLabel_pigment2(QString label){
    label_pigment2 = label;
}

void RenderingWidget::setSlider_concentration(float concentration){
    slider_concentration = concentration;
}
