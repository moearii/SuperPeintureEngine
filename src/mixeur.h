#ifndef MIXEUR_H
#define MIXEUR_H

#include <QMainWindow>
#include <QFileDialog>
#include "renderingwidget.h"
#include <vector>
#include <sstream>

namespace Ui {
class Mixeur;
}

class Mixeur : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Mixeur(QWidget *parent = 0);
    ~Mixeur();
    

private slots:
    void on_pigment_1_clicked();
    void on_pigment_2_clicked();
    void on_cpu_gpu_clicked();

    void on_slider_valueChanged();

    void on_exporter_clicked();

private:

    void update_rgb(QColor & rgb);
    void update_xyz(std::vector<float> xyz);

    Ui::Mixeur *ui;
    std::vector<QString> pigments_labels;

    int numeroLabel_pigment_1;
    int numeroLabel_pigment_2;

};

#endif // MIXEUR_H
