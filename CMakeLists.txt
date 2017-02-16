#----------------------------------------------------------------------
#
#----------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8)


set(PROJ_NAME netvizGL)

project(${PROJ_NAME})

# Find OpenGL
find_package(OpenGL)
find_package(X11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtkmm-3.0)

# Find glfw header
find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h ${HEADER_SEARCH_PATH})

# Find glfw library
find_library(GLFW_LIBRARIES glfw3 ${LIBRARY_SEARCH_PATH})

# Set additional libs
set(ADDITIONAL_LIBS
        -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0
        -fopenmp
        -lGLEW
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
        -lz
        -lpngwriter
        -lfreetype
        -lpng
        -lftgl
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

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

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
        src/GLWindow.cpp inc/GLWindow.h
        src/Vertex.cpp inc/Vertex.h
        inc/Shader.h src/Shader.cpp
        src/Line.cpp inc/Line.h
        src/Graphs/Graph.cpp inc/Graphs/Graph.h
        src/Algorithms/SimpleForceDirected.cpp inc/Algorithms/SimpleForceDirected.h
        src/Algorithms/MultiLevel.cpp inc/Algorithms/MultiLevel.h
        inc/Algorithms/Algorithm.h
        src/Graphs/AdjacencyGraph.cpp inc/Graphs/AdjacencyGraph.h
        src/Graphs/EdgeGraph.cpp inc/Graphs/EdgeGraph.h
        src/Graphs/MatrixMarketGraph.cpp inc/Graphs/MatrixMarketGraph.h
        src/Widget.cpp inc/Widget.h
        inc/Command/Command.h
        src/Command/LoadGraphCommand.cpp inc/Command/LoadGraphCommand.h
        src/Command/ColourNodeCommand.cpp inc/Command/ColourNodeCommand.h
        src/Command/TextNodeCommand.cpp inc/Command/TextNodeCommand.h
        src/Graphs/mmio.c inc/Graphs/mmio.h
        inc/SvgPrinter.h 
        src/Algorithms/FruchtermanReingold.cpp inc/Algorithms/FruchtermanReingold.h 
        src/Centrality/DegreeCentrality.cpp inc/Centrality/DegreeCentrality.h 
        inc/Centrality/Centrality.h 
        src/Centrality/DistanceCentrality.cpp inc/Centrality/DistanceCentrality.h)
        src/Command/RefreshGraphCommand.cpp inc/Command/RefreshGraphCommand.h)


# Libraries to be linked
target_link_libraries(${PROJ_NAME}
        ${LIBRARIES}
        )
