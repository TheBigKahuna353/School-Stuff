/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The sphere class
*  This is a subclass of SceneObject, and hence implements the
*  methods intersect() and normal().
-------------------------------------------------------------*/

#ifndef H_CSG
#define H_CSG
#include <glm/glm.hpp>
#include "SceneObject.h"

/**
 * Defines a simple Sphere located at 'center'
 * with the specified radius
 */
class Csg : public SceneObject
{

private:
    glm::vec3 center = glm::vec3(0);
    float radius = 1;

public:
	Csg() {};  //Default constructor creates a unit sphere

	Csg(glm::vec3 c, float r) : center(c), radius(r) {}

	float intersect(glm::vec3 p0, glm::vec3 dir);

    float* intersectMain(glm::vec3 p0, glm::vec3 dir);

    float* intersectSecondary(glm::vec3 p0, glm::vec3 dir);

	glm::vec3 normal(glm::vec3 p);

};

#endif //!H_CSG
