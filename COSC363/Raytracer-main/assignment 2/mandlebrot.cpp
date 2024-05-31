#include "mandlebrot.h"
#include <glm/glm.hpp>


// Function to compute the Mandelbrot set
int mandelbrot(double cr, double ci, int max_iter)
{
    int i = 0;
    double zr = 0.0, zi = 0.0;
    while (i < max_iter && zr*zr + zi*zi < 4.0)
    {
        double temp = zr*zr - zi*zi + cr;
        zi = 2.0*zr*zi + ci;
        zr = temp;
        i++;
    }
    return i + 1 - std::log(std::log2(abs(zr*zi)));
}

glm::vec3 hsv2rgb(double fH, double fS, double fV)
{
    float fC = fV * fS; // Chroma
    float fHPrime = fmod(fH / 60.0, 6);
    float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
    float fM = fV - fC;
    float fR, fG, fB;
    
    if(0 <= fHPrime && fHPrime < 1) {
        fR = fC;
        fG = fX;
        fB = 0;
    } else if(1 <= fHPrime && fHPrime < 2) {
        fR = fX;
        fG = fC;
        fB = 0;
    } else if(2 <= fHPrime && fHPrime < 3) {
        fR = 0;
        fG = fC;
        fB = fX;
    } else if(3 <= fHPrime && fHPrime < 4) {
        fR = 0;
        fG = fX;
        fB = fC;
    } else if(4 <= fHPrime && fHPrime < 5) {
        fR = fX;
        fG = 0;
        fB = fC;
    } else if(5 <= fHPrime && fHPrime < 6) {
        fR = fC;
        fG = 0;
        fB = fX;
    } else {
        fR = 0;
        fG = 0;
        fB = 0;
    }
    
    fR += fM;
    fG += fM;
    fB += fM;
    return glm::vec3(fR, fG, fB);     
}

glm::vec3 getColorInSet(float x, float y)
{
    int max_iter = 20;
    int iter = mandelbrot(x, y, max_iter);
    double hue = (iter*360.0)/max_iter;
    double saturation = 1.0;
    double value;
    if(iter < max_iter)
        value = 1.0;
    else
        value = 0.0;
    return hsv2rgb(hue, saturation, value);
}

