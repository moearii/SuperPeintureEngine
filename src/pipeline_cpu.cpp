#include <pipeline_cpu.h>


Pipeline_CPU::Pipeline_CPU(){

}

Pipeline_CPU::~Pipeline_CPU(){

}

void Pipeline_CPU::run_8_samples(Pigment * pig1, Pigment * pig2, float concentration, Light * lum, glm::vec3 & couleur, glm::vec3 & xyz){
    // need Hi et lamdi
}

void Pipeline_CPU::run_full_samples(Pigment * pig1, Pigment * pig2, float concentration, Light * lum, glm::vec3 & couleur, glm::vec3 & xyz){

    vector<Spectre> melange = Utils_kubelka::compute_melange(pig1, pig2, concentration);
    Spectre reflectance = Utils_kubelka::compute_reflectance_melange(melange.at(0));
    Spectre reflechie = Utils_kubelka::compute_lumiere_reflechie(reflectance, lum);

    xyz = Utils_kubelka::convertXYZ(reflechie, lum);
    glm::vec3 rgb = Utils_kubelka::convertRGB(xyz);

    rgb = Utils_kubelka::correctionGamma(rgb, 2.2f);

    couleur = Utils_kubelka::clipping(rgb);
}
