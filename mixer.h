#ifndef MIXER_H
#define MIXER_H

#include <QDialog>

namespace Ui {
class Mixer;
}

class Mixer : public QDialog
{
    Q_OBJECT

public:
    explicit Mixer(QWidget *parent = 0);
    ~Mixer();

private:
    Ui::Mixer *ui;
};

#endif // MIXER_H
