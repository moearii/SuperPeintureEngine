#include "mixeur.h"
#include "ui_mixeur.h"

Mixeur::Mixeur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mixeur)
{
    ui->setupUi(this);

    ui->render->initializeGL();                     // Pour que l'initialisation se soit bien executée avant ce qui suit

    ui->render->show();                          // debug

    pigments_labels = ui->render->getPigmentsLabels();
    numeroLabel_pigment_1 = 0;
    numeroLabel_pigment_2 = 0;

//    connect(ui->pigment_1,SIGNAL(clicked()),this,SLOT(on_pigment_1_clicked()));
//    connect(ui->pigment_2,SIGNAL(clicked()),this,SLOT(on_pigment_2_clicked()));
}

Mixeur::~Mixeur()
{
    delete ui;
}

void Mixeur::on_pigment_1_clicked()
{
    numeroLabel_pigment_1 = (numeroLabel_pigment_1 + 1) % pigments_labels.size();
    QString current_label = pigments_labels[numeroLabel_pigment_1];

    ui->pigment_1->setText(current_label);

    ui->render->setLabel_pigment1(current_label);
    ui->render->setLabel_pigment2(current_label);
    ui->render->setSlider_concentration(1.f);

    ui->render->repaint();

    QColor couleur = ui->render->getResultat();
    QPalette pal = ui->pigment_1->palette();
    pal.setColor(QPalette::Button, couleur);

    ui->pigment_1->setAutoFillBackground(true);
    ui->pigment_1->setPalette(pal);
    ui->pigment_1->update();

    update_rgb(couleur);
    update_xyz(ui->render->getXYZ());
}

void Mixeur::on_pigment_2_clicked(){

    numeroLabel_pigment_2 = (numeroLabel_pigment_2 + 1) % pigments_labels.size();
    QString current_label = pigments_labels[numeroLabel_pigment_2];

    ui->pigment_2->setText(current_label);

    ui->render->setLabel_pigment2(current_label);
    ui->render->setLabel_pigment1(current_label);
    ui->render->setSlider_concentration(1.f);

    ui->render->repaint();

    QColor couleur = ui->render->getResultat();
    QPalette pal = ui->pigment_2->palette();
    pal.setColor(QPalette::Button, couleur);

    ui->pigment_2->setAutoFillBackground(true);
    ui->pigment_2->setPalette(pal);
    ui->pigment_2->update();

    update_rgb(couleur);
    update_xyz(ui->render->getXYZ());
}

void Mixeur::on_cpu_gpu_clicked(){
    // TODO
}

void Mixeur::on_slider_valueChanged(){

    ui->render->setLabel_pigment2(pigments_labels[numeroLabel_pigment_2]);
    ui->render->setLabel_pigment1(pigments_labels[numeroLabel_pigment_1]);
    ui->render->setSlider_concentration(1.f - (ui->slider->value()) / 100.f);                   // slider value 0 -> 99

    ui->render->repaint();

    stringstream pourcentage;
    pourcentage << ui->slider->value() << "%";
    std::string pourcent(pourcentage.str());
    ui->label_pourcentage->setText(QString(pourcent.c_str()));

    QColor couleur = ui->render->getResultat();

    update_rgb(couleur);
    update_xyz(ui->render->getXYZ());
}

void Mixeur::update_rgb(QColor & rgb){
    stringstream rgbText;
    rgbText << "R : " << rgb.red() << "  G : " << rgb.green() << "  B : " << rgb.blue();
    std::string rgb_text(rgbText.str());
    ui->RGB->setText(QString(rgb_text.c_str()));
}

void Mixeur::update_xyz(std::vector<float> xyz){
    stringstream x, y, z;
    x << "X : " << xyz[0];
    y << "Y : " << xyz[1];
    z << "Z : " << xyz[2];

    std::string x_text(x.str());
    std::string y_text(y.str());
    std::string z_text(z.str());

    ui->X->setText(QString(x_text.c_str()));
    ui->Y->setText(QString(y_text.c_str()));
    ui->Z->setText(QString(z_text.c_str()));
}

void Mixeur::on_exporter_clicked()
{
    QString directoryName = QFileDialog::getSaveFileName(this, "Enregistrer un fichier pigment");

    Pigment * pig1 = ui->render->getPigmentfromLabel(pigments_labels[numeroLabel_pigment_1]);
    Pigment * pig2 = ui->render->getPigmentfromLabel(pigments_labels[numeroLabel_pigment_2]);
    float concentration = ui->render->getSlider_concentration();
    vector<Spectre> spectres = Utils_kubelka::compute_melange(pig1,pig2,concentration);

    ui->render->parseur->exportDataToFilePigment(directoryName,spectres.at(1),spectres.at(2));
}

