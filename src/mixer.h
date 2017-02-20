#ifndef MIXER_H
#define MIXER_H

#include <QDialog>
#include <QWidget>
#include <QGLWidget>
#include "renderingwidget.h"

class RenderingWidget;

namespace Ui {
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

    void initMixer();
    void printColor();

private:
    RenderingWidget *mixerRenderer;
    Ui::Mixer *ui;
};

#endif // MIXER_H
