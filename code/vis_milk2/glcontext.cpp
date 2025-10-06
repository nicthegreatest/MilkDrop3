/*
LICENSE
-------
Copyright 2005-2013 Nullsoft, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

* Neither the name of Nullsoft nor the names of its contributors may be used to
endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "glcontext.h"
#include "utility.h"
#include <string.h>
#include <stdio.h>

GLContext::GLContext(GLFWwindow* window, wchar_t* szIniFile)
{
    printf("GLContext: constructor\n");
    m_window = window;
    m_truly_exiting = 0;
    m_bpp = 0;
    m_frame_delay = 0;
    if (szIniFile) {
        //wcsncpy(m_szIniFile, szIniFile, sizeof(m_szIniFile)/sizeof(wchar_t) - 1);
    }
    m_szDriver[0] = 0;
    m_szDesc[0] = 0;
    m_lastErr = 0;
    m_ready = false;
}

GLContext::~GLContext()
{
    Internal_CleanUp();
}

void GLContext::Internal_CleanUp()
{
    m_ready = false;
}

bool GLContext::Internal_Init(GLCONTEXT_PARAMS *pParams, bool bFirstInit)
{
    printf("GLContext: Internal_Init\n");
    memcpy(&m_current_mode, pParams, sizeof(GLCONTEXT_PARAMS));

    glfwMakeContextCurrent(m_window);
    printf("GLContext: Internal_Init: glfwMakeContextCurrent successful\n");
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        printf("GLContext: Internal_Init: gladLoadGL failed\n");
        // handle error
        return false;
    }
    printf("GLContext: Internal_Init: gladLoadGL successful\n");

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    //strncpy(m_szDesc, (const char*)renderer, sizeof(m_szDesc)-1);
    //strncpy(m_szDriver, (const char*)version, sizeof(m_szDriver)-1);

    int width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
    glViewport(0, 0, width, height);
    m_window_width = width;
    m_window_height = height;
    m_client_width = width;
    m_client_height = height;

    m_bpp = 32; // Assuming 32-bit color depth

    m_ready = true;
    printf("GLContext: Internal_Init successful\n");
    return true;
}

bool GLContext::StartOrRestartDevice(GLCONTEXT_PARAMS *pParams)
{
    printf("GLContext: StartOrRestartDevice\n");
    if (!m_ready)
    {
        return Internal_Init(pParams, true);
    }
    else
    {
        m_ready = false;
        return Internal_Init(pParams, false);
    }
}

GLFWwindow* GLContext::GetWindow() { return m_window; }
bool GLContext::TempIgnoreDestroyMessages() { return false; }
void GLContext::SaveWindow() { }

void GLContext::WriteSafeWindowPos()
{
    // Stubbed out - replace with cross-platform config saving if needed
}

bool GLContext::OnUserResizeWindow(int new_width, int new_height)
{
    if (!m_ready)
        return false;

    if (m_client_width == new_width && m_client_height == new_height)
    {
        return true;
    }

    m_ready = false;

    m_window_width = new_width;
    m_window_height = new_height;
    m_client_width = new_width;
    m_client_height = new_height;

    glfwSetWindowSize(m_window, new_width, new_height);
    glViewport(0, 0, new_width, new_height);

    m_ready = true;
    return true;
}

void GLContext::UpdateMonitorWorkRect()
{
    // Stubbed out - platform-specific
}
