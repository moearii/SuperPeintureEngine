#include "mixeur.h"
#include "ui_mixeur.h"

Mixeur::Mixeur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mixeur)
{
    ui->setupUi(this);

    QGLFormat glFormat;
    glFormat.setVersion(4, 3);
    glFormat.setProfile(QGLFormat::CoreProfile);
    glFormat.setSampleBuffers(true);

    render = new RenderingWidget(glFormat);
    render->initializeGL();                     // Pour que l'initialisation se soit bien executée avant ce qui suit

    ui->opengllayout->addWidget(render);
    render->show();                          // debug

    pigments_labels = render->getPigmentsLabels();
    numeroLabel_pigment_1 = 0;
    numeroLabel_pigment_2 = 0;

    //    this->setStyleSheet("background-color:black");
}

Mixeur::~Mixeur()
{
    delete ui;
}

void Mixeur::on_pigment_1_clicked(){

    numeroLabel_pigment_1 = (numeroLabel_pigment_1 + 1) % pigments_labels.size();
    QString current_label = pigments_labels[numeroLabel_pigment_1];

    ui->pigment_1->setText(current_label);

    render->setLabel_pigment1(current_label);
    render->setLabel_pigment2(current_label);
    render->setSlider_concentration(1.f);

    render->repaint();

    QColor couleur = render->getResultat();
    QPalette pal = ui->pigment_1->palette();
    pal.setColor(QPalette::Button, couleur);

    ui->pigment_1->setAutoFillBackground(true);
    ui->pigment_1->setPalette(pal);
    ui->pigment_1->update();

    stringstream rgbText;
    rgbText << "R : " <<couleur.red() << "  G : " << couleur.green() << "  B : " << couleur.blue();
    std::string rgb_text(rgbText.str());
    ui->RGB->setText(QString(rgb_text.c_str()));
}

void Mixeur::on_pigment_2_clicked(){

    numeroLabel_pigment_2 = (numeroLabel_pigment_2 + 1) % pigments_labels.size();
    QString current_label = pigments_labels[numeroLabel_pigment_2];

    ui->pigment_2->setText(current_label);

    render->setLabel_pigment2(current_label);
    render->setLabel_pigment1(current_label);
    render->setSlider_concentration(1.f);

    render->repaint();

    QColor couleur = render->getResultat();
    QPalette pal = ui->pigment_2->palette();
    pal.setColor(QPalette::Button, couleur);

    ui->pigment_2->setAutoFillBackground(true);
    ui->pigment_2->setPalette(pal);
    ui->pigment_2->update();

    stringstream rgbText;
    rgbText << "R : " <<couleur.red() << "  G : " << couleur.green() << "  B : " << couleur.blue();
    std::string rgb_text(rgbText.str());
    ui->RGB->setText(QString(rgb_text.c_str()));
}

void Mixeur::on_cpu_gpu_clicked(){
    // coming soon;
}

void Mixeur::on_slider_valueChanged(){

    render->setLabel_pigment1(pigments_labels[numeroLabel_pigment_1]);
    render->setLabel_pigment2(pigments_labels[numeroLabel_pigment_2]);
    render->setSlider_concentration(1.f - (ui->slider->value()) / 100.f);                   // slider value 0 -> 99

    render->repaint();
    /*
    QColor couleur = render->getResultat();
    QPalette pal = ui->pigment_3->palette();
    pal.setColor(ui->pigment_3->backgroundRole(), couleur);
    pal.setColor(ui->pigment_3->foregroundRole(), couleur);

    ui->pigment_3->setAutoFillBackground(true);
    ui->pigment_3->setPalette(pal);
    ui->pigment_3->update();
*/
    stringstream pourcentage;
    pourcentage << ui->slider->value() << "%";
    std::string pourcent(pourcentage.str());
    ui->label_pourcentage->setText(QString(pourcent.c_str()));

    QColor couleur = render->getResultat();

    stringstream rgbText;
    rgbText << "R : " <<couleur.red() << "  G : " << couleur.green() << "  B : " << couleur.blue();
    std::string rgb_text(rgbText.str());
    ui->RGB->setText(QString(rgb_text.c_str()));
}

void Mixeur::on_export_clicked()
{
    cout << "Export en cours..." << endl;

}

void Mixeur::mousePressEvent(QMouseEvent *e)
{
    cout << "Right click" << endl;
}
