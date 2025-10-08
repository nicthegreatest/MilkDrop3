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

#ifndef __NULLSOFT_DX9_PLUGIN_SHELL_H__
#define __NULLSOFT_DX9_PLUGIN_SHELL_H__ 1

#include "shell_defines.h"
#include "glcontext.h"
#include "fft.h"
#include "defines.h"
#include "textmgr.h"
#include <vector>

// Windows-specific types are now defined in shell_defines.h


#define TIME_HIST_SLOTS 128     // # of slots used if fps > 60.  half this many if fps==30.
#define MAX_SONGS_PER_PAGE 40

typedef struct
{
    wchar_t szFace[256];
    int nSize;  // size requested @ font creation time
    int bBold;
    int bItalic;
    int bAntiAliased;
} td_fontinfo;

typedef struct
{
    float imm[2][3];
    float avg[2][3];
    float med_avg[2][3];
    float long_avg[2][3];
    float infinite_avg[2][3];
    float fWaveform[2][576];
    float fSpectrum[2][NUM_FREQUENCIES];
} td_soundinfo;

class CPluginShell
{
public:
    // GET METHODS
    int       GetFrame();
    float     GetTime();
    float     GetFps();
    char*  GetPluginsDirPath();
    char*  GetConfigIniFile();
	char*     GetConfigIniFileA();
    int          GetWidth();
    int          GetHeight();
protected:
    int          GetBitDepth();
    char*        GetDriverFilename();
    char*        GetDriverDescription();
public:
    int          GetFontHeight(eFontIndex idx);
    CTextManager m_text;
protected:
    td_soundinfo m_sound;
    void         SuggestHowToFreeSomeMem();

    int          m_start_fullscreen;
    int          m_start_desktop;
    int          m_fake_fullscreen_mode;
    int          m_max_fps_fs;
    int          m_max_fps_dm;
    int          m_max_fps_w;
    int          m_show_press_f1_msg;
    int          m_allow_page_tearing_w;
    int          m_allow_page_tearing_fs;
    int          m_allow_page_tearing_dm;
    int          m_minimize_winamp;
    int          m_desktop_show_icons;
    int          m_desktop_textlabel_boxes;
    int          m_desktop_manual_icon_scoot;
    int          m_desktop_555_fix;
    int          m_dualhead_horz;
    int          m_dualhead_vert;
    int          m_save_cpu;
    int          m_skin;
    int          m_fix_slow_text;
    td_fontinfo  m_fontinfo[NUM_BASIC_FONTS + NUM_EXTRA_FONTS];
    struct DisplayMode { int Width; int Height; int RefreshRate; D3DFORMAT Format; };
    DisplayMode m_disp_mode_fs;

    virtual void OverrideDefaults()      = 0;
    virtual void MyPreInitialize()       = 0;
    virtual void MyReadConfig()          = 0;
    virtual void MyWriteConfig()         = 0;
    virtual int  AllocateMyNonDx9Stuff() = 0;
    virtual void  CleanUpMyNonDx9Stuff() = 0;
    virtual int  AllocateMyDX9Stuff()    = 0;
    virtual void  CleanUpMyDX9Stuff(int final_cleanup) = 0;
    virtual void MyRenderFn(int redraw)  = 0;
    virtual void MyRenderUI(int *upper_left_corner_y, int *upper_right_corner_y, int *lower_left_corner_y, int *lower_right_corner_y, int xL, int xR) = 0;
    virtual void MyKeyHandler(int key) = 0;
    virtual void OnAltK() { };

    int m_show_help;
private:
    int          m_frame;
    float        m_time;
    float        m_fps;
    GLContext*   m_lpDX;
    char      m_szPluginsDirPath[1024];
    char      m_szConfigIniFile[1024];
	char         m_szConfigIniFileA[1024];
	void* m_lpDDSText; // IDirect3DTexture9
    LPD3DXFONT   m_d3dx_font[NUM_BASIC_FONTS + NUM_EXTRA_FONTS];
    LPD3DXFONT   m_d3dx_desktop_font;
    HFONT        m_font[NUM_BASIC_FONTS + NUM_EXTRA_FONTS];
    HFONT        m_font_desktop;
    enum D3DMULTISAMPLE_TYPE {};
    D3DMULTISAMPLE_TYPE m_multisample_fullscreen;
    D3DMULTISAMPLE_TYPE m_multisample_desktop;
    D3DMULTISAMPLE_TYPE m_multisample_windowed;
    GUID m_adapter_guid_fullscreen;
    GUID m_adapter_guid_desktop;
    GUID m_adapter_guid_windowed;
    char m_adapter_devicename_fullscreen[256];
    char m_adapter_devicename_desktop[256];
    char m_adapter_devicename_windowed[256];
    int m_lost_focus;
    int m_hidden;
    int m_resizing;
    int m_show_playlist;
    int  m_playlist_pos;
    int  m_playlist_pageups;
    int  m_playlist_top_idx;
    int  m_playlist_btm_idx;
    int  m_playlist_width_pixels;
    char m_playlist[MAX_SONGS_PER_PAGE][256];
    int m_exiting;
    int m_upper_left_corner_y;
    int m_lower_left_corner_y;
    int m_upper_right_corner_y;
    int m_lower_right_corner_y;
    int m_left_edge;
    int m_right_edge;
    int m_force_accept_WM_WINDOWPOSCHANGING;
    bool                m_bClearVJWindow;
   protected:
    double m_last_raw_time;
    long long m_high_perf_timer_freq;
   private:
    float  m_time_hist[TIME_HIST_SLOTS];
    int    m_time_hist_pos;
    long long m_prev_end_of_frame;
    FFT   m_fftobj;
    float m_oldwave[2][576];
    int   m_prev_align_offset[2];
    int   m_align_weights_ready;
public:
    CPluginShell();
    ~CPluginShell();
    int  PluginInitialize(void* device, void* d3dpp, void* window, int iWidth, int iHeight);
    int  PluginRender(unsigned char *pWaveL, unsigned char *pWaveR);
    void PluginQuit();
    void ToggleHelp();
	void READ_FONT(int n);
	void WRITE_FONT(int n);
private:
    void DrawAndDisplay(int redraw);
    void ReadConfig();
    void WriteConfig();
    void DoTime();
    void AnalyzeNewSound(unsigned char *pWaveL, unsigned char *pWaveR);
    void AlignWaves();
    int  InitDirectX(void* device, void* d3dpp, void* window);
    void CleanUpDirectX();
    int  InitGDIStuff();
    void CleanUpGDIStuff();
    int  AllocateDX9Stuff();
    void CleanUpDX9Stuff(int final_cleanup);
    int  InitNondx9Stuff();
    void CleanUpNondx9Stuff();
    int  InitVJStuff(RECT* pClientRect=NULL);
    void CleanUpVJStuff();
    int  AllocateFonts(void* pDevice);
    void CleanUpFonts();
    void AllocateTextSurface();
    void OnUserResizeWindow();
    void OnUserResizeTextWindow();
    void PrepareFor2DDrawing_B(void* pDevice, int w, int h);
    void RenderBuiltInTextMsgs();
    int  GetCanvasMarginX();
    int  GetCanvasMarginY();
public:
    void DrawDarkTranslucentBox(RECT* pr);
    unsigned int LoadShader(const char* vs_file, const char* fs_file);
    unsigned int LoadShaderFromStrings(const char* vs_source, const char* fs_source);
protected:
    void RenderPlaylist();
    void StuffParams(void* pParams);
    void EnforceMaxFPS();
	  int 		m_vj_mode;
      int       m_hidden_textwnd;
      int       m_resizing_textwnd;
      protected:
	   HWND		m_hTextWnd;
      private:
	  int		m_nTextWndWidth;
	  int		m_nTextWndHeight;
	  bool		m_bTextWindowClassRegistered;
      void* m_vjd3d9; // LPDIRECT3D9
      void* m_vjd3d9_device; // LPDIRECT3DDEVICE9
};

#endif