/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The Torus class
*  This is a subclass of SceneObject, and hence implements the
*  methods intersect() and normal().
-------------------------------------------------------------*/

#include "Torus.h"
#include <math.h>
#include <iostream>

#include "algebra.h"


glm::vec3 rotate(glm::vec3 p, glm::vec3 direction) {
    // Calculate change-of-basis matrix
    glm::mat3 transform;

    if (direction.x == 0 && direction.z == 0)
    {
        if (direction.y < 0) // rotate 180 degrees
        {
            transform = glm::mat3(glm::vec3(-1.0, 0.0, 0.0),
                                  glm::vec3( 0.0, -1.0, 0.0),
                                  glm::vec3( 0.0,  0.0, 1.0));
        }

        // else if direction.y >= 0, leave transform as the identity matrix.
    }
    else
    {
        glm::vec3 new_y = glm::normalize(direction);
        glm::vec3 new_z = glm::normalize(glm::cross(new_y, glm::vec3(0, 1, 0)));
        glm::vec3 new_x = glm::normalize(glm::cross(new_y, new_z));

        transform = glm::mat3(new_x, new_y, new_z);
    }

    return transform * p;
}

float Torus::intersectHalf(glm::vec3 p0, glm::vec3 dir) {

    double G = 4*A*A*(dir.x*dir.x + dir.y*dir.y);
    double H = 8*A*A*(p0.x*dir.x + p0.y*dir.y);
    double I = 4*A*A*(p0.x*p0.x + p0.y*p0.y);
    double J = dir.x*dir.x + dir.y*dir.y + dir.z*dir.z;
    double K = 2*(p0.x*dir.x + p0.y*dir.y + p0.z*dir.z);
    double L = p0.x*p0.x + p0.y*p0.y + p0.z*p0.z + A*A - B*B;



    double roots[4];

    int numRoots = Algebra::SolveQuarticEquation(
        J*J,
        2*J*K,
        2*J*L + K*K - G,
        2*K*L - H,
        L*L - I,
        roots);
    
    float t = -1;
    for (int i = 0; i < numRoots; i++) {
        if (roots[i] > 0) {
            t = roots[i];
            break;
        }
    }

    return t;
}


// Update the intersect method with the implementation of the 
// A = radius to the center of the tube
// B = radius of the tube
// A > B
float Torus::intersect(glm::vec3 p0, glm::vec3 dir) {

    p0 = p0 - center;

    // check intersection with half torus
    float t1 = intersectHalf(p0, dir);

    // rotate p0 and dir by 180 degrees around the y-axis
    glm::vec3 p0_rot = rotate(p0, glm::vec3(0, -1, 0));
    glm::vec3 dir_rot = rotate(dir, glm::vec3(0, -1, 0));


    //check intersection with other half torus
    float t2 = intersectHalf(p0_rot, dir_rot);


    return t1;
}


/**
* Returns the unit normal vector at a given point.
* Assumption: The input point p lies on the sphere.
*/
glm::vec3 Torus::normal(glm::vec3 p) {
    
    double a = 1.0 - (A / sqrt(p.x*p.x + p.z*p.z));
    return glm::vec3(p.x*a, p.y, p.z*a);
}
