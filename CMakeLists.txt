cmake_minimum_required(VERSION 3.9)
project(OpenGL-GLSL)

set(TARGET OpenGL-GLSL)
set(CMAKE_CXX_STANDARD 11)

add_executable(OpenGL-GLSL main.cpp Common/Common.h Common/Context.h Source/Context.cpp Common/ShaderLoader.h Source/ShaderLoader.cpp)

#-----------------------------------------------------------------------
# Set common information for c++ compiler
#-----------------------------------------------------------------------

if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O0 -v \
     -I/usr/local/include -I/opt/X11/include \
     -L/usr/local/lib -L/opt/X11/lib \
     -w -framework OpenGL -lGLEW -lGLFW \
     -lXxf86vm -lpthread -lXrandr -lXinerama -lXi -lXcursor\
     -framework COCOA -framework COREVIDEO -framework IOKIT -framework CARBON \
     -L/usr/local/Cellar/freetype/2.9/lib -I/usr/local/Cellar/freetype/2.9/include/freetype2 -lFREETYPE \
     -L/usr/local/Cellar/freeimage/3.17.0_1/lib -I/usr/local/Cellar/freeimage/3.17.0_1/include -lFREEIMAGE \
     -L/usr/local/Cellar/ftgl/2.1.3-rc5/lib -I/usr/local/Cellar/ftgl/2.1.3-rc5/include -lFTGL\
     ")
endif (APPLE)

#-----------------------------------------------------------------------
# Find OPENGL GLEW GLFW3 GLM PKGCONFIG COCOA IOKIT COREVIDEO
#-----------------------------------------------------------------------

if (NOT WIN32)
    set(CMAKE_MODULE_PATH /usr/local/lib/cmake /usr/local/lib/x86_64-linux-gnu/cmake)
    set(CMAKE_PREFIX_PATH /usr/local/lib/cmake/glfw)
endif (NOT WIN32)

find_package (PkgConfig REQUIRED)
find_package (OpenGL REQUIRED)
if (WIN32)
    include_directories("C:/GLFW/include" "C:/glm" "C:/glew/include")
    link_directories("C:/glew/lib/Release/x64" "C:/GLFW/lib-mingw" )
else (WIN32)
    find_package (glfw3 REQUIRED)
    find_package (GLM REQUIRED)
    find_package (GLEW REQUIRED STATIC)
endif (WIN32)
if (APPLE)
    include_directories(/usr/local/include)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COREVID_LIBRARY CoreVideo REQUIRED)
endif (APPLE)

#-----------------------------------------------------------------------
# Link libs  OPENGL GLEW GLFW3 GLM PKGCONFIG COCOA IOKIT COREVIDEO
#-----------------------------------------------------------------------

target_link_libraries (${TARGET}
        ${GLFW3_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARY}
        ${COCOA_LIBRARY}
        ${COREVID_LIBRARY}
        ${IOKIT_LIBRARY})
if (WIN32)
    target_link_libraries (${TARGET}
            ${OPENGL_LIBRARIES} glfw3 glew32s glu32 opengl32)
endif (WIN32)

if (UNIX)
    target_link_libraries (${TARGET}
            ${OPENGL_LIBRARIES}
            ${GLFW3_LIBRARY}
            ${GLEW_LIBRARY}
            ${FREEGLUT_LIBRARY}
            Xxf86vm pthread Xrandr Xinerama Xi Xcursor)
endif (UNIX)