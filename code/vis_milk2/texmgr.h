#ifndef GEISS_TEXTURE_MANAGER
#define GEISS_TEXTURE_MANAGER 1

#define NUM_TEX 16

#include "../ns-eel2/ns-eel.h"
#include "md_defines.h"

#define TEXMGR_ERROR_MASK                 0x0F
#define TEXMGR_ERR_SUCCESS                0
#define TEXMGR_ERR_BAD_INDEX              1
#define TEXMGR_ERR_FORMAT                 8
#define TEXMGR_ERR_BADFILE                9
#define TEXMGR_ERR_OUTOFMEM               10
#define TEXMGR_WARNING_MASK               0xF0
#define TEXMGR_WARN_ERROR_IN_INIT_CODE    0x10
#define TEXMGR_WARN_ERROR_IN_REG_CODE     0x20

#ifdef _WIN32

#ifdef _DEBUG
    #define D3D_DEBUG_INFO  // declare this before including d3d9.h
#endif
#include <d3d9.h>

typedef struct
{
	LPDIRECT3DTEXTURE9     pSurface;
	int                    img_w, img_h;
	wchar_t				   szFileName[512];	
	float				   fStartTime;
	int                    nStartFrame;
	int                    nUserData;

	// stuff for expressions:
	char            m_szExpr[8192];
    NSEEL_CODEHANDLE				m_codehandle;
    double          *var_time, *var_frame, *var_fps, *var_progress;
	double          *var_bass, *var_bass_att, *var_mid, *var_mid_att, *var_treb, *var_treb_att;
	double          *var_x, *var_y;
	double          *var_sx, *var_sy, *var_rot, *var_flipx, *var_flipy;
	double          *var_r, *var_g, *var_b, *var_a;
	double          *var_blendmode;
	double          *var_repeatx, *var_repeaty;
	double          *var_done, *var_burn;
	NSEEL_VMCTX	tex_eel_ctx;
}
td_tex;

class texmgr
{
public:
	texmgr();
	~texmgr();

	void Init(LPDIRECT3DDEVICE9 lpDD);
	int  LoadTex(wchar_t *szFilename, int iSlot, char *szInitCode, char *szCode, float time, int frame, unsigned int ck);
	void KillTex(int iSlot);
	void Finish();

	td_tex          m_tex[NUM_TEX];
	
protected:
	void FreeVars(int iSlot);
	void FreeCode(int iSlot);
	void RegisterBuiltInVariables(int iSlot);
	bool RunInitCode(int iSlot, char *szInitCode);
	bool RecompileExpressions(int iSlot);
	void StripLinefeedCharsAndComments(char *src, char *dest);

	LPDIRECT3DDEVICE9 m_lpDD;					
};

#else // non-Windows

#include <wchar.h>

// Stubs for DirectX types
typedef void* LPDIRECT3DTEXTURE9;
typedef void* LPDIRECT3DDEVICE9;

typedef struct
{
	LPDIRECT3DTEXTURE9     pSurface;
	int                    img_w, img_h;
	wchar_t				   szFileName[512];	
	float				   fStartTime;
	int                    nStartFrame;
	int                    nUserData;

	// stuff for expressions:
	char            m_szExpr[8192];
    NSEEL_CODEHANDLE				m_codehandle;
    double          *var_time, *var_frame, *var_fps, *var_progress;
	double          *var_bass, *var_bass_att, *var_mid, *var_mid_att, *var_treb, *var_treb_att;
	double          *var_x, *var_y;
	double          *var_sx, *var_sy, *var_rot, *var_flipx, *var_flipy;
	double          *var_r, *var_g, *var_b, *var_a;
	double          *var_blendmode;
	double          *var_repeatx, *var_repeaty;
	double          *var_done, *var_burn;
	NSEEL_VMCTX	tex_eel_ctx;
}
td_tex;

class texmgr
{
public:
	texmgr() { }
	~texmgr() { }

	void Init(LPDIRECT3DDEVICE9 lpDD) { }
	int  LoadTex(wchar_t *szFilename, int iSlot, char *szInitCode, char *szCode, float time, int frame, unsigned int ck) { return 0; }
	void KillTex(int iSlot) { }
	void Finish() { }

	td_tex          m_tex[NUM_TEX];
	
protected:
	void FreeVars(int iSlot) { }
	void FreeCode(int iSlot) { }
	void RegisterBuiltInVariables(int iSlot) { }
	bool RunInitCode(int iSlot, char *szInitCode) { return true; }
	bool RecompileExpressions(int iSlot) { return true; }
	void StripLinefeedCharsAndComments(char *src, char *dest) { }

	LPDIRECT3DDEVICE9 m_lpDD;
};

#endif // _WIN32

#endif
