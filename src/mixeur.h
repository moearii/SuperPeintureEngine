#ifndef MIXEUR_H
#define MIXEUR_H

#include <QMainWindow>
#include "renderingwidget.h"
#include <vector>
#include <sstream>
#include <QMouseEvent>

#include "configxml.h"

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
    void on_export_clicked();

    void on_slider_valueChanged();

protected:
    void mousePressEvent(QMouseEvent *e);

private:
    Ui::Mixeur *ui;
    RenderingWidget * render;
    std::vector<QString> pigments_labels;

    int numeroLabel_pigment_1;
    int numeroLabel_pigment_2;

};

#endif // MIXEUR_H
