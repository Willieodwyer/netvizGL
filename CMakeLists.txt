#----------------------------------------------------------------------
#
#----------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8)


set(PROJ_NAME netvizGL)


project(${PROJ_NAME})


#set up linux search paths
set(LIBRARY_SEARCH_PATH
        /usr/local
        /opt/local
        /usr
        /opt
        )


set(HEADER_SEARCH_PATH
        /usr/local
        /opt/local
        /usr
        /opt
        )


# Find OpenGL
find_package(OpenGL)
find_package(X11)


# Find glfw header
find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h ${HEADER_SEARCH_PATH})


# Find glfw library
find_library(GLFW_LIBRARIES glfw3 ${LIBRARY_SEARCH_PATH})


# Set additional libs
set( ADDITIONAL_LIBS
        -lglut
        -lGLEW
        -lglfw
        -lglfw3
        -lGL
        -lX11
        -lXi
        -lXrandr
        -lXxf86vm
        -lXinerama
        -lXcursor
        -lrt
        -lm
        -pthread
        -ldl
        )


# Include directories for this project
set(INCLUDE_PATH
        ${OPENGL_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIR}
        )


# Libraries needed on all platforms for this project
set(LIBRARIES
        ${OPENGL_LIBRARIES}
        ${GLFW_LIBRARIES}
        ${X11_LIBRARIES}
        ${ADDITIONAL_LIBS}
        )


# Windows and Linux need GLEW, the OpenGL Extension Wrangler
find_path(GLEW_INCLUDE_DIR GL/glew.h
        ${HEADER_SEARCH_PATH}
        )


set(INCLUDE_PATH ${INCUDE_PATH}
        ${GLEW_INCLUDE_DIR}
        )


# Add a target executable
add_executable(${PROJ_NAME}
        main.cpp
        shader.h window.cpp window.h Point.cpp Point.h)


# Libraries to be linked
target_link_libraries(${PROJ_NAME}
        ${LIBRARIES}
        )
