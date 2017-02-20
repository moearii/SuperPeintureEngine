#include "renderingwidget.h"

#include <QCoreApplication>
#include <QKeyEvent>

QColor RenderingWidget::couleurPigment1 = QColor(0,0,0);
QColor RenderingWidget::couleurPigment2 = QColor(0,0,0);
QColor RenderingWidget::couleurMelange = QColor(0,0,0);

glm::vec3 RenderingWidget::test(0.0f, 0.0f, 0.0f);

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
    parseur.loadFilesFromDirectory((char*)"../pigments/");

    /** Indiquer le chemin vers les fichiers lumieres */
    parseur.loadFilesFromDirectory((char*)"../lumieres/");

    pigments = parseur.getPigmentList();
    lumieres = parseur.getLightList();
}

void RenderingWidget::resizeGL(int w, int h) {
    glEnable(GL_DEPTH_TEST);
    glViewport(0,0,w,h);
}

void RenderingWidget::paintGL() {

//    cout << "ClearColor = " << test.x << " " << test.y << " " << test.z << endl;
    glClearColor(test.x, test.y, test.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    QString pigmentLabel1("yo");
    QString pigmentLabel2("ac");
    QString lightLabel("D65");
    float concentrationPig1 = 1.f;
    float concentrationPig2 = 1.f - concentrationPig1;

    getPigmentfromLabel(pigmentLabel1)->setConcentration(concentrationPig1);
    getPigmentfromLabel(pigmentLabel2)->setConcentration(concentrationPig2);

    pipe_cpu->run_full_samples(
                getPigmentfromLabel(pigmentLabel1),
                getPigmentfromLabel(pigmentLabel2),
                getLightfromLabel(lightLabel),
                test);
}

Pigment* RenderingWidget::getPigmentfromLabel(const QString& name){
    int i=0;
    while(name.toStdString().compare(pigments.at(i).getLabel()) != 0)
        i++;

    return &(pigments.at(i));
}

Light* RenderingWidget::getLightfromLabel(const QString& name){
    int i=0;
    while(name.toStdString().compare(lumieres.at(i).getLabel()) != 0)
        i++;

    return &(lumieres.at(i));
}
