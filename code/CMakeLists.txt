cmake_minimum_required(VERSION 3.10)
project(MilkDrop3)

cmake_policy(SET CMP0072 NEW)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler-specific flags
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
    set(CMAKE_C_FLAGS_DEBUG "-g")
    set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
endif()

# Define source files
set(AUDIO_SOURCES
    audio/audiobuf.cpp
    audio/log.cpp
    audio/loopback-capture-portaudio.cpp
)

if(WIN32)
    list(APPEND AUDIO_SOURCES audio/prefs.cpp)
endif()

set(NSEEL_SOURCES
    ns-eel2/numericSys/FilterDesign/generalFdesign.c
    ns-eel2/numericSys/FilterDesign/eqnerror.c
    ns-eel2/numericSys/FilterDesign/firls.c
    ns-eel2/numericSys/FilterDesign/cos_fib_paraunitary.c
    ns-eel2/numericSys/FilterDesign/polyphaseASRC.c
    ns-eel2/numericSys/FilterDesign/polyphaseFilterbank.c
    ns-eel2/numericSys/SolveLinearSystem/inv.c
    ns-eel2/numericSys/SolveLinearSystem/pinv.c
    ns-eel2/numericSys/SolveLinearSystem/mldivide.c
    ns-eel2/numericSys/SolveLinearSystem/mrdivide.c
    ns-eel2/numericSys/SolveLinearSystem/qr_fact.c
    ns-eel2/numericSys/solvopt.c
    ns-eel2/numericSys/cpoly.c
    ns-eel2/numericSys/MersenneTwister.c
    ns-eel2/numericSys/quadprog.c
    ns-eel2/numericSys/codelet.c
    ns-eel2/numericSys/FFTConvolver.c
    ns-eel2/numericSys/HPFloat/atox.c
    ns-eel2/numericSys/HPFloat/constant.c
    ns-eel2/numericSys/HPFloat/cxaop.c
    ns-eel2/numericSys/HPFloat/cxbasic.c
    ns-eel2/numericSys/HPFloat/cxconstant.c
    ns-eel2/numericSys/HPFloat/cxconvf.c
    ns-eel2/numericSys/HPFloat/cxexp.c
    ns-eel2/numericSys/HPFloat/cxhypb.c
    ns-eel2/numericSys/HPFloat/cxidiv.c
    ns-eel2/numericSys/HPFloat/cxpow.c
    ns-eel2/numericSys/HPFloat/cxprcmp.c
    ns-eel2/numericSys/HPFloat/cxtrig.c
    ns-eel2/numericSys/HPFloat/hpaconf.c
    ns-eel2/numericSys/HPFloat/prcxpr.c
    ns-eel2/numericSys/HPFloat/print.c
    ns-eel2/numericSys/HPFloat/prxpr.c
    ns-eel2/numericSys/HPFloat/sfmod.c
    ns-eel2/numericSys/HPFloat/shift.c
    ns-eel2/numericSys/HPFloat/xadd.c
    ns-eel2/numericSys/HPFloat/xchcof.c
    ns-eel2/numericSys/HPFloat/xdiv.c
    ns-eel2/numericSys/HPFloat/xevtch.c
    ns-eel2/numericSys/HPFloat/xexp.c
    ns-eel2/numericSys/HPFloat/xfmod.c
    ns-eel2/numericSys/HPFloat/xfrac.c
    ns-eel2/numericSys/HPFloat/xhypb.c
    ns-eel2/numericSys/HPFloat/xivhypb.c
    ns-eel2/numericSys/HPFloat/xivtrg.c
    ns-eel2/numericSys/HPFloat/xlog.c
    ns-eel2/numericSys/HPFloat/xmul.c
    ns-eel2/numericSys/HPFloat/xneg.c
    ns-eel2/numericSys/HPFloat/xprcmp.c
    ns-eel2/numericSys/HPFloat/xpwr.c
    ns-eel2/numericSys/HPFloat/xsigerr.c
    ns-eel2/numericSys/HPFloat/xsqrt.c
    ns-eel2/numericSys/HPFloat/xtodbl.c
    ns-eel2/numericSys/HPFloat/xtoflt.c
    ns-eel2/numericSys/HPFloat/xtrig.c
    ns-eel2/numericSys/libsamplerate/samplerate.c
    ns-eel2/numericSys/libsamplerate/src_linear.c
    ns-eel2/numericSys/libsamplerate/src_sinc.c
    ns-eel2/cpthread.c
    ns-eel2/s_str.c
    ns-eel2/fft.c
    ns-eel2/nseel-compiler.c
    ns-eel2/nseel-ram.c
    ns-eel2/y.tab.c
    ns-eel2/nseel-cfunc.c
)

# Find necessary libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(PORTAUDIO REQUIRED portaudio-2.0)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)
find_package(glm REQUIRED)

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
    vis_milk2/text_renderer.cpp
    vis_milk2/utility.cpp
    vis_milk2/wasabi.cpp
    vis_milk2/glad.c
)

set(ALL_SOURCES
    ${AUDIO_SOURCES}
    ${NSEEL_SOURCES}
    ${VIS_MILK2_SOURCES}
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
    "${PROJECT_SOURCE_DIR}/ns-eel2/numericSys/HPFloat"
    "${PROJECT_SOURCE_DIR}/third_party/stb"
    ${PORTAUDIO_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(milkdrop3 PRIVATE
    OpenGL::GL
    glfw
    ${PORTAUDIO_LIBRARIES}
    Freetype::Freetype
    glm::glm
)

# Copy data files to the build directory
file(COPY resources/Milkdrop2/data/ DESTINATION ${CMAKE_BINARY_DIR}/data)
file(COPY ${CMAKE_SOURCE_DIR}/../data/ DESTINATION ${CMAKE_BINARY_DIR}/data)

install(TARGETS milkdrop3 DESTINATION bin)
install(DIRECTORY ${CMAKE_BINARY_DIR}/data/ DESTINATION share/milkdrop3)