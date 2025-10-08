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

#include "plugin.h"
#include "utility.h"
#include "support.h"
#include "resource.h"
#include "defines.h"
#include "shell_defines.h"
#include "wasabi.h"
#include <assert.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <dirent.h>


#define FRAND ((rand() % 7381)/7380.0f)

static bool m_bAlwaysOnTop = false;

void NSEEL_HOSTSTUB_EnterMutex(){}
void NSEEL_HOSTSTUB_LeaveMutex(){}

CPlugin* g_plugin = nullptr;

CPlugin::CPlugin()
{
    m_pState    = &m_state_DO_NOT_USE[0];
	m_pOldState = &m_state_DO_NOT_USE[1];
	m_pNewState = &m_state_DO_NOT_USE[2];


}

// from support.cpp:
extern bool g_bDebugOutput;
extern bool g_bDumpFileCleared;

#define IsAlphabetChar(x) ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
#define IsAlphanumericChar(x) ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') || (x >= '0' && x <= '9') || x == '.')
#define IsNumericChar(x) (x >= '0' && x <= '9')

const unsigned char LC2UC[256] = {
	0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
	17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,255,
	33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,
	49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,
	'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
	'Q','R','S','T','U','V','W','X','Y','Z',91,92,93,94,95,96,
	'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
	'Q','R','S','T','U','V','W','X','Y','Z',123,124,125,126,127,128,
	129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,
	145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,
	161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,
	177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,
	193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,
	209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,
	225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,
	241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,
};

void ConvertCRsToLFCA(const char* src, char* dst)
{
    while (*src)
    {
        if (*src=='\r' && *(src+1)=='\n')
        {
            *dst++ = LINEFEED_CONTROL_CHAR;
            src += 2;
        }
        else
        {
            *dst++ = *src++;
        }
    }
    *dst = 0;
}

void ConvertLFCToCRsA(const char* src, char* dst)
{
    while (*src)
    {
        if (*src==LINEFEED_CONTROL_CHAR)
        {
            *dst++ = '\r';
            *dst++ = '\n';
            src++;
        }
        else
        {
            *dst++ = *src++;
        }
    }
    *dst = 0;
}

int mystrcmpi(const char *s1, const char *s2)
{
	int i=0;
	while (LC2UC[(unsigned char)s1[i]] == LC2UC[(unsigned char)s2[i]] && s1[i] != 0)
		i++;
	if (s1[i]==0 && s2[i]==0)
		return 0;
	else if (s1[i]==0)
		return -1;
	else if (s2[i]==0)
		return 1;
	else
		return (LC2UC[(unsigned char)s1[i]] < LC2UC[(unsigned char)s2[i]]) ? -1 : 1;
}

void StripComments(char *str)
{
    // stub
}

#include <string>

bool ReadFileToString(const char* szBaseFilename, char* szDestText, int nMaxBytes, bool bConvertLFsToSpecialChar)
{
    std::string szFile = std::string(g_plugin->GetPluginsDirPath()) + szBaseFilename;

    FILE* f = fopen(szFile.c_str(), "rb");
    if (!f)
    {
        char buf[1024];
		snprintf(buf, sizeof(buf), "Unable to read data file: %s", szFile.c_str());
		g_plugin->dumpmsg(buf);
		return false;
    }
    int len = 0;
    int x;
    char prev_ch = 0;
    while ( (x = fgetc(f)) >= 0 && len < nMaxBytes-4 )
    {
        char orig_ch = (char)x;
        char ch = orig_ch;
        bool bSkipChar = false;
        if (bConvertLFsToSpecialChar)
        {
            if (ch=='\n')
            {
                if (prev_ch=='\r')
                    bSkipChar = true;
                else
                    ch = LINEFEED_CONTROL_CHAR;
            }
            else if (ch=='\r')
                ch = LINEFEED_CONTROL_CHAR;
        }

        if (!bSkipChar)
            szDestText[len++] = ch;
        prev_ch = orig_ch;
    }
    szDestText[len] = 0;
    szDestText[len++] = ' ';
    fclose(f);
    return true;
}

void OnUserEditedPerFrame(LPARAM param1, LPARAM param2) { g_plugin->m_pState->RecompileExpressions(RECOMPILE_PRESET_CODE, 0); }
void OnUserEditedPerPixel(LPARAM param1, LPARAM param2) { g_plugin->m_pState->RecompileExpressions(RECOMPILE_PRESET_CODE, 0); }
void OnUserEditedPresetInit(LPARAM param1, LPARAM param2) { g_plugin->m_pState->RecompileExpressions(RECOMPILE_PRESET_CODE, 1); }
void OnUserEditedWavecode(LPARAM param1, LPARAM param2) { g_plugin->m_pState->RecompileExpressions(RECOMPILE_WAVE_CODE, 0); }
void OnUserEditedWavecodeInit(LPARAM param1, LPARAM param2) { g_plugin->m_pState->RecompileExpressions(RECOMPILE_WAVE_CODE, 1); }
void OnUserEditedShapecode(LPARAM param1, LPARAM param2) { g_plugin->m_pState->RecompileExpressions(RECOMPILE_SHAPE_CODE, 0); }
void OnUserEditedShapecodeInit(LPARAM param1, LPARAM param2) { g_plugin->m_pState->RecompileExpressions(RECOMPILE_SHAPE_CODE, 1); }
void OnUserEditedWarpShaders(LPARAM param1, LPARAM param2) { /* Stub */ }
void OnUserEditedCompShaders(LPARAM param1, LPARAM param2) { /* Stub */ }

//char* g_szHelp = (char*)"F1 toggles this help screen\nL brings up the preset list\nScroll Lock toggles preset lock (hard cuts only)\n+/- changes rating for current preset\nR chooses a new random preset\nH does an instant hard cut to a new random preset\n\nSee readme.txt for more...";
//int g_szHelp_W = 0;

void CPlugin::OverrideDefaults()
{
   m_max_fps_fs            = 60;
   m_max_fps_w             = 60;
   m_show_press_f1_msg     = 0;
   m_allow_page_tearing_w  = 0;
   m_save_cpu              = 0;
}

void CPlugin::MyPreInitialize()
{
	//g_szHelp = (char*)"Help text not implemented yet.";
	m_bFirstRun		            = true;
    m_bInitialPresetSelected    = false;
	m_fBlendTimeUser			= 1.7f;
	m_fBlendTimeAuto			= 2.7f;
	m_fTimeBetweenPresets		= 16.0f;
	m_fTimeBetweenPresetsRand	= 10.0f;
	m_bSequentialPresetOrder    = false;
	m_bHardCutsDisabled			= true;
	m_fHardCutLoudnessThresh	= 2.5f;
	m_fHardCutHalflife			= 60.0f;
    m_nCanvasStretch    = 100;
	m_nTexSizeX			= -1;
	m_nTexSizeY			= -1;
	m_nTexBitsPerCh     =  8;
	m_nGridX			= 64;
	m_nGridY			= 48;
	m_bShowPressF1ForHelp = true;
	m_bShowMenuToolTips = true;
	m_n16BitGamma	= 2;
	m_bAutoGamma    = true;
	m_bEnableRating			= true;
	m_bSongTitleAnims		= true;
	m_fSongTitleAnimDuration = 1.7f;
	m_fTimeBetweenRandomSongTitles = -1.0f;
	m_fTimeBetweenRandomCustomMsgs = -1.0f;
	m_nSongTitlesSpawned = 0;
	m_nCustMsgsSpawned = 0;
    m_nFramesSinceResize = 0;
    m_bWarningsDisabled2    = false;
    m_bPresetLockOnAtStartup = false;
	m_bPreventScollLockHandling = false;
    m_nMaxPSVersion_ConfigPanel = 3;
    m_nMaxPSVersion_DX9 = 3;
    m_nMaxPSVersion = 3;
    m_nMaxImages = 3000;
    m_nMaxBytes  = 2000000000;
    m_dwShaderFlags = 0;
    m_pShaderCompileErrors = NULL;
    m_bShowMenu = true;
    m_bWarpShaderLock = false;
    m_bCompShaderLock = false;
    m_bNeedRescanTexturesDir = true;
    m_pSpriteVertDecl = NULL;
    m_pWfVertDecl = NULL;
    m_pMyVertDecl = NULL;
    m_gdi_title_font_doublesize  = NULL;
    m_d3dx_title_font_doublesize = NULL;
    m_prev_time = 0.0f;
	m_bTexSizeWasAutoPow2	= false;
	m_bTexSizeWasAutoExact	= false;
	m_bPresetLockedByCode = false;
	m_fStartTime	= 0.0f;
	m_fPresetStartTime = 0.0f;
	m_fNextPresetTime  = -1.0f;
    m_nLoadingPreset   = 0;
    m_nPresetsLoadedTotal = 0;

	m_UI_mode			= UI_REGULAR;
    m_bShowShaderHelp = false;
    m_nMashSlot = 0;
    for (int mash=0; mash<MASH_SLOTS; mash++)
        m_nLastMashChangeFrame[mash] = 0;
    m_bUserPagedUp      = false;
    m_bUserPagedDown    = false;
	m_fMotionVectorsTempDx = 0.0f;
	m_fMotionVectorsTempDy = 0.0f;
    m_waitstring.bActive		= false;
	m_waitstring.bOvertypeMode  = false;
	m_waitstring.szClipboard[0] = 0;
	m_nPresets		= 0;
	m_nDirs			= 0;
    m_nPresetListCurPos = 0;
	m_nCurrentPreset = -1;
	m_szCurrentPresetFile[0] = 0;
    m_szLoadingPreset[0] = 0;
    m_bPresetListReady = false;
    m_szUpdatePresetMask[0] = 0;
    myfft.Init(576, MY_FFT_SAMPLES, -1);
	memset(&mysound, 0, sizeof(mysound));
    m_presetHistoryPos = 0;
    m_presetHistoryBackFence = 0;
    m_presetHistoryFwdFence = 0;
	m_bShowFPS			= false;
	m_bShowRating		= false;
	m_bShowPresetInfo	= false;
	m_bShowDebugInfo	= false;
	m_bShowSongTitle	= false;
	m_bShowSongTime		= false;
	m_bShowSongLen		= false;
	m_fShowRatingUntilThisTime = -1.0f;
	ClearErrors();
	m_szDebugMessage[0]	= 0;
    m_szSongTitle[0]    = 0;
    m_szSongTitlePrev[0] = 0;
	m_bMMX		        = false;
    m_bHasFocus             = true;
    m_bHadFocus             = false;
    m_bOrigScrollLockState  = false;
	m_nNumericInputMode   = 0;
	m_nNumericInputNum    = 0;
	m_nNumericInputDigits = 0;
	m_supertext.bRedrawSuperText = false;
	m_supertext.fStartTime = -1.0f;
    strncpy(m_szMilkdrop2Path, "plugins/MilkDrop2/", sizeof(m_szMilkdrop2Path) - 1);
    m_szMilkdrop2Path[sizeof(m_szMilkdrop2Path)-1] = 0;

    std::string presetDir(m_szMilkdrop2Path);
    presetDir += "presets/";
    strncpy(m_szPresetDir, presetDir.c_str(), sizeof(m_szPresetDir) - 1);
    m_szPresetDir[sizeof(m_szPresetDir)-1] = 0;

    char szConfigDirA[1024] = {0};
    strncpy(szConfigDirA, GetConfigIniFileA(), sizeof(szConfigDirA) - 1);
    char* p = strrchr(szConfigDirA, '/');
    if (!p) p = strrchr(szConfigDirA, '\\');
    if (p) *(p+1) = 0;

    std::string msgIniFile(szConfigDirA);
    msgIniFile += "milk_msg.ini";
	strncpy(m_szMsgIniFile, msgIniFile.c_str(), sizeof(m_szMsgIniFile) - 1);
    m_szMsgIniFile[sizeof(m_szMsgIniFile)-1] = 0;

    std::string imgIniFile(szConfigDirA);
    imgIniFile += "milk_img.ini";
	strncpy(m_szImgIniFile, imgIniFile.c_str(), sizeof(m_szImgIniFile) - 1);
    m_szImgIniFile[sizeof(m_szImgIniFile)-1] = 0;
}

void CPlugin::MyReadConfig() { /* Stub */ }
void CPlugin::MyWriteConfig() { /* Stub */ }

int CPlugin::AllocateMyNonDx9Stuff()
{
    g_bDebugOutput		= false;
	g_bDumpFileCleared	= false;
    ReadFileToString("data/include.fx", m_szShaderIncludeText, sizeof(m_szShaderIncludeText)-4, false);
	StripComments(m_szShaderIncludeText);
	m_nShaderIncludeTextLen = strlen(m_szShaderIncludeText);
    ReadFileToString("data/warp_vs.fx", m_szDefaultWarpVShaderText, sizeof(m_szDefaultWarpVShaderText), true);
    ReadFileToString("data/warp_ps.fx", m_szDefaultWarpPShaderText, sizeof(m_szDefaultWarpPShaderText), true);
    ReadFileToString("data/comp_vs.fx", m_szDefaultCompVShaderText, sizeof(m_szDefaultCompVShaderText), true);
    ReadFileToString("data/comp_ps.fx", m_szDefaultCompPShaderText, sizeof(m_szDefaultCompPShaderText), true);
    ReadFileToString("data/blur_vs.fx", m_szBlurVS, sizeof(m_szBlurVS), true);
    ReadFileToString("data/blur1_ps.fx", m_szBlurPSX, sizeof(m_szBlurPSX), true);
    ReadFileToString("data/blur2_ps.fx", m_szBlurPSY, sizeof(m_szBlurPSY), true);
	BuildMenus();
	m_bMMX = CheckForMMX();
	m_pState->Default();
	m_pOldState->Default();
    m_pNewState->Default();
    return true;
}

void CPlugin::CleanUpMyNonDx9Stuff()
{
	m_menuPreset.Finish();
	m_menuWave.Finish();
	m_menuAugment.Finish();
    m_menuCustomWave.Finish();
    m_menuCustomShape.Finish();
	m_menuMotion.Finish();
	m_menuPost.Finish();
    for (int i=0; i<MAX_CUSTOM_WAVES; i++)
	    m_menuWavecode[i].Finish();
    for (int i=0; i<MAX_CUSTOM_SHAPES; i++)
	    m_menuShapecode[i].Finish();
}

int CPlugin::AllocateMyDX9Stuff()
{
    m_nFramesSinceResize = 0;
    m_fAspectX = (m_nTexSizeY > m_nTexSizeX) ? m_nTexSizeX/(float)m_nTexSizeY : 1.0f;
    m_fAspectY = (m_nTexSizeX > m_nTexSizeY) ? m_nTexSizeY/(float)m_nTexSizeX : 1.0f;
	m_fInvAspectX = 1.0f/m_fAspectX;
	m_fInvAspectY = 1.0f/m_fAspectY;
	m_verts      = new MYVERTEX[(m_nGridX+1)*(m_nGridY+1)];
	m_verts_temp = new MYVERTEX[(m_nGridX+2) * 4];
	m_vertinfo   = new td_vertinfo[(m_nGridX+1)*(m_nGridY+1)];
	m_indices_strip = new int[(m_nGridX+2)*(m_nGridY*2)];
	m_indices_list  = new int[m_nGridX*m_nGridY*6];
	if (!m_verts || !m_vertinfo) return false;

    // Load shaders and create VBO/VAO for waveform
    m_wave_shader_program = LoadShader("data/shaders/wave_vs.glsl", "data/shaders/wave_fs.glsl");
    glGenVertexArrays(1, &m_wave_vao);
    glGenBuffers(1, &m_wave_vbo);
    glBindVertexArray(m_wave_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_wave_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(WFVERTEX) * 576, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(WFVERTEX), (void*)0);
    glEnableVertexAttribArray(0);

    // Load shaders and create VBO/VAO for shapes
    m_shape_shader_program = LoadShader("data/shaders/shape_vs.glsl", "data/shaders/shape_fs.glsl");
    glGenVertexArrays(1, &m_shape_vao);
    glGenBuffers(1, &m_shape_vbo);
    glBindVertexArray(m_shape_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_shape_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(WFVERTEX) * 102, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(WFVERTEX), (void*)0);
    glEnableVertexAttribArray(0);

    // Load shaders and create VBO/VAO for sprites
    m_sprite_shader_program = LoadShader("data/shaders/sprite_vs.glsl", "data/shaders/sprite_fs.glsl");
    glGenVertexArrays(1, &m_sprite_vao);
    glGenBuffers(1, &m_sprite_vbo);
    glBindVertexArray(m_sprite_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_sprite_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SPRITEVERTEX) * 4, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SPRITEVERTEX), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(SPRITEVERTEX), (void*)offsetof(SPRITEVERTEX, Diffuse));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SPRITEVERTEX), (void*)offsetof(SPRITEVERTEX, tu));
    glEnableVertexAttribArray(2);

    // Load shaders and create VBO/VAO for menu
    m_menu_shader_program = LoadShader("data/shaders/menu_vs.glsl", "data/shaders/menu_fs.glsl");
    glGenVertexArrays(1, &m_menu_vao);
    glGenBuffers(1, &m_menu_vbo);
    glBindVertexArray(m_menu_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_menu_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(WFVERTEX) * 4, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(WFVERTEX), (void*)0);
    glEnableVertexAttribArray(0);

    // Create fullscreen quad
    glGenVertexArrays(1, &m_fs_quad_vao);
    glGenBuffers(1, &m_fs_quad_vbo);
    glBindVertexArray(m_fs_quad_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_fs_quad_vbo);
    float quadStrip[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, // bottom-left
         1.0f, -1.0f, 1.0f, 0.0f, // bottom-right
        -1.0f,  1.0f, 0.0f, 1.0f, // top-left
         1.0f,  1.0f, 1.0f, 1.0f  // top-right
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadStrip), &quadStrip, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    // Create render target FBOs and textures
    glGenFramebuffers(2, m_render_target_fbo);
    glGenTextures(2, m_render_target_tex);

    for (int i = 0; i < 2; i++) {
        glBindFramebuffer(GL_FRAMEBUFFER, m_render_target_fbo[i]);
        glBindTexture(GL_TEXTURE_2D, m_render_target_tex[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_nTexSizeX, m_nTexSizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_render_target_tex[i], 0);
    }

    // Create blur FBOs and textures
    glGenFramebuffers(NUM_BLUR_TEX, m_blur_fbo);
    glGenTextures(NUM_BLUR_TEX, m_blur_tex);
    int w = m_nTexSizeX;
    int h = m_nTexSizeY;
    for (int i = 0; i < NUM_BLUR_TEX; i++) {
        w /= 2;
        h /= 2;
        m_nBlurTexW[i] = w;
        m_nBlurTexH[i] = h;
        glBindFramebuffer(GL_FRAMEBUFFER, m_blur_fbo[i]);
        glBindTexture(GL_TEXTURE_2D, m_blur_tex[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_blur_tex[i], 0);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    m_text_renderer = new TextRenderer(GetWidth(), GetHeight());
    m_text_renderer->Load("data/fonts/DejaVuSans.ttf", 14);


    if (!m_bInitialPresetSelected)
    {
		UpdatePresetList(true);
        LoadRandomPreset(0.0f);
        m_bInitialPresetSelected = true;
    }
    return true;
}

void CPlugin::CleanUpMyDX9Stuff(int final_cleanup)
{
    m_pState->m_bBlending = false;
    if (final_cleanup)
    {
        //WritePrivateProfileInt(m_bPresetLockedByUser, "bPresetLockOnAtStartup", GetConfigIniFile(), "settings");
    }

    glDeleteVertexArrays(1, &m_wave_vao);
    glDeleteBuffers(1, &m_wave_vbo);
    glDeleteProgram(m_wave_shader_program);

    glDeleteVertexArrays(1, &m_shape_vao);
    glDeleteBuffers(1, &m_shape_vbo);
    glDeleteProgram(m_shape_shader_program);

    glDeleteVertexArrays(1, &m_sprite_vao);
    glDeleteBuffers(1, &m_sprite_vbo);
    glDeleteProgram(m_sprite_shader_program);

    glDeleteVertexArrays(1, &m_menu_vao);
    glDeleteBuffers(1, &m_menu_vbo);
    glDeleteProgram(m_menu_shader_program);

    glDeleteVertexArrays(1, &m_fs_quad_vao);
    glDeleteBuffers(1, &m_fs_quad_vbo);
    glDeleteFramebuffers(2, m_render_target_fbo);
    glDeleteTextures(2, m_render_target_tex);
    glDeleteFramebuffers(NUM_BLUR_TEX, m_blur_fbo);
    glDeleteTextures(NUM_BLUR_TEX, m_blur_tex);

    delete m_text_renderer;
}

void CPlugin::MyRenderFn(int redraw)
{
    if (!redraw)
    {
        float dt = GetTime() - m_prev_time;
        m_prev_time = GetTime();
        m_bPresetLockedByCode = (m_UI_mode != UI_REGULAR);
        if (m_bPresetLockedByUser || m_bPresetLockedByCode)
        {
            m_fPresetStartTime = GetTime();
			m_fNextPresetTime = -1.0f;
        }
    }
    m_bHadFocus = m_bHasFocus;
    m_bHasFocus = true; // Simplified
    if (!redraw)
    {
        GetSongTitle(m_szSongTitle, sizeof(m_szSongTitle)/sizeof(char) -1);
        if (strcmp(m_szSongTitle, m_szSongTitlePrev))
        {
            strncpy(m_szSongTitlePrev, m_szSongTitle, 512);
            if (m_bSongTitleAnims)
                LaunchSongTitleAnim();
        }
    }
    DoCustomSoundAnalysis();
    RenderFrame(redraw);
    if (!redraw)
    {
        m_nFramesSinceResize++;
        if (m_nLoadingPreset > 0)
        {
            LoadPresetTick();
        }
    }
}

void CPlugin::MyRenderUI(int *upper_left_corner_y, int *upper_right_corner_y, int *lower_left_corner_y, int *lower_right_corner_y, int xL, int xR)
{
    if (m_bShowMenu)
    {
        m_pCurMenu->DrawMenu();
    }
}

void CPlugin::MyKeyHandler(int key)
{
    // This is a basic implementation to handle key presses.
    // It can be expanded to handle more complex interactions.
    if (m_bShowMenu)
    {
        m_pCurMenu->HandleKeydown(key);
    }
    else
    {
        // Handle regular keys when menu is not shown
        HandleRegularKey(key);
    }
}

void CPlugin::DrawRect(RECT* pr, DWORD color)
{
    // Decode the D3DCOLOR
    float r = ((color >> 16) & 0xFF) / 255.0f;
    float g = ((color >> 8)  & 0xFF) / 255.0f;
    float b = ( color        & 0xFF) / 255.0f;
    float a = ((color >> 24) & 0xFF) / 255.0f;

    // Get screen dimensions
    float screen_w = (float)GetWidth();
    float screen_h = (float)GetHeight();

    // Convert pixel coordinates to Normalized Device Coordinates (-1 to 1)
    // Y is flipped because screen coords are top-down, NDC is bottom-up.
    float left   = (pr->left   / screen_w) * 2.0f - 1.0f;
    float right  = (pr->right  / screen_w) * 2.0f - 1.0f;
    float top    = 1.0f - (pr->top    / screen_h) * 2.0f;
    float bottom = 1.0f - (pr->bottom / screen_h) * 2.0f;

    // Define vertices for a quad
    WFVERTEX vertices[4] = {
        { right, top,    0.0f, 0 },
        { left,  top,    0.0f, 0 },
        { right, bottom, 0.0f, 0 },
        { left,  bottom, 0.0f, 0 }
    };

    glUseProgram(m_menu_shader_program);

    // Set the color as a uniform
    GLint color_loc = glGetUniformLocation(m_menu_shader_program, "u_color");
    glUniform4f(color_loc, r, g, b, a);

    glBindVertexArray(m_menu_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_menu_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    // Draw the quad as a triangle strip
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
    glUseProgram(0);
}

int CPlugin::HandleRegularKey(WPARAM wParam)
{
    // This is a simplified key handler. A more robust implementation would
    // be needed to handle all of MilkDrop's keyboard shortcuts.
    switch(wParam)
    {
        case 'L':
            m_bShowMenu = true;
            break;
        case 'R':
            LoadRandomPreset(m_fBlendTimeUser);
            break;
        case 'H':
            LoadRandomPreset(0.0f);
            break;
        default:
            return 0; // unhandled
    }
    return 1; // handled
}
void CPlugin::GetSongTitle(char *szSongTitle, int nSize)
{
    emulatedWinampSongTitle = "Playback Stopped";
    strncpy(szSongTitle, emulatedWinampSongTitle.c_str(), nSize);
}
void CPlugin::dumpmsg(const char *s)
{
    printf("%s\n", s);
}
void CPlugin::LoadRandomPreset(float fBlendTime)
{
	if (m_nPresets - m_nDirs == 0) return;
	m_nCurrentPreset = m_nDirs + (rand() % (m_nPresets - m_nDirs));
	char szFile[1024];
	snprintf(szFile, sizeof(szFile), "%s%s", m_szPresetDir, m_presets[m_nCurrentPreset].szFilename.c_str());
    LoadPreset(szFile, fBlendTime);
}
void CPlugin::LoadPreset(const char *szPresetFilename, float fBlendTime)
{
    m_pState->Import(szPresetFilename, GetTime(), m_pOldState, STATE_ALL);
    m_fPresetStartTime = GetTime();
    m_fNextPresetTime = -1.0f;
}
void CPlugin::UpdatePresetList(bool bBackground, bool bForce, bool bTryReselectCurrentPreset)
{
    m_presets.clear();
    m_nPresets = 0;
    m_nDirs = 0;

    DIR *dir;
    struct dirent *ent;
    std::string preset_dir = std::string(GetPluginsDirPath()) + m_szPresetDir;

    if ((dir = opendir(preset_dir.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, ".milk") != NULL) {
                PresetInfo p;
                p.szFilename = ent->d_name;
                p.fRatingThis = 3.0f; // Default rating
                p.fRatingCum = 3.0f;
                m_presets.push_back(p);
            }
        }
        closedir(dir);
    } else {
        // Could not open directory
        char buf[1024];
        snprintf(buf, sizeof(buf), "Could not open preset directory: %s", preset_dir.c_str());
        dumpmsg(buf);
    }

    m_nPresets = m_presets.size();
    m_bPresetListReady = true;
}
void CPlugin::BuildMenus() { }
void CPlugin::SetMenusForPresetVersion(int WarpPSVersion, int CompPSVersion) { }
void CPlugin::DoCustomSoundAnalysis()
{
    memcpy(mysound.fWave[0], m_sound.fWaveform[0], sizeof(float)*576);
    memcpy(mysound.fWave[1], m_sound.fWaveform[1], sizeof(float)*576);
	myfft.time_to_frequency_domain(mysound.fWave[0], mysound.fSpecLeft);
}
void CPlugin::GenWarpPShaderText(char *szShaderText, float decay, bool bWrap) { }
void CPlugin::GenCompPShaderText(char *szShaderText, float brightness, float ve_alpha, float ve_zoom, int ve_orient, float hue_shader, bool bBrighten, bool bDarken, bool bSolarize, bool bInvert) { }
void CPlugin::LaunchSongTitleAnim() { }
void CPlugin::AddError(const char* szMsg, float fDuration, int category, bool bBold) { printf("Error: %s\n", szMsg); }
void CPlugin::ClearErrors(int category) { }
void CPlugin::SetCurrentPresetRating(float fNewRating) { }

void CPlugin::PrevPreset(float fBlendTime) { LoadRandomPreset(fBlendTime); }
void CPlugin::NextPreset(float fBlendTime) { LoadRandomPreset(fBlendTime); }
void CPlugin::LoadPresetTick() {}
void CPlugin::OnFinishedLoadingPreset() {}
void CPlugin::RandomizeBlendPattern() {}
void CPlugin::GenPlasma(int x0, int x1, int y0, int y1, float dt) {}
void CPlugin::WaitString_NukeSelection() {}
void CPlugin::WaitString_Cut() {}
void CPlugin::WaitString_Copy() {}
void CPlugin::WaitString_Paste() {}
void CPlugin::WaitString_SeekLeftWord() {}
void CPlugin::WaitString_SeekRightWord() {}
int CPlugin::WaitString_GetCursorColumn() { return 0; }
int CPlugin::WaitString_GetLineLength() { return 0; }
void CPlugin::WaitString_SeekUpOneLine() {}
void CPlugin::WaitString_SeekDownOneLine() {}
void CPlugin::SavePresetAs(char *szNewFile) {}
void CPlugin::DeletePresetFile(char *szDelFile) {}
void CPlugin::RenamePresetFile(char *szOldFile, char *szNewFile) {}
void CPlugin::SeekToPreset(char cStartChar) {}
void CPlugin::FindValidPresetDir() {}
void CPlugin::MergeSortPresets(int left, int right) {}
void CPlugin::ReadCustomMessages() {}
void CPlugin::LaunchCustomMessage(int nMsgNum) {}
bool CPlugin::LaunchSprite(int nSpriteNum, int nSlot) { return true; }
void CPlugin::KillSprite(int iSlot) {}
bool CPlugin::LoadShaders(PShaderSet* sh, CState* pState, bool bTick)
{
    sh->warp.Clear();
    sh->comp.Clear();

    if (pState->m_nWarpPSVersion > 0)
    {
        sh->warp.program = LoadShaderFromStrings(m_szDefaultWarpVShaderText, pState->m_szWarpShadersText);
        if (sh->warp.program == 0)
        {
            AddError("Failed to compile warp shader!", 10.0f, ERR_PRESET, true);
            pState->m_nWarpPSVersion = 0;
        }
        else
        {
            sh->warp.params.CacheParams(sh->warp.program, true);
        }
    }

    if (pState->m_nCompPSVersion > 0)
    {
        sh->comp.program = LoadShaderFromStrings(m_szDefaultCompVShaderText, pState->m_szCompShadersText);
        if (sh->comp.program == 0)
        {
            AddError("Failed to compile composite shader!", 10.0f, ERR_PRESET, true);
            pState->m_nCompPSVersion = 0;
        }
        else
        {
            sh->comp.params.CacheParams(sh->comp.program, true);
        }
    }

    return true;
}
void CPlugin::UvToMathSpace(float u, float v, float* rad, float* ang) {}
void CPlugin::ApplyShaderParams(CShaderParams* p, CState* pState)
{
    if (p->rand_frame != -1)
    {
        glUniform4f(p->rand_frame, m_rand_frame.x, m_rand_frame.y, m_rand_frame.z, m_rand_frame.w);
    }

    if (p->rand_preset != -1)
    {
        glUniform4f(p->rand_preset, pState->m_rand_preset.x, pState->m_rand_preset.y, pState->m_rand_preset.z, pState->m_rand_preset.w);
    }

    for (int i = 0; i < (NUM_Q_VAR + 3) / 4; i++)
    {
        if (p->q_const_handles[i] != -1)
        {
            float q_vars[4] = {0.0f, 0.0f, 0.0f, 0.0f};
            for (int j = 0; j < 4; j++)
            {
                int q_idx = i * 4 + j;
                if (q_idx < NUM_Q_VAR)
                {
                    q_vars[j] = *pState->var_pv_q[q_idx];
                }
            }
            glUniform4fv(p->q_const_handles[i], 1, q_vars);
        }
    }
}
//void CPlugin::RestoreShaderParams() {}
bool CPlugin::AddNoiseTex(const char* szTexName, int size, int zoom_factor) { return true; }
bool CPlugin::AddNoiseVol(const char* szTexName, int size, int zoom_factor) { return true; }
bool CPlugin::RecompileVShader(const char* szShadersText, VShaderInfo *si, int shaderType, bool bHardErrors) { return true; }
bool CPlugin::RecompilePShader(const char* szShadersText, PShaderInfo *si, int shaderType, bool bHardErrors, int PSVersion) { return true; }
bool CPlugin::EvictSomeTexture() { return true; }
void CPlugin::OnAltK() {}

void CShaderParams::Clear()
{
    rand_frame = -1;
    rand_preset = -1;
    for (int i = 0; i < 24; i++) {
        const_handles[i] = -1;
        rot_mat[i] = -1;
    }
    for (int i = 0; i < (NUM_Q_VAR + 3) / 4; i++) {
        q_const_handles[i] = -1;
    }
    texsize_params.clear();
}

void CShaderParams::CacheParams(GLuint program, bool bHardErrors)
{
    rand_frame = glGetUniformLocation(program, "rand_frame");
    rand_preset = glGetUniformLocation(program, "rand_preset");

    for (int i = 0; i < 24; i++) {
        char sz[32];
        sprintf(sz, "const_reg%02d", i);
        const_handles[i] = glGetUniformLocation(program, sz);
    }

    for (int i = 0; i < (NUM_Q_VAR + 3) / 4; i++) {
        char sz[32];
        sprintf(sz, "q_const%d", i + 1);
        q_const_handles[i] = glGetUniformLocation(program, sz);
    }

    for (int i = 0; i < 24; i++) {
        char sz[32];
        sprintf(sz, "rot_mat%02d", i);
        rot_mat[i] = glGetUniformLocation(program, sz);
    }
}

void CShaderParams::OnTextureEvict(GLuint texptr)
{
    // Stub
}

CShaderParams::CShaderParams()
{
    Clear();
}

CShaderParams::~CShaderParams()
{
}

void VShaderInfo::Clear()
{
    if (program)
    {
        glDeleteProgram(program);
        program = 0;
    }
    params.Clear();
}

void PShaderInfo::Clear()
{
    if (program)
    {
        glDeleteProgram(program);
        program = 0;
    }
    params.Clear();
}