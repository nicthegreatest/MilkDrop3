cmake_minimum_required(VERSION 3.10)
project(MilkDrop3)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source files
set(AUDIO_SOURCES
    audio/audiobuf.cpp
    audio/log.cpp
    audio/loopback-capture-portaudio.cpp
    audio/prefs.cpp
)

set(NSEEL_SOURCES
    ns-eel2/nseel-caltab.c
    ns-eel2/nseel-cfunc.c
    ns-eel2/nseel-compiler.c
    ns-eel2/nseel-eval.c
    ns-eel2/nseel-lextab.c
    ns-eel2/nseel-ram.c
    ns-eel2/nseel-yylex.c
)

# Find necessary libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(PORTAUDIO REQUIRED portaudio-2.0)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

set(VIS_MILK2_SOURCES
    vis_milk2/main.cpp
    vis_milk2/glcontext.cpp
    vis_milk2/fft.cpp
    vis_milk2/menu.cpp
    vis_milk2/milkdropfs.cpp
    vis_milk2/plugin.cpp
    vis_milk2/pluginshell.cpp
    vis_milk2/state.cpp
    vis_milk2/support.cpp
    vis_milk2/texmgr.cpp
    vis_milk2/textmgr.cpp
    vis_milk2/utility.cpp
    vis_milk2/wasabi.cpp
)

# Add executable
add_executable(milkdrop3
    ${AUDIO_SOURCES}
    ${NSEEL_SOURCES}
    ${VIS_MILK2_SOURCES}
)

# Include directories
target_include_directories(milkdrop3 PUBLIC
    "${PROJECT_SOURCE_DIR}/audio"
    "${PROJECT_SOURCE_DIR}/ns-eel2"
    "${PROJECT_SOURCE_DIR}/vis_milk2"
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${glfw3_INCLUDE_DIRS}
    ${PORTAUDIO_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(milkdrop3
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    glfw
    ${PORTAUDIO_LIBRARIES}
)