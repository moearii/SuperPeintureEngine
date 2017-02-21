#include <pipeline_gpu.h>



Pipeline_GPU::Pipeline_GPU(){

    glGenTextures(1, &rgbtexture);

    glBindTexture(GL_TEXTURE_2D, rgbtexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 1, 1, 0, GL_RGBA, GL_FLOAT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);



}

Pipeline_GPU::~Pipeline_GPU(){

}

void Pipeline_GPU::run_8_samples(Pigment * pig1, Pigment * pig2, float concentration, Light * lum, glm::vec3 & couleur, glm::vec3 & xyz){

}

void Pipeline_GPU::run_full_samples(Pigment * pig1, Pigment * pig2, float concentration, Light * lum, glm::vec3 & couleur, glm::vec3 & xyz){

}
