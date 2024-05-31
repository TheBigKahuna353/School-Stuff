/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The sphere class
*  This is a subclass of SceneObject, and hence implements the
*  methods intersect() and normal().
-------------------------------------------------------------*/

#include "Csg.h"
#include <math.h>
#include <iostream>


float* Csg::intersectMain(glm::vec3 p0, glm::vec3 dir)
{
    glm::vec3 vdif = p0 - center;   //Vector s (see Slide 28)
    float b = glm::dot(dir, vdif);
    float len = glm::length(vdif);
    float c = len*len - radius*radius;
    float delta = b*b - c;
   
    if(delta < 0.001) return new float[] {-1, -1};    //includes zero and negative values

    float t1 = -b - sqrt(delta);
    float t2 = -b + sqrt(delta);

    float* result = new float[2];
    result[0] = t1;
    result[1] = t2;
    return result;
}

float* Csg::intersectSecondary(glm::vec3 p0, glm::vec3 dir)
{
    glm::vec3 dif = glm::vec3(-1, 0, 0);
    glm::vec3 vdif = p0 - (center + dif);   //Vector s (see Slide 28)
    float b = glm::dot(dir, vdif);
    float len = glm::length(vdif);
    float c = len*len - radius*radius;
    float delta = b*b - c;
   
    if(delta < 0.001) return new float[] {-1, -1};    //includes zero and negative values

    float t1 = -b - sqrt(delta);
    float t2 = -b + sqrt(delta);

    float* result = new float[2];
    result[0] = t1;
    result[1] = t2;
    return result;
}

bool hasPositive(float* arr)
{
    return arr[0] > 0 || arr[1] > 0;
}

/**
* Sphere's intersection method.  The input is a ray. 
*/
float Csg::intersect(glm::vec3 p0, glm::vec3 dir)
{
    float* result = intersectMain(p0, dir);
    float* result2 = intersectSecondary(p0, dir);

    if (!hasPositive(result)) return -1; // doesnt intersect with main sphere

    if (hasPositive(result2)) {
        if (result[0] < result2[0]) {
            return result[0];   // intersects main sphere first
        } else {
            if (result2[1] < result[1]) {
                return result2[1];  // intersects secondary sphere first
            } else {
                return -1;  // weird edge case
            }
        }
    } else {
        return result[0]; // only intersects with main sphere
    }
        
}


float get_distance(glm::vec3 p, glm::vec3 q)
{
    return sqrt(pow(p.x - q.x, 2) + pow(p.y - q.y, 2) + pow(p.z - q.z, 2));
}

/**
* Returns the unit normal vector at a given point.
* Assumption: The input point p lies on the sphere.
*/
glm::vec3 Csg::normal(glm::vec3 p)
{
    glm::vec3 dif = glm::vec3(-1, 0, 0);
    if (get_distance(p, center+dif) <= radius + 0.001) {
        glm::vec3 n = p - (center + dif);
        n = glm::normalize(n);
        return -n;
    } else {
        glm::vec3 n = p - center;
        n = glm::normalize(n);
        return n;
    }
}
