#----------------------------------------------------------------------
#
#----------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8)


set(PROJ_NAME netvizGL)

project(${PROJ_NAME})

# Find OpenGL
find_package(OpenGL)
find_package(X11)

# Find glfw header
find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h ${HEADER_SEARCH_PATH})

# Find glfw library
find_library(GLFW_LIBRARIES glfw3 ${LIBRARY_SEARCH_PATH})

# Set additional libs
set(ADDITIONAL_LIBS
        -fopenmp
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

set(CMAKE_CXX_STANDARD 11)

# Add a target executable
add_executable(${PROJ_NAME}
        main.cpp
        inc/Shader.h src/Window.cpp inc/Window.h src/Vertex.cpp inc/Vertex.h src/Shader.cpp src/Line.cpp inc/Line.h src/Graphs/Graph.cpp inc/Graphs/Graph.h src/Algorithms/SimpleForceDirected.cpp inc/Algorithms/SimpleForceDirected.h inc/Algorithms/Algorithm.h src/Graphs/AdjacencyGraph.cpp inc/Graphs/AdjacencyGraph.h src/Graphs/EdgeGraph.cpp inc/Graphs/EdgeGraph.h)


# Libraries to be linked
target_link_libraries(${PROJ_NAME}
        ${LIBRARIES}
        )
