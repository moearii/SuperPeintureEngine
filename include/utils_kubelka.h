#ifndef UTILS_KUBELKA_H
#define UTILS_KUBELKA_H

#include <spectre.h>
#include <pigment.h>
#include <light.h>
#include <QRgb>
#include <QColor>
#include <vector>
#include <lib/glm/glm.hpp>
#include <lib/glm/gtc/matrix_transform.hpp>
#include <lib/glm/gtc/type_ptr.hpp>

using namespace std;

class Utils_kubelka{

public:

    static vector<Spectre> compute_melange(Pigment * pig1, Pigment * pig2, float concentration);
    static Spectre compute_reflectance_melange(Spectre melange);
    static Spectre compute_lumiere_reflechie(Spectre reflectance, Light * incidente);
    static glm::vec3 convertXYZ(Spectre lumiere_reflect, Light * incidente);
    static glm::vec3 convertRGB(glm::vec3 xyz);
    static glm::vec3 convert_sRGB(glm::vec3 rgb);
    static glm::vec3 correctionGamma(glm::vec3 rgb, float gamma);
    static glm::vec3 clipping(glm::vec3 rgb);

    static int SAMPLES;

private:

    static const double CIE_1964_CMFs[303];
    static const glm::mat3 M_D65;
};



#endif // UTILS_KUBELKA_H
