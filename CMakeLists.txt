project(netvizGL)
cmake_minimum_required(VERSION 2.8)


######################################
# finds OpenGL, GLU and X11
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

# linking "glfw" and not "glfw3"
# assumes that glfw was built with BUILD_SHARED_LIBS to ON
target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
