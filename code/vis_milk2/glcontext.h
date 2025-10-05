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

#ifndef __NULLSOFT_GL_PLUGIN_SHELL_GLCONTEXT_H__
#define __NULLSOFT_GL_PLUGIN_SHELL_GLCONTEXT_H__ 1

#include "shell_defines.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct
{
    int  nbackbuf;
    int  allow_page_tearing;
    int adapter_devicename;
    int display_mode;
    int multisamp;
    GLFWwindow* parent_window;
    int m_dualhead_horz;
    int m_dualhead_vert;
    int m_skin;
}
GLCONTEXT_PARAMS;

class GLContext
{
public:
    GLContext(GLFWwindow* window, wchar_t* szIniFile);
    ~GLContext();
    BOOL StartOrRestartDevice(GLCONTEXT_PARAMS *pParams);
    void OnTrulyExiting() { m_truly_exiting = 1; }
    void UpdateMonitorWorkRect();
    int  GetBitDepth() { return m_bpp; };
    char* GetDriver() { return m_szDriver; };
    char* GetDesc() { return m_szDesc; };

    void SaveWindow();
    GLFWwindow* GetWindow();
    bool OnUserResizeWindow(int width, int height);
    bool TempIgnoreDestroyMessages();

    int m_ready;
    int m_lastErr;
    int m_window_width;
    int m_window_height;
    int m_client_width;
    int m_client_height;
    int m_REAL_client_width;
    int m_REAL_client_height;
    int m_fake_fs_covers_all;
    int m_frame_delay;
    //RECT m_all_monitors_rect;
    //RECT m_monitor_rect;
    //RECT m_monitor_rect_orig;
    //RECT m_monitor_work_rect;
    //RECT m_monitor_work_rect_orig;
    GLCONTEXT_PARAMS m_current_mode;
    GLFWwindow* m_window;

protected:
    wchar_t m_szIniFile[260];
    char m_szDriver[MAX_DEVICE_IDENTIFIER_STRING];
    char m_szDesc[MAX_DEVICE_IDENTIFIER_STRING];
    int  m_minimize_winamp;
    int  m_winamp_minimized;
    int  m_truly_exiting;
    int  m_bpp;

    void WriteSafeWindowPos();
    BOOL Internal_Init(GLCONTEXT_PARAMS *pParams, BOOL bFirstInit);
    void Internal_CleanUp();
};

#endif