#ifndef PIPELINE_GPU_H
#define PIPELINE_GPU_H

#include <pipeline.h>
#include <QRgb>
#include <QColor>


class Pipeline_GPU: public Pipeline{

public:

    Pipeline_GPU();
    virtual ~Pipeline_GPU();

    virtual void run_8_samples(Pigment * pig1, Pigment * pig2, Light * lum, glm::vec3 & couleur);
    virtual void run_full_samples(Pigment * pig1, Pigment * pig2, Light * lum, glm::vec3 & couleur);

private:

    GLuint rgbtexture;
};

#endif // PIPELINE_GPU_H
