#ifndef MIXER_H
#define MIXER_H

#include <QDialog>
#include <QMainWindow>
#include <QWidget>
#include <QGLWidget>
#include <QGridLayout>

#include "renderingwidget.h"


namespace Ui {
class RenderingWidget;

class Mixer;
}

class Mixer : public QDialog
{
    Q_OBJECT

public:
    explicit Mixer(RenderingWidget *renderer, QWidget *parent = 0);
    ~Mixer();

    void setGlWidget(RenderingWidget* widget) {
        mixerRenderer = widget;
    }

private slots:
    void initMixer();
    void updateColor();

private:
    RenderingWidget *mixerRenderer;
    Ui::Mixer *ui;
    QGridLayout *viewerLayout;
};

#endif // MIXER_H
