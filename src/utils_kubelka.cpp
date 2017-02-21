#include <utils_kubelka.h>

int Utils_kubelka::SAMPLES = 101;

Spectre Utils_kubelka::compute_melange(Pigment * pig1, Pigment * pig2, float concentration){

    Spectre melange;
    vector<float> wavelengthsmelange;

    for(int i = 0; i < SAMPLES; i++){
        float km = pig1->getAbsorption().getAmplitude(i) * concentration + pig2->getAbsorption().getAmplitude(i) * (1 - concentration);
        float sm = pig1->getScattering().getAmplitude(i) * concentration + pig2->getScattering().getAmplitude(i) * (1 - concentration);
        //cout << "i = " << i << " km = " << km << " sm = " << sm << endl;
        wavelengthsmelange.push_back(km / sm);
    }

    //cout << "concentration pig 1 = " << pig1->getConcentration() << " concentration pig2 = " << pig2->getConcentration() << endl;
    //cout << "abs pig 1 = " << pig1->getAbsorption().getAmplitude(0) << " abs pig2 = " << pig2->getAbsorption().getAmplitude(0) << endl;

    melange.setAmplitudes(wavelengthsmelange);
    melange.setWavelengths(pig1->getAbsorption().getWavelengthList());

    //for(int i = 0; i < SAMPLES; i++)
        //cout << "melange " << i << " = " << melange.getAmplitude(i) << endl;
    return melange;
}


Spectre Utils_kubelka::compute_reflectance_melange(Spectre melange){

    Spectre reflectance;
    vector<float> wavelengthsreflectance;

    for(int i = 0; i < SAMPLES; i++){
        float amp = melange.getAmplitude(i);
        float r = 1 + amp - sqrt((amp * amp) + 2 * amp);
        wavelengthsreflectance.push_back(r);
    }

    reflectance.setAmplitudes(wavelengthsreflectance);
    reflectance.setWavelengths(melange.getWavelengthList());

    //for(int i = 0; i < SAMPLES; i++)
        //cout << "reflectance " << i << " = " << reflectance.getAmplitude(i) << endl;

    return reflectance;
}

Spectre Utils_kubelka::compute_lumiere_reflechie(Spectre reflectance, Light * incidente){

    Spectre reflechie;
    vector<float> wavelengthsreflechie;

    for(int i = 0; i < SAMPLES; i++){
        float ref = reflectance.getAmplitude(i) * incidente->getSpectre().getAmplitude(i);
        wavelengthsreflechie.push_back(ref);
    }

    reflechie.setAmplitudes(wavelengthsreflechie);
    reflechie.setWavelengths(reflectance.getWavelengthList());

    //for(int i = 0; i < SAMPLES; i++)
        //cout << "reflechie " << i << " = " << reflechie.getAmplitude(i) << endl;

    return reflechie;
}

glm::vec3 Utils_kubelka::convertXYZ(Spectre lumiere_reflect, Light * incidente){

    float X = 0.f;
    float Y = 0.f;
    float Z = 0.f;
    float k = incidente->getK();             // facteur de normalisation

    for(int i = 0; i < SAMPLES; i++){
        X += lumiere_reflect.getAmplitude(i) * CIE_1964_CMFs[i*3];
        Y += lumiere_reflect.getAmplitude(i) * CIE_1964_CMFs[i*3 + 1];
        Z += lumiere_reflect.getAmplitude(i) * CIE_1964_CMFs[i*3 + 2];
    }

    X = k * X;
    Y = k * Y;
    Z = k * Z;

    cout << "XYZ = " << X << " " << Y << " " << Z << endl;
    return glm::vec3(X, Y, Z);
}


glm::vec3 Utils_kubelka::convertRGB(glm::vec3 xyz){

    glm::vec3 rgb = M_D65 * xyz;

    cout << "rgb = " << rgb.x << " " << rgb.y << " " << rgb.z << endl;
    return glm::vec3(rgb.x, rgb.y, rgb.z);
}

/* http://www.brucelindbloom.com/  -    sRGB
 * sRGB -> non linear
*/
glm::vec3 Utils_kubelka::convert_sRGB(glm::vec3 rgb){

    const float epsilon = 0.0031308;
    const float alpha = 0.055;
    float sr, sg, sb;

    if(rgb.x <= epsilon)
        sr = 12.92 * rgb.x;
    else
        sr = (1 + alpha) * pow(rgb.x, 1.f / 2.4f) - alpha;

    if(rgb.y <= epsilon)
        sg = 12.92 * rgb.y;
    else
        sg = (1 + alpha) * pow(rgb.y, 1.f / 2.4f) - alpha;

    if(rgb.z <= epsilon)
        sb = 12.92 * rgb.z;
    else
        sb = (1 + alpha) * pow(rgb.z, 1.f / 2.4f) - alpha;

    glm::vec3 sRGB = glm::vec3(sr, sg, sb);

    return sRGB;
}

glm::vec3 Utils_kubelka::correctionGamma(glm::vec3 rgb, float gamma){

    float r, g, b;

    r = pow(rgb.x, 1.f / gamma);
    g = pow(rgb.y, 1.f / gamma);
    b = pow(rgb.z, 1.f / gamma);

    return glm::vec3(r, g, b);
}

glm::vec3 Utils_kubelka::clipping(glm::vec3 rgb){

    float x, y, z;

    x = std::max(0.f, std::min(rgb.x, 1.f));
    y = std::max(0.f, std::min(rgb.y, 1.f));
    z = std::max(0.f, std::min(rgb.z, 1.f));

    return glm::vec3(x, y, z);
}


/* http://www.brucelindbloom.com/  -    sRGB
 * Attention : A la lecture visuelle de la matrice, lisez transpose(M_D65)
 * Matrice de conversion XYZ -> RGB
*/
const glm::mat3 Utils_kubelka::M_D65 = glm::mat3(
        glm::vec3(3.2404542f, -0.9692660f, 0.0556434f),
        glm::vec3(-1.5371385f, 1.8760108f, -0.2040259f),
        glm::vec3(-0.4985314f, 0.0415560f, 1.0572252f));



const double Utils_kubelka::CIE_1964_CMFs[303] = {

/*
 *      http://www.cvrl.org/cmfs.htm
 *          380 nm -> 780 nm avec pas de 4nm
 *      x                   y               z
 *
*/
    0.000159952000, 0.000017364000, 0.000704776000,
    0.000504550000, 0.000054560000, 0.002228500000,
    0.001446160000, 0.000155640000, 0.006406700000,
    0.003764500000, 0.000402400000, 0.016747000000,
    0.008899600000, 0.000941700000, 0.039802000000,
    0.019109700000, 0.002004400000, 0.086010900000,
    0.037278000000, 0.003880000000, 0.168990000000,
    0.066038000000, 0.006833000000, 0.301900000000,
    0.105836000000, 0.010918000000, 0.489220000000,
    0.152893000000, 0.015717000000, 0.716580000000,
    0.204492000000, 0.021391000000, 0.972542000000,
    0.253793000000, 0.027841000000, 1.224900000000,
    0.295143000000, 0.034738000000, 1.446100000000,
    0.333570000000, 0.042946000000, 1.658900000000,
    0.364482000000, 0.051934000000, 1.839200000000,
    0.383734000000, 0.062077000000, 1.967280000000,
    0.387978000000, 0.072218000000, 2.024400000000,
    0.378709000000, 0.082874000000, 2.015300000000,
    0.361045000000, 0.096275000000, 1.965300000000,
    0.335893000000, 0.109901000000, 1.874100000000,
    0.302273000000, 0.128201000000, 1.745370000000,
    0.264263000000, 0.147787000000, 1.595600000000,
    0.220488000000, 0.170362000000, 1.419900000000,
    0.170222000000, 0.200313000000, 1.205000000000,
    0.120584000000, 0.226170000000, 0.973830000000,
    0.080507000000, 0.253589000000, 0.772125000000,
    0.048117000000, 0.288694000000, 0.606850000000,
    0.023876000000, 0.323335000000, 0.471400000000,
    0.010759000000, 0.358326000000, 0.366399000000,
    0.003982000000, 0.408482000000, 0.283036000000,
    0.003816000000, 0.460777000000, 0.218502000000,
    0.012147000000, 0.516740000000, 0.170281000000,
    0.027690000000, 0.576290000000, 0.129096000000,
    0.049114000000, 0.637830000000, 0.098196000000,
    0.079901000000, 0.701550000000, 0.077744000000,
    0.117749000000, 0.761757000000, 0.060709000000,
    0.161041000000, 0.812140000000, 0.045954000000,
    0.210538000000, 0.854870000000, 0.035384000000,
    0.262972000000, 0.895370000000, 0.025862000000,
    0.318361000000, 0.932550000000, 0.019127000000,
    0.376772000000, 0.961988000000, 0.013676000000,
    0.436517000000, 0.979460000000, 0.008872000000,
    0.497738000000, 0.988320000000, 0.005453000000,
    0.563426000000, 0.995230000000, 0.002646000000,
    0.633948000000, 0.999770000000, 0.000711000000,
    0.705224000000, 0.997340000000, 0.000000000000,
    0.776083000000, 0.986300000000, 0.000000000000,
    0.845879000000, 0.967740000000, 0.000000000000,
    0.909206000000, 0.940981000000, 0.000000000000,
    0.964283000000, 0.905954000000, 0.000000000000,
    1.014160000000, 0.868934000000, 0.000000000000,
    1.062900000000, 0.834393000000, 0.000000000000,
    1.104200000000, 0.797947000000, 0.000000000000,
    1.128000000000, 0.755309000000, 0.000000000000,
    1.134300000000, 0.708281000000, 0.000000000000,
    1.123990000000, 0.658341000000, 0.000000000000,
    1.098000000000, 0.606887000000, 0.000000000000,
    1.056700000000, 0.554490000000, 0.000000000000,
    1.000800000000, 0.501363000000, 0.000000000000,
    0.932800000000, 0.448823000000, 0.000000000000,
    0.856297000000, 0.398057000000, 0.000000000000,
    0.775610000000, 0.350863000000, 0.000000000000,
    0.691290000000, 0.305936000000, 0.000000000000,
    0.602520000000, 0.260990000000, 0.000000000000,
    0.513240000000, 0.217853000000, 0.000000000000,
    0.431567000000, 0.179828000000, 0.000000000000,
    0.360190000000, 0.147535000000, 0.000000000000,
    0.297110000000, 0.119892000000, 0.000000000000,
    0.241300000000, 0.096347000000, 0.000000000000,
    0.192950000000, 0.076583000000, 0.000000000000,
    0.152568000000, 0.060281000000, 0.000000000000,
    0.119480000000, 0.046998000000, 0.000000000000,
    0.092610000000, 0.036297800000, 0.000000000000,
    0.071114000000, 0.027791800000, 0.000000000000,
    0.054050000000, 0.021077900000, 0.000000000000,
    0.040850800000, 0.015905100000, 0.000000000000,
    0.030753000000, 0.011960700000, 0.000000000000,
    0.023052000000, 0.008959900000, 0.000000000000,
    0.017241000000, 0.006697500000, 0.000000000000,
    0.012862000000, 0.004994100000, 0.000000000000,
    0.009576880000, 0.003717740000, 0.000000000000,
    0.007116300000, 0.002762810000, 0.000000000000,
    0.005281900000, 0.002051320000, 0.000000000000,
    0.003925800000, 0.001525350000, 0.000000000000,
    0.002920800000, 0.001135550000, 0.000000000000,
    0.002174960000, 0.000846190000, 0.000000000000,
    0.001620500000, 0.000631010000, 0.000000000000,
    0.001208700000, 0.000471110000, 0.000000000000,
    0.000903600000, 0.000352543000, 0.000000000000,
    0.000676900000, 0.000264375000, 0.000000000000,
    0.000508258000, 0.000198730000, 0.000000000000,
    0.000382490000, 0.000149730000, 0.000000000000,
    0.000288580000, 0.000113106000, 0.000000000000,
    0.000218470000, 0.000085738000, 0.000000000000,
    0.000165970000, 0.000065222000, 0.000000000000,
    0.000126390000, 0.000049737000, 0.000000000000,
    0.000096427000, 0.000038000000, 0.000000000000,
    0.000073729000, 0.000029099000, 0.000000000000,
    0.000056500000, 0.000022333200, 0.000000000000,
    0.000043389000, 0.000017177700, 0.000000000000,
    0.000033411700, 0.000013249000, 0.000000000000,
                                 };
