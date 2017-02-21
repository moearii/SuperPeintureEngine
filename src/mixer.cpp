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
//    connect(ui->concentrationSlider,SIGNAL(valueChanged(int)),this,SLOT(updateColor()));
}

void Mixer::initMixer()
{
    // Initialize renderer
    mixerRenderer->initializeGL();

    // Initialize viewer
    viewerLayout = new QGridLayout();
    viewerLayout->addWidget(mixerRenderer);
    ui->pigmentWidget->setLayout(viewerLayout);

}

void Mixer::updateColor()
{
//    mixerRenderer->paintGL();
//    QColor color = QColor(mixerRenderer->test[0],
//                          mixerRenderer->test[1],
//                          mixerRenderer->test[2]);
//    ui->pigmentWidget->setAutoFillBackground(true);
//    QPalette pal = palette();
//    pal.setColor(QPalette::Background,color);
//    ui->pigmentWidget->setPalette(pal);
//    ui->pigmentWidget->repaint();
}

Mixer::~Mixer()
{
    delete ui;
    delete viewerLayout;
}
