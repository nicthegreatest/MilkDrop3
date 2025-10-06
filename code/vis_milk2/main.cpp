#include "plugin.h"
#include "glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <locale.h>
#include "portaudio.h"

#include "wasabi.h"
#include "../audio/common.h"
#include "../audio/loopback-capture.h"

extern CPlugin* g_plugin;
locale_t g_use_C_locale;

#define SAMPLE_SIZE 576

static unsigned char pcmLeftIn[SAMPLE_SIZE];
static unsigned char pcmRightIn[SAMPLE_SIZE];
static unsigned char pcmLeftOut[SAMPLE_SIZE];
static unsigned char pcmRightOut[SAMPLE_SIZE];

static LoopbackCaptureThreadFunctionArguments g_audio_thread_args;

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        // This is a simplified mapping. A more robust solution would be needed for full compatibility.
        g_plugin->PluginShellWindowProc(NULL, WM_KEYDOWN, key, 0);
    }
}

void RenderFrame() {
    GetAudioBuf(pcmLeftIn, pcmRightIn, SAMPLE_SIZE);

    g_plugin->PluginRender(
        (unsigned char*) pcmLeftOut,
        (unsigned char*) pcmRightOut);
}

int main(void)
{
    printf("main: starting\n");
    GLFWwindow* window;

    g_plugin = new CPlugin();

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        printf("main: glfwInit() failed\n");
        exit(EXIT_FAILURE);
    }
    printf("main: glfwInit() successful\n");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "MilkDrop 3", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    printf("main: glfwCreateWindow() successful\n");

    glfwMakeContextCurrent(window);
    printf("main: glfwMakeContextCurrent() successful\n");
    glfwSetKeyCallback(window, key_callback);

    g_plugin->PluginInitialize(NULL, NULL, window, 800, 600);
    printf("main: g_plugin->PluginInitialize() successful\n");

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    // Start the audio capture thread
    g_audio_thread_args.hr = 0;
    std::thread audio_thread(LoopbackCaptureThreadFunction, &g_audio_thread_args);
    audio_thread.detach();

    printf("main: entering main loop\n");
    while (!glfwWindowShouldClose(window))
    {
        RenderFrame();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    printf("main: exiting main loop\n");

    g_plugin->PluginQuit();
    Pa_Terminate();
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
