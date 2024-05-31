/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The Torus class
*  This is a subclass of SceneObject, and hence implements the
*  methods intersect() and normal().
-------------------------------------------------------------*/

#ifndef H_TORUS
#define H_TORUS

#include <glm/glm.hpp>
#include "SceneObject.h"

class Torus : public SceneObject
{
private:
	
	glm::vec3 center = glm::vec3(0);
    float A = 0.0;
	float B = 0.0;


public:	
	Torus() = default;
	
	Torus(glm::vec3 pa, float a, float b) : 
        center(pa), A(a), B(b) {}


	bool isInside(glm::vec3 pt);
	
	float intersect(glm::vec3 posn, glm::vec3 dir);

	float intersectHalf(glm::vec3 posn, glm::vec3 dir);


	
	glm::vec3 normal(glm::vec3 pt);

};

#endif //!H_TORUS
