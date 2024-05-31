cmake_minimum_required(VERSION 2.8)

project(ass2)

add_executable(RayTracer.out RayTracer.cpp mandlebrot.cpp algebra.cpp Ray.cpp world.cpp SceneObject.cpp Sphere.cpp Torus.cpp Plane.cpp TextureBMP.cpp Csg.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glm REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${GLM_INCLUDE_DIR} )

target_link_libraries( RayTracer.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLM_LIBRARY} )

