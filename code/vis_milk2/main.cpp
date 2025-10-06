#include "plugin.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <locale.h>

#include "wasabi.h"
#include "../audio/common.h"
#include "../audio/loopback-capture.h"

extern CPlugin g_plugin;
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
        g_plugin.PluginShellWindowProc(NULL, WM_KEYDOWN, key, 0);
    }
}

void RenderFrame() {
    GetAudioBuf(pcmLeftIn, pcmRightIn, SAMPLE_SIZE);

    g_plugin.PluginRender(
        (unsigned char*) pcmLeftOut,
        (unsigned char*) pcmRightOut);
}

int main(void)
{
    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "MilkDrop 3", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    g_plugin.PluginPreInitialize(0, 0);
    g_plugin.PluginInitialize(NULL, NULL, NULL, 800, 600);

    // Start the audio capture thread
    g_audio_thread_args.hr = 0;
    std::thread audio_thread(LoopbackCaptureThreadFunction, &g_audio_thread_args);
    audio_thread.detach();

    while (!glfwWindowShouldClose(window))
    {
        RenderFrame();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    g_plugin.PluginQuit();
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}