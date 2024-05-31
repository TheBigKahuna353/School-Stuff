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
#include "Torus.h"
#include "Csg.h"
using namespace std;

extern vector<SceneObject*> sceneObjects;


void createObjects() {
    Sphere *sphere1 = new Sphere(glm::vec3(-8.0, -6.0, -10.0), 2.0);
	sphere1->setColor(glm::vec3(1, 1, 1));   //Set colour to blue
	sphere1->setReflectivity(true, 0.6);
	sceneObjects.push_back(sphere1);		 //Add sphere to scene objects

	// Sphere *sphere2 = new Sphere(glm::vec3(8.0, -7.0, -10.0), 1.0);
	// sphere2->setColor(glm::vec3(0, 1, 0));   //Set colour to green
    // sphere2->setTransparency(true, 0.5);
	// sceneObjects.push_back(sphere2);		 //Add sphere to scene objects

	Sphere *sphere3 = new Sphere(glm::vec3(0.0, -6.0, -10.0), 2.0);
	sphere3->setColor(glm::vec3(1, 0, 0));   //Set colour to red
	sphere3->setRefractivity(true, 1.0, 1.5);
	sceneObjects.push_back(sphere3);		 //Add sphere to scene objects

    // Torus *torus = new Torus(glm::vec3(10, -3, -14), 3, 1.0);
    // torus->setColor(glm::vec3(1, 0, 0));
    // // torus->setTransparency(true, 0.8);
    // sceneObjects.push_back(torus);
    Csg *csg = new Csg(glm::vec3(10, -3, -14), 3);
    csg->setColor(glm::vec3(1, 0, 0));
    csg->setSpecularity(false);
    sceneObjects.push_back(csg);


	Plane *floor = new Plane (
        glm::vec3(-50., -10, 50), //Point D
        glm::vec3(50., -10, 50), //Point C
        glm::vec3(50., -10, -50), //Point B
        glm::vec3(-50., -10, -50)); //Point A
	floor->setColor(glm::vec3(1, 0, 0));
	floor->setSpecularity(false);
	sceneObjects.push_back(floor);

    Plane *mirror = new Plane (
        glm::vec3(-5., -5, -50), //Point A
        glm::vec3(5., -5, -50), //Point B
        glm::vec3(5., 5, -50), //Point C
        glm::vec3(-5., 5, -50)); //Point D
    mirror->setColor(glm::vec3(0, 1, 0));
    mirror->setReflectivity(true, 1.0);
    sceneObjects.push_back(mirror);

    Plane *light = new Plane (
        glm::vec3(-3., 14.9f, -33), //Point A
        glm::vec3(3., 14.9f, -33), //Point B
        glm::vec3(3., 14.9f, -27), //Point C
        glm::vec3(-3., 14.9f, -27)); //Point D
	light->setColor(glm::vec3(0.95, 0.95, 0.9));
	light->setLight(true);
	sceneObjects.push_back(light);

    Plane *roof = new Plane (
        glm::vec3(-50., 15, -50), //Point A
        glm::vec3(50., 15, -50), //Point B
        glm::vec3(50., 15, 50), //Point C
        glm::vec3(-50., 15, 50)); //Point D
	roof->setColor(glm::vec3(0, 1, 1));
	roof->setSpecularity(false);
	sceneObjects.push_back(roof);

    Plane *back = new Plane (
        glm::vec3(-50., -10, -50), //Point A
        glm::vec3(50., -10, -50), //Point B
        glm::vec3(50., 15, -50), //Point C
        glm::vec3(-50., 15, -50)); //Point D
	back->setSpecularity(false);
    back->setColor(glm::vec3(0.8, 0.8, 0));
	sceneObjects.push_back(back);

    Plane *mirror2 = new Plane (
        glm::vec3(-5., 5, 50), //Point A
        glm::vec3(5., 5, 50), //Point B
        glm::vec3(5., -5, 50), //Point C
        glm::vec3(-5., -5, 50)); //Point D
    mirror2->setColor(glm::vec3(0, 0, 1));
    mirror2->setReflectivity(true, 1.0);
    sceneObjects.push_back(mirror2);

    Plane *front = new Plane (
        glm::vec3(-50., 15, 50), //Point D
        glm::vec3(50., 15, 50), //Point C
        glm::vec3(50., -10, 50), //Point B
        glm::vec3(-50., -10, 50)); //Point A
	front->setSpecularity(false);
    front->setColor(glm::vec3(1, 0, 0));
	sceneObjects.push_back(front);

    Plane *left = new Plane (
        glm::vec3(-15., -10, 50), //Point A
        glm::vec3(-15., -10, -50), //Point B
        glm::vec3(-15., 15, -50), //Point C
        glm::vec3(-15., 15, 50)); //Point D
    left->setColor(glm::vec3(0, 0, 1));
    left->setSpecularity(false);
    sceneObjects.push_back(left);

    Plane *right = new Plane (
        glm::vec3(15., -10, -50), //Point A
        glm::vec3(15., -10, 50), //Point B
        glm::vec3(15., 15, 50), //Point C
        glm::vec3(15., 15, -50)); //Point D
    right->setColor(glm::vec3(1, 1, 1));
    sceneObjects.push_back(right);

}