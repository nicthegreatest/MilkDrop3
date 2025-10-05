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

#ifndef _MILKDROP_TEXMGR_H_
#define _MILKDROP_TEXMGR_H_ 1

#include "shell_defines.h"
#include "../ns-eel2/ns-eel.h"

#define NUM_TEX 16

class texmgr
{
public:
	texmgr();
	~texmgr();

	void Init(LPDIRECT3DDEVICE9 lpDevice);
	void Finish();

	void KillTex(int iSlot);
	bool LoadTex(const wchar_t* szFilename, int iSlot, bool* bTextureWasCleared, int* pCurTexSize);
	void SetTex(int iSlot);
    void SetUserTex(int iSlot, LPDIRECT3DTEXTURE9 pTex);
    void SetUserTex(int iSlot, const wchar_t* szFilename);

protected:
	LPDIRECT3DDEVICE9 m_lpDevice;

public:
	typedef struct
	{
		LPDIRECT3DTEXTURE9 pSurface;
		wchar_t       szFile[MAX_PATH];
		int           nLoaded;	// 0 for not loaded, 1 for loaded, 2 for failed.
		int           nTexSize;
		int           img_w, img_h;
		int           tex_w, tex_h;

		// for expression evaluation:
		NSEEL_VMCTX m_eel_ctx;
		NSEEL_CODEHANDLE m_codehandle;
		double *var_x, *var_y, *var_sx, *var_sy, *var_rot, *var_r, *var_g, *var_b, *var_a, *var_flipx, *var_flipy, *var_repeatx, *var_repeaty;
		double *var_time, *var_frame, *var_fps, *var_progress, *var_bass, *var_mid, *var_treb, *var_bass_att, *var_mid_att, *var_treb_att;
		double *var_done;
		double *var_burn;
		int    nStartFrame;
		float  fStartTime;
	}
	td_texture_info;

	td_texture_info m_tex[NUM_TEX];
};


#endif