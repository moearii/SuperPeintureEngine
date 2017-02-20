#include "mixer.h"
#include "ui_mixer.h"

#include "renderingwidget.h"

Mixer::Mixer(RenderingWidget *renderer, QWidget *parent) :
    QDialog(parent),
    mixerRenderer(renderer),
    ui(new Ui::Mixer)
{
    ui->setupUi(this);
    initMixer();
}

void Mixer::initMixer()
{
    printColor();
}

void Mixer::printColor()
{
   // mixerRenderer->paintGL();
    QColor color = QColor(mixerRenderer->test[0],
                          mixerRenderer->test[1],
                          mixerRenderer->test[2]);
    ui->pigmentWidget->setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Background,color);
    ui->pigmentWidget->setPalette(pal);
    ui->pigmentWidget->repaint();
    mixerRenderer->show();

}

Mixer::~Mixer()
{
    delete ui;
}
