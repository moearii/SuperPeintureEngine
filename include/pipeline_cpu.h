#ifndef PIPELINE_CPU_H
#define PIPELINE_CPU_H

#include <pipeline.h>
#include <QRgb>
#include <QColor>
#include <utils_kubelka.h>


class Pipeline_CPU: public Pipeline{

public:

    Pipeline_CPU();
    virtual ~Pipeline_CPU();

    virtual void run_8_samples(Pigment * pig1, Pigment * pig2, Light * lum, glm::vec3 & couleur);
    virtual void run_full_samples(Pigment * pig1, Pigment * pig2, Light * lum, glm::vec3 & couleur);

private:

};

#endif // PIPELINE_CPU_H
