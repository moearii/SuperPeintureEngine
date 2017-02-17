#ifndef PIPELINE_H
#define PIPELINE_H

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <string>
#include <QRgb>
#include <QColor>
#include <pigment.h>
#include <light.h>
#include <lib/glm/glm.hpp>
#include <lib/glm/gtc/matrix_transform.hpp>
#include <lib/glm/gtc/type_ptr.hpp>

class Pipeline{

public:

    virtual ~Pipeline(){}

    virtual void run_8_samples(Pigment * pig1, Pigment * pig2, Light * lum, glm::vec3 & couleur) = 0;
    virtual void run_full_samples(Pigment * pig1, Pigment * pig2, Light * lum, glm::vec3 & couleur) = 0;


private:


};


#endif // PIPELINE_H
