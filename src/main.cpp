#include <iostream>
#include <string>
#include <fstream>

#include <GL/gl.h>
#include <QApplication>

#include "renderingwidget.h"
#include "mixeur.h"

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    Mixeur mixeur;
    mixeur.show();

    return application.exec();
}


