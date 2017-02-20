#include "mixer.h"
#include "ui_mixer.h"

Mixer::Mixer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mixer)
{
    ui->setupUi(this);
}

Mixer::~Mixer()
{
    delete ui;
}
