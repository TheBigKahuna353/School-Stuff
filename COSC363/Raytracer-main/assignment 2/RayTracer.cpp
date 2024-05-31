/*==================================================================================
* COSC 363  Computer Graphics
* Department of Computer Science and Software Engineering, University of Canterbury.
*
* A basic ray tracer
* See Lab07.pdf   for details.
*===================================================================================
*/
#include <iostream>
#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include "Sphere.h"
#include "SceneObject.h"
#include "Ray.h"
#include <GL/freeglut.h>
#include "Plane.h"
#include "TextureBMP.h"
#include "world.h"
#include "mandlebrot.h"
#include <chrono>

using namespace std;

const float EDIST = 40.0;
const int NUMDIV = 600;
const int MAX_STEPS = 10;
const float XMIN = -10.0;
const float XMAX = 10.0;
const float YMIN = -10.0;
const float YMAX = 10.0;
const bool USEAAA = true;
const bool SOFTSHADOWS = true;

glm::vec3 eye(0., 0., 40.);
long numTraces = 0;

TextureBMP texture;

vector<SceneObject*> sceneObjects;




//---The most important function in a ray tracer! ---------------------------------- 
//   Computes the colour value obtained by tracing a ray and finding its 
//     closest point of intersection with objects in the scene.
//----------------------------------------------------------------------------------
glm::vec3 trace(Ray ray, int step)
{
	numTraces++;
	glm::vec3 backgroundCol(0);						//Background colour = (0,0,0)
	glm::vec3 lightPos(0, 14, -30);					//Light's position
	glm::vec3 color(0);
	SceneObject* obj;

    ray.closestPt(sceneObjects);					//Compare the ray with all objects in the scene
    if(ray.index == -1) return backgroundCol;		//no intersection
	obj = sceneObjects[ray.index];					//object on which the closest point of intersection is found

	if (ray.index == 3)
	{
		//Stripe pattern
		int stripeWidth = 5;
		int iz = (ray.hit.z) / stripeWidth;
		int ix = (ray.hit.x) / stripeWidth + 1000;
		// if (ix < 0) ix++; //for negative values of x (floor function)
		int j = ix % 2;
		int k = iz % 2; //2 colors
		if (k == 0) {
			if (j == 0) color = glm::vec3(1, 1, 1);
			else color = glm::vec3(0, 0, 0);
		}
		else {
			if (j == 0) color = glm::vec3(0, 0, 0);
			else color = glm::vec3(1, 1, 1);
		}
		obj->setColor(color);

		//Add code for texture mapping here
		float x1 = -15;
		float x2 = 5;
		float z1 = -60;
		float z2 = -90;
		float texcoords = (ray.hit.x - x1)/(x2-x1);
		float texcoordt = (ray.hit.z - z1)/(z2-z1);
		if(texcoords > 0 && texcoords < 1 &&
		texcoordt > 0 && texcoordt < 1)
		{
			color=texture.getColorAt(texcoords, texcoordt);
			obj->setColor(color);
		}
	}
	if (ray.index == 11) {
		// mandlebrot set
		float z0 = ray.hit.z / 10;
		float y0 = ray.hit.y/10;

		obj->setColor(getColorInSet(z0 + 3, y0));
	}

	color = obj->lighting(lightPos, -ray.dir, ray.hit);						//Object's colour

	if (ray.index == 6) {
		glm::vec3 new_light(0, 10, -30);
		color = obj->lighting(new_light, -ray.dir, ray.hit);
	}
	
	if (SOFTSHADOWS) {
		// 1 center shadow rar, 4 surrounding shadows rays
		glm::vec3 shadowCol = glm::vec3(0);
		Ray shadowRay;
		SceneObject* shadowObj;
		const int xNum = 4;
		const int zNum = 4;
		const double size = 6/xNum;
		for (int i = -xNum/2; i < xNum/2; i++) {
			for (int j = -zNum/2; j < zNum/2; j++) {
				double x = lightPos.x + i * size;
				double z = lightPos.z + j * size;
				glm::vec3 new_lightPos = glm::vec3(x + (rand() % (int)(size*100))/100.0f, lightPos.y, z + (rand() % (int)(size*100))/100.0f);
				shadowRay = Ray(ray.hit, new_lightPos - ray.hit);
				shadowRay.closestPt(sceneObjects);
				shadowObj = sceneObjects[shadowRay.index];
				if (shadowRay.index != 6 && shadowRay.dist < glm::length(lightPos - ray.hit)) {
					float shadowCoeff = (shadowObj->isRefractive() || shadowObj->isTransparent()) ? 0.7 : 0.5;
					shadowCol = shadowCol + color * shadowCoeff;
				} else {
					shadowCol = shadowCol + color;

				}
			}
		}
		shadowCol = shadowCol / (float)(xNum * zNum);
		color = shadowCol;
	} else {
		Ray shadowRay;
		SceneObject* shadowObj;
		shadowRay = Ray(ray.hit, lightPos - ray.hit);
		shadowRay.closestPt(sceneObjects);
		shadowObj = sceneObjects[shadowRay.index];
		if (shadowRay.index != 6 && shadowRay.dist < glm::length(lightPos - ray.hit)) {
			float shadowCoeff = (shadowObj->isRefractive() || shadowObj->isTransparent()) ? 0.7 : 0.5;
			color = color * shadowCoeff;
		}
	}

	if (obj->isReflective() && step < MAX_STEPS)
	{	
		float rho = obj->getReflectionCoeff();
		glm::vec3 normalVec = obj->normal(ray.hit);
		glm::vec3 reflectedDir = glm::reflect(ray.dir, normalVec);
		Ray reflectedRay(ray.hit, reflectedDir);
		glm::vec3 reflectedColor = trace(reflectedRay, step + 1);
		color = color + (rho * reflectedColor);
		if (rho == 1.0f) color = reflectedColor;
		
	}

	if (obj->isRefractive() && step < MAX_STEPS)
	{
		float eta = 1.0f / obj->getRefractiveIndex();
		glm::vec3 normalVec = obj->normal(ray.hit);
		glm::vec3 g = glm::refract(ray.dir, normalVec, eta);
		Ray refractedRay(ray.hit, g);
		refractedRay.closestPt(sceneObjects);
		glm::vec3 m = obj->normal(refractedRay.hit);
		glm::vec3 h = glm::refract(g, -m, 1.0f / eta);
		Ray finalRay(refractedRay.hit, h);
		glm::vec3 refractedColor = trace(finalRay, step + 1);
		color = color + refractedColor;
	}

	if (obj->isTransparent() && step < MAX_STEPS)
	{
		float tau = obj->getTransparencyCoeff();
		glm::vec3 normalVec = obj->normal(ray.hit);
		glm::vec3 refractedDir = glm::refract(ray.dir, normalVec, 1.0f/ obj->getRefractiveIndex());
		Ray refractedRay(ray.hit, refractedDir);
		refractedRay.closestPt(sceneObjects);
		Ray finalRay(refractedRay.hit, refractedDir);
		glm::vec3 refractedColor = trace(finalRay, step + 1);
		color = color + (tau * refractedColor);
	}


	return color;
}

glm::vec3 subdivideCell(float x, float y, float cellX, float cellY, int step) {
	// cast 4 rays
	glm::vec3 dir1(x + 0.25 * cellX, y + 0.25 * cellY, -EDIST);
	glm::vec3 dir2(x + 0.75 * cellX, y + 0.25 * cellY, -EDIST);
	glm::vec3 dir3(x + 0.25 * cellX, y + 0.75 * cellY, -EDIST);
	glm::vec3 dir4(x + 0.75 * cellX, y + 0.75 * cellY, -EDIST);

	Ray ray1 = Ray(eye, dir1);
	Ray ray2 = Ray(eye, dir2);
	Ray ray3 = Ray(eye, dir3);
	Ray ray4 = Ray(eye, dir4);

	glm::vec3 col1 = trace(ray1, 1);
	glm::vec3 col2 = trace(ray2, 1);
	glm::vec3 col3 = trace(ray3, 1);
	glm::vec3 col4 = trace(ray4, 1);

	// if all the colours are the same, return the colour
	if (col1 == col2 && col2 == col3 && col3 == col4) return col1;

	if (step >= 1) return (col1 + col2 + col3 + col4) / 4.0f;

	// else, subdivide the cell
	glm::vec3 col5 = subdivideCell(x, y, cellX / 2, cellY / 2, step + 1);
	glm::vec3 col6 = subdivideCell(x + cellX / 2, y, cellX / 2, cellY / 2, step + 1);
	glm::vec3 col7 = subdivideCell(x, y + cellY / 2, cellX / 2, cellY / 2, step + 1);
	glm::vec3 col8 = subdivideCell(x + cellX / 2, y + cellY / 2, cellX / 2, cellY / 2, step + 1);

	return (col5 + col6 + col7 + col8) / 4.0f;
}


//---The main display module -----------------------------------------------------------
// In a ray tracing application, it just displays the ray traced image by drawing
// each cell as a quad.
//---------------------------------------------------------------------------------------
void display()
{
	auto start = std::chrono::high_resolution_clock::now();
	float xp, yp;  //grid point
	float cellX = (XMAX - XMIN) / NUMDIV;  //cell width
	float cellY = (YMAX - YMIN) / NUMDIV;  //cell height

	glm::vec3 window[NUMDIV][NUMDIV];

	glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glBegin(GL_QUADS);  //Each cell is a tiny quad.

	for (int i = 0; i < NUMDIV; i++)	//Scan every cell of the image plane
	{
		xp = XMIN + i * cellX;
		for (int j = 0; j < NUMDIV; j++)
		{
			yp = YMIN + j * cellY;

			// cast 1 ray per pixel

			glm::vec3 dir(xp + 0.5 * cellX, yp + 0.5 * cellY, -EDIST);	//direction of the primary ray

			Ray ray = Ray(eye, dir);

			glm::vec3 col = trace(ray, 1); //Trace the primary ray and get the colour value

			window[i][j] = col;

			if (!USEAAA) {
				glColor3f(col.r, col.g, col.b);
				glVertex2f(xp, yp);				//Draw each cell with its color value
				glVertex2f(xp + cellX, yp);
				glVertex2f(xp + cellX, yp + cellY);
				glVertex2f(xp, yp + cellY);
			}
			
		}
	}

	if (USEAAA) {
		for (int i = 0; i < NUMDIV; i++)	//Scan every cell of the image plane
		{
			xp = XMIN + i * cellX;
			for (int j = 0; j < NUMDIV; j++)
			{
				yp = YMIN + j * cellY;

				glm::vec3 col = window[i][j];
				// check neighbouring pixels
				glm::vec3 col1 = window[i][j];
				glm::vec3 col2 = window[i][j];
				glm::vec3 col3 = window[i][j];
				glm::vec3 col4 = window[i][j];

				if (i > 0) col1 = window[i - 1][j];
				if (i < NUMDIV - 1) col2 = window[i + 1][j];
				if (j > 0) col3 = window[i][j - 1];
				if (j < NUMDIV - 1) col4 = window[i][j + 1];

				// if different, subdivide
				if (col != col1 || col != col2 || col != col3 || col != col4)
				{
					col = subdivideCell(xp, yp, cellX, cellY, 0);
				}


				glColor3f(col.r, col.g, col.b);
				glVertex2f(xp, yp);				//Draw each cell with its color value
				glVertex2f(xp + cellX, yp);
				glVertex2f(xp + cellX, yp + cellY);
				glVertex2f(xp, yp + cellY);
			}
		}
	}


    glEnd();
    glFlush();
	std::cout << "Number of traces: " << numTraces << std::endl;

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";
}



//---This function initializes the scene ------------------------------------------- 
//   Specifically, it creates scene objects (spheres, planes, cones, cylinders etc)
//     and add them to the list of scene objects.
//   It also initializes the OpenGL 2D orthographc projection matrix for drawing the
//     the ray traced image.
//----------------------------------------------------------------------------------
void initialize()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(XMIN, XMAX, YMIN, YMAX);

    glClearColor(0, 0, 0, 1);

	createObjects();

}


int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Raytracing");

    glutDisplayFunc(display);
    initialize();

    glutMainLoop();
    return 0;
}
