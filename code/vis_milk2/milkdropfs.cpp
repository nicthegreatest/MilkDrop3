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
#include "resource.h"
#include "support.h"
#include "../ns-eel2/ns-eel.h"
#include "utility.h"
#include <assert.h>
#include <math.h>
#include <algorithm>
#include "shell_defines.h"


#define D3DCOLOR_RGBA_01(r,g,b,a) D3DCOLOR_RGBA(((int)(r*255)),((int)(g*255)),((int)(b*255)),((int)(a*255)))
#define FRAND ((rand() % 7381)/7380.0f)

#define VERT_CLIP 0.75f		// warning: top/bottom can get clipped if you go < 0.65!

int g_title_font_sizes[] =
{
    // NOTE: DO NOT EXCEED 64 FONTS HERE.
	6,  8,  10, 12, 14, 16,
	20, 26, 32, 38, 44, 50, 56,
	64, 72, 80, 88, 96, 104, 112, 120, 128, 136, 144,
	160, 192, 224, 256, 288, 320, 352, 384, 416, 448,
	480, 512	/**/
};

static void MungeFPCW( WORD *pwOldCW )
{
    // Stub for Linux
}

void RestoreFPCW(WORD wSave)
{
    // Stub for Linux
}

int GetNumToSpawn(float fTime, float fDeltaT, float fRate, float fRegularity, int iNumSpawnedSoFar)
{
    float fNumToSpawnReg;
    float fNumToSpawnIrreg;
    float fNumToSpawn;

    fNumToSpawnReg = ((fTime + fDeltaT) * fRate) - iNumSpawnedSoFar;

    if (fDeltaT <= 1.0f / fRate)
    {
        if ((rand() % 16384)/16384.0f < fDeltaT * fRate)
            fNumToSpawnIrreg = 1.0f;
        else
            fNumToSpawnIrreg = 0.0f;
    }
    else
    {
        fNumToSpawnIrreg = fDeltaT * fRate;
        fNumToSpawnIrreg *= 2.0f*(rand() % 16384)/16384.0f;
    }

    fNumToSpawn = fNumToSpawnReg*fRegularity + fNumToSpawnIrreg*(1.0f - fRegularity);

    return (int)(fNumToSpawn + 0.49f);
}

bool CPlugin::OnResizeTextWindow()
{
	return true;
}


void CPlugin::ClearGraphicsWindow()
{
}

HFONT CreateFontW(int,int,int,int,int,int,int,int,int,int,int,int,int,const wchar_t*) { return NULL; }
void DeleteObject(HFONT) {}
void lstrcpyW(wchar_t* dest, const wchar_t* src) { wcscpy(dest, src); }
void* D3DXCreateFontW(void*, int, int, int, int, int, int, int, int, int, const wchar_t*, void**) { return NULL; }


bool CPlugin::RenderStringToTitleTexture()	// m_szSongMessage
{
    if (!m_lpDDSTitle)
        return false;

	if (m_supertext.szTextW[0]==0)
		return false;


	wchar_t szTextToDraw[512];
	swprintf(szTextToDraw, 512, L" %s ", m_supertext.szTextW);

    bool ret = true;
	return ret;
}

void CPlugin::LoadPerFrameEvallibVars(CState* pState)
{
	*pState->var_pf_zoom		= (double)pState->m_fZoom.eval(-1);
	*pState->var_pf_zoomexp		= (double)pState->m_fZoomExponent.eval(-1);
	*pState->var_pf_rot			= (double)pState->m_fRot.eval(-1);
	*pState->var_pf_warp		= (double)pState->m_fWarpAmount.eval(-1);
	*pState->var_pf_cx			= (double)pState->m_fRotCX.eval(-1);
	*pState->var_pf_cy			= (double)pState->m_fRotCY.eval(-1);
	*pState->var_pf_dx			= (double)pState->m_fXPush.eval(-1);
	*pState->var_pf_dy			= (double)pState->m_fYPush.eval(-1);
	*pState->var_pf_sx			= (double)pState->m_fStretchX.eval(-1);
	*pState->var_pf_sy			= (double)pState->m_fStretchY.eval(-1);
	*pState->var_pf_time		= (double)(GetTime() - m_fStartTime);
	*pState->var_pf_fps         = (double)GetFps();
	*pState->var_pf_bass		= (double)mysound.imm_rel[0];
	*pState->var_pf_mid			= (double)mysound.imm_rel[1];
	*pState->var_pf_treb		= (double)mysound.imm_rel[2];
	*pState->var_pf_bass_att	= (double)mysound.avg_rel[0];
	*pState->var_pf_mid_att		= (double)mysound.avg_rel[1];
	*pState->var_pf_treb_att	= (double)mysound.avg_rel[2];
	*pState->var_pf_frame		= (double)GetFrame();
    for (int vi=0; vi<NUM_Q_VAR; vi++)
	    *pState->var_pf_q[vi]	= pState->q_values_after_init_code[vi];
    *pState->var_pf_monitor     = pState->monitor_after_init_code;
	*pState->var_pf_progress    = (GetTime() - m_fPresetStartTime) / (m_fNextPresetTime - m_fPresetStartTime);
	*pState->var_pf_decay		= (double)pState->m_fDecay.eval(GetTime());
	*pState->var_pf_wave_a		= (double)pState->m_fWaveAlpha.eval(GetTime());
	*pState->var_pf_wave_r		= (double)pState->m_fWaveR.eval(GetTime());
	*pState->var_pf_wave_g		= (double)pState->m_fWaveG.eval(GetTime());
	*pState->var_pf_wave_b		= (double)pState->m_fWaveB.eval(GetTime());
	*pState->var_pf_wave_x		= (double)pState->m_fWaveX.eval(GetTime());
	*pState->var_pf_wave_y		= (double)pState->m_fWaveY.eval(GetTime());
	*pState->var_pf_wave_mystery= (double)pState->m_fWaveParam.eval(GetTime());
	*pState->var_pf_wave_mode   = (double)pState->m_nWaveMode;
	*pState->var_pf_ob_size		= (double)pState->m_fOuterBorderSize.eval(GetTime());
	*pState->var_pf_ob_r		= (double)pState->m_fOuterBorderR.eval(GetTime());
	*pState->var_pf_ob_g		= (double)pState->m_fOuterBorderG.eval(GetTime());
	*pState->var_pf_ob_b		= (double)pState->m_fOuterBorderB.eval(GetTime());
	*pState->var_pf_ob_a		= (double)pState->m_fOuterBorderA.eval(GetTime());
	*pState->var_pf_ib_size		= (double)pState->m_fInnerBorderSize.eval(GetTime());
	*pState->var_pf_ib_r		= (double)pState->m_fInnerBorderR.eval(GetTime());
	*pState->var_pf_ib_g		= (double)pState->m_fInnerBorderG.eval(GetTime());
	*pState->var_pf_ib_b		= (double)pState->m_fInnerBorderB.eval(GetTime());
	*pState->var_pf_ib_a		= (double)pState->m_fInnerBorderA.eval(GetTime());
	*pState->var_pf_mv_x        = (double)pState->m_fMvX.eval(GetTime());
	*pState->var_pf_mv_y        = (double)pState->m_fMvY.eval(GetTime());
	*pState->var_pf_mv_dx       = (double)pState->m_fMvDX.eval(GetTime());
	*pState->var_pf_mv_dy       = (double)pState->m_fMvDY.eval(GetTime());
	*pState->var_pf_mv_l        = (double)pState->m_fMvL.eval(GetTime());
	*pState->var_pf_mv_r        = (double)pState->m_fMvR.eval(GetTime());
	*pState->var_pf_mv_g        = (double)pState->m_fMvG.eval(GetTime());
	*pState->var_pf_mv_b        = (double)pState->m_fMvB.eval(GetTime());
	*pState->var_pf_mv_a        = (double)pState->m_fMvA.eval(GetTime());
	*pState->var_pf_echo_zoom   = (double)pState->m_fVideoEchoZoom.eval(GetTime());
	*pState->var_pf_echo_alpha  = (double)pState->m_fVideoEchoAlpha.eval(GetTime());
	*pState->var_pf_echo_orient = (double)pState->m_nVideoEchoOrientation;
    *pState->var_pf_wave_usedots  = (double)pState->m_bWaveDots;
    *pState->var_pf_wave_thick    = (double)pState->m_bWaveThick;
    *pState->var_pf_wave_additive = (double)pState->m_bAdditiveWaves;
    *pState->var_pf_wave_brighten = (double)pState->m_bMaximizeWaveColor;
    *pState->var_pf_darken_center = (double)pState->m_bDarkenCenter;
    *pState->var_pf_gamma         = (double)pState->m_fGammaAdj.eval(GetTime());
    *pState->var_pf_wrap          = (double)pState->m_bTexWrap;
    *pState->var_pf_invert        = (double)pState->m_bInvert;
    *pState->var_pf_brighten      = (double)pState->m_bBrighten;
    *pState->var_pf_darken        = (double)pState->m_bDarken;
    *pState->var_pf_solarize      = (double)pState->m_bSolarize;
    *pState->var_pf_meshx         = (double)m_nGridX;
    *pState->var_pf_meshy         = (double)m_nGridY;
    *pState->var_pf_pixelsx       = (double)GetWidth();
    *pState->var_pf_pixelsy       = (double)GetHeight();
    *pState->var_pf_aspectx       = (double)m_fInvAspectX;
    *pState->var_pf_aspecty       = (double)m_fInvAspectY;
    *pState->var_pf_blur1min      = (double)pState->m_fBlur1Min.eval(GetTime());
    *pState->var_pf_blur2min      = (double)pState->m_fBlur2Min.eval(GetTime());
    *pState->var_pf_blur3min      = (double)pState->m_fBlur3Min.eval(GetTime());
    *pState->var_pf_blur1max      = (double)pState->m_fBlur1Max.eval(GetTime());
    *pState->var_pf_blur2max      = (double)pState->m_fBlur2Max.eval(GetTime());
    *pState->var_pf_blur3max      = (double)pState->m_fBlur3Max.eval(GetTime());
    *pState->var_pf_blur1_edge_darken = (double)pState->m_fBlur1EdgeDarken.eval(GetTime());
}

void CPlugin::RunPerFrameEquations(int code)
{
    m_fSnapPoint = 0.5f;
    if (m_pState->m_bBlending)
    {
        switch(code)
        {
        case 4:
        case 6:
        case 12:
        case 14:
            m_fSnapPoint = -0.01f;
            break;
        case 1:
        case 3:
        case 9:
        case 11:
            m_fSnapPoint = 1.01f;
            break;
        case 0:
        case 2:
        case 8:
        case 10:
            m_fSnapPoint = 0.5f;
            break;
        case 5:
        case 7:
        case 13:
        case 15:
            m_fSnapPoint = 0.5f;
            break;
        }
    }

	int num_reps = (m_pState->m_bBlending) ? 2 : 1;
	for (int rep=0; rep<num_reps; rep++)
	{
		CState *pState = (rep==0) ? m_pState : m_pOldState;
        LoadPerFrameEvallibVars(pState);

		*pState->var_pv_time		= *pState->var_pf_time;
		*pState->var_pv_fps         = *pState->var_pf_fps;
		*pState->var_pv_frame		= *pState->var_pf_frame;
		*pState->var_pv_progress    = *pState->var_pf_progress;
		*pState->var_pv_bass		= *pState->var_pf_bass;
		*pState->var_pv_mid			= *pState->var_pf_mid;
		*pState->var_pv_treb		= *pState->var_pf_treb;
		*pState->var_pv_bass_att	= *pState->var_pf_bass_att;
		*pState->var_pv_mid_att		= *pState->var_pf_mid_att;
		*pState->var_pv_treb_att	= *pState->var_pf_treb_att;
        *pState->var_pv_meshx       = (double)m_nGridX;
        *pState->var_pv_meshy       = (double)m_nGridY;
        *pState->var_pv_pixelsx     = (double)GetWidth();
        *pState->var_pv_pixelsy     = (double)GetHeight();
        *pState->var_pv_aspectx     = (double)m_fInvAspectX;
        *pState->var_pv_aspecty     = (double)m_fInvAspectY;

		if (pState->m_pf_codehandle)
		{
			if (pState->m_pf_codehandle)
			{
				NSEEL_code_execute(pState->m_pf_codehandle);
			}
		}

        pState->monitor_after_init_code = *pState->var_pf_monitor;
        for (int vi=0; vi<NUM_Q_VAR; vi++)
            *pState->var_pv_q[vi] = *pState->var_pf_q[vi];

        *pState->var_pf_gamma     = std::max(0.0f, std::min(8.0f, *pState->var_pf_gamma));
        *pState->var_pf_echo_zoom = std::max(0.001f, std::min(1000.0f, *pState->var_pf_echo_zoom));
	}

	if (m_pState->m_bBlending)
	{
		double mix  = (double)CosineInterp(m_pState->m_fBlendProgress);
		double mix2 = 1.0 - mix;
        *m_pState->var_pf_decay        = mix*(*m_pState->var_pf_decay       ) + mix2*(*m_pOldState->var_pf_decay       );
        *m_pState->var_pf_wave_a       = mix*(*m_pState->var_pf_wave_a      ) + mix2*(*m_pOldState->var_pf_wave_a      );
        *m_pState->var_pf_wave_r       = mix*(*m_pState->var_pf_wave_r      ) + mix2*(*m_pOldState->var_pf_wave_r      );
        *m_pState->var_pf_wave_g       = mix*(*m_pState->var_pf_wave_g      ) + mix2*(*m_pOldState->var_pf_wave_g      );
        *m_pState->var_pf_wave_b       = mix*(*m_pState->var_pf_wave_b      ) + mix2*(*m_pOldState->var_pf_wave_b      );
        *m_pState->var_pf_wave_x       = mix*(*m_pState->var_pf_wave_x      ) + mix2*(*m_pOldState->var_pf_wave_x      );
        *m_pState->var_pf_wave_y       = mix*(*m_pState->var_pf_wave_y      ) + mix2*(*m_pOldState->var_pf_wave_y      );
        *m_pState->var_pf_wave_mystery = mix*(*m_pState->var_pf_wave_mystery) + mix2*(*m_pOldState->var_pf_wave_mystery);
        *m_pState->var_pf_ob_size      = mix*(*m_pState->var_pf_ob_size     ) + mix2*(*m_pOldState->var_pf_ob_size     );
        *m_pState->var_pf_ob_r         = mix*(*m_pState->var_pf_ob_r        ) + mix2*(*m_pOldState->var_pf_ob_r        );
        *m_pState->var_pf_ob_g         = mix*(*m_pState->var_pf_ob_g        ) + mix2*(*m_pOldState->var_pf_ob_g        );
        *m_pState->var_pf_ob_b         = mix*(*m_pState->var_pf_ob_b        ) + mix2*(*m_pOldState->var_pf_ob_b        );
        *m_pState->var_pf_ob_a         = mix*(*m_pState->var_pf_ob_a        ) + mix2*(*m_pOldState->var_pf_ob_a        );
        *m_pState->var_pf_ib_size      = mix*(*m_pState->var_pf_ib_size     ) + mix2*(*m_pOldState->var_pf_ib_size     );
        *m_pState->var_pf_ib_r         = mix*(*m_pState->var_pf_ib_r        ) + mix2*(*m_pOldState->var_pf_ib_r        );
        *m_pState->var_pf_ib_g         = mix*(*m_pState->var_pf_ib_g        ) + mix2*(*m_pOldState->var_pf_ib_g        );
        *m_pState->var_pf_ib_b         = mix*(*m_pState->var_pf_ib_b        ) + mix2*(*m_pOldState->var_pf_ib_b        );
        *m_pState->var_pf_ib_a         = mix*(*m_pState->var_pf_ib_a        ) + mix2*(*m_pOldState->var_pf_ib_a        );
        *m_pState->var_pf_mv_x         = mix*(*m_pState->var_pf_mv_x        ) + mix2*(*m_pOldState->var_pf_mv_x        );
        *m_pState->var_pf_mv_y         = mix*(*m_pState->var_pf_mv_y        ) + mix2*(*m_pOldState->var_pf_mv_y        );
        *m_pState->var_pf_mv_dx        = mix*(*m_pState->var_pf_mv_dx       ) + mix2*(*m_pOldState->var_pf_mv_dx       );
        *m_pState->var_pf_mv_dy        = mix*(*m_pState->var_pf_mv_dy       ) + mix2*(*m_pOldState->var_pf_mv_dy       );
        *m_pState->var_pf_mv_l         = mix*(*m_pState->var_pf_mv_l        ) + mix2*(*m_pOldState->var_pf_mv_l        );
        *m_pState->var_pf_mv_r         = mix*(*m_pState->var_pf_mv_r        ) + mix2*(*m_pOldState->var_pf_mv_r        );
        *m_pState->var_pf_mv_g         = mix*(*m_pState->var_pf_mv_g        ) + mix2*(*m_pOldState->var_pf_mv_g        );
        *m_pState->var_pf_mv_b         = mix*(*m_pState->var_pf_mv_b        ) + mix2*(*m_pOldState->var_pf_mv_b        );
        *m_pState->var_pf_mv_a         = mix*(*m_pState->var_pf_mv_a        ) + mix2*(*m_pOldState->var_pf_mv_a        );
		*m_pState->var_pf_echo_zoom    = mix*(*m_pState->var_pf_echo_zoom   ) + mix2*(*m_pOldState->var_pf_echo_zoom   );
		*m_pState->var_pf_echo_alpha   = mix*(*m_pState->var_pf_echo_alpha  ) + mix2*(*m_pOldState->var_pf_echo_alpha  );
        *m_pState->var_pf_echo_orient  = (mix < m_fSnapPoint) ? *m_pOldState->var_pf_echo_orient : *m_pState->var_pf_echo_orient;
        *m_pState->var_pf_wave_usedots = (mix < m_fSnapPoint) ? *m_pOldState->var_pf_wave_usedots  : *m_pState->var_pf_wave_usedots ;
        *m_pState->var_pf_wave_thick   = (mix < m_fSnapPoint) ? *m_pOldState->var_pf_wave_thick    : *m_pState->var_pf_wave_thick   ;
        *m_pState->var_pf_wave_additive= (mix < m_fSnapPoint) ? *m_pOldState->var_pf_wave_additive : *m_pState->var_pf_wave_additive;
        *m_pState->var_pf_wave_brighten= (mix < m_fSnapPoint) ? *m_pOldState->var_pf_wave_brighten : *m_pState->var_pf_wave_brighten;
        *m_pState->var_pf_darken_center= (mix < m_fSnapPoint) ? *m_pOldState->var_pf_darken_center : *m_pState->var_pf_darken_center;
        *m_pState->var_pf_gamma        = mix*(*m_pState->var_pf_gamma       ) + mix2*(*m_pOldState->var_pf_gamma       );
        *m_pState->var_pf_wrap         = (mix < m_fSnapPoint) ? *m_pOldState->var_pf_wrap          : *m_pState->var_pf_wrap         ;
        *m_pState->var_pf_invert       = (mix < m_fSnapPoint) ? *m_pOldState->var_pf_invert        : *m_pState->var_pf_invert       ;
        *m_pState->var_pf_brighten     = (mix < m_fSnapPoint) ? *m_pOldState->var_pf_brighten      : *m_pState->var_pf_brighten     ;
        *m_pState->var_pf_darken       = (mix < m_fSnapPoint) ? *m_pOldState->var_pf_darken        : *m_pState->var_pf_darken       ;
        *m_pState->var_pf_solarize     = (mix < m_fSnapPoint) ? *m_pOldState->var_pf_solarize      : *m_pState->var_pf_solarize     ;
        *m_pState->var_pf_blur1min  = mix*(*m_pState->var_pf_blur1min ) + mix2*(*m_pOldState->var_pf_blur1min );
        *m_pState->var_pf_blur2min  = mix*(*m_pState->var_pf_blur2min ) + mix2*(*m_pOldState->var_pf_blur2min );
        *m_pState->var_pf_blur3min  = mix*(*m_pState->var_pf_blur3min ) + mix2*(*m_pOldState->var_pf_blur3min );
        *m_pState->var_pf_blur1max  = mix*(*m_pState->var_pf_blur1max ) + mix2*(*m_pOldState->var_pf_blur1max );
        *m_pState->var_pf_blur2max  = mix*(*m_pState->var_pf_blur2max ) + mix2*(*m_pOldState->var_pf_blur2max );
        *m_pState->var_pf_blur3max  = mix*(*m_pState->var_pf_blur3max ) + mix2*(*m_pOldState->var_pf_blur3max );
        *m_pState->var_pf_blur1_edge_darken = mix*(*m_pState->var_pf_blur1_edge_darken) + mix2*(*m_pOldState->var_pf_blur1_edge_darken);
    }
}

void CPlugin::RenderFrame(int bRedraw)
{
	int i;
    float fDeltaT = 1.0f/GetFps();

    m_rand_frame.x = FRAND;
    m_rand_frame.y = FRAND;
    m_rand_frame.z = FRAND;
    m_rand_frame.w = FRAND;

    if (bRedraw)
    {
	    IDirect3DTexture9* pTemp = m_lpVS[0];
	    m_lpVS[0] = m_lpVS[1];
	    m_lpVS[1] = pTemp;
    }

	if (GetFrame()==0)
	{
		m_fStartTime = GetTime();
		m_fPresetStartTime = GetTime();
	}

	if (m_fNextPresetTime < 0)
	{
		float dt = m_fTimeBetweenPresetsRand * (rand()%1000)*0.001f;
		m_fNextPresetTime = GetTime() + m_fBlendTimeAuto + m_fTimeBetweenPresets + dt;
	}

    if (!bRedraw)
    {
	    if (m_fNextPresetTime < GetTime())
	    {
            if (m_nLoadingPreset==0)
		        LoadRandomPreset(m_fBlendTimeAuto);
	    }

	    if (m_fTimeBetweenRandomSongTitles > 0 &&
		    !m_supertext.bRedrawSuperText &&
		    GetTime() >= m_supertext.fStartTime + m_supertext.fDuration + 1.0f/GetFps())
	    {
		    int n = GetNumToSpawn(GetTime(), fDeltaT, 1.0f/m_fTimeBetweenRandomSongTitles, 0.5f, m_nSongTitlesSpawned);
		    if (n > 0)
		    {
			    LaunchSongTitleAnim();
			    m_nSongTitlesSpawned += n;
		    }
	    }

	    if (m_fTimeBetweenRandomCustomMsgs > 0 &&
		    !m_supertext.bRedrawSuperText &&
		    GetTime() >= m_supertext.fStartTime + m_supertext.fDuration + 1.0f/GetFps())
	    {
		    int n = GetNumToSpawn(GetTime(), fDeltaT, 1.0f/m_fTimeBetweenRandomCustomMsgs, 0.5f, m_nCustMsgsSpawned);
		    if (n > 0)
		    {
			    LaunchCustomMessage(-1);
			    m_nCustMsgsSpawned += n;
		    }
	    }

	    if (m_pState->m_bBlending)
	    {
		    m_pState->m_fBlendProgress = (GetTime() - m_pState->m_fBlendStartTime) / m_pState->m_fBlendDuration;
		    if (m_pState->m_fBlendProgress > 1.0f)
		    {
			    m_pState->m_bBlending = false;
		    }
	    }

	    static float m_fHardCutThresh;
	    if (GetFrame() == 0)
		    m_fHardCutThresh = m_fHardCutLoudnessThresh*2.0f;
	    if (GetFps() > 1.0f && !m_bHardCutsDisabled && !m_bPresetLockedByUser && !m_bPresetLockedByCode)
	    {
		    if (mysound.imm_rel[0] + mysound.imm_rel[1] + mysound.imm_rel[2] > m_fHardCutThresh*3.0f)
		    {
                if (m_nLoadingPreset==0)
		            LoadRandomPreset(0.0f);
			    m_fHardCutThresh *= 2.0f;
		    }
		    else
		    {
			    float k = -1.3863f / (m_fHardCutHalflife*GetFps());
			    float single_frame_multiplier = expf(k);
			    m_fHardCutThresh = (m_fHardCutThresh - m_fHardCutLoudnessThresh)*single_frame_multiplier + m_fHardCutLoudnessThresh;
		    }
	    }

	    float scale = m_pState->m_fWaveScale.eval(GetTime()) / 128.0f;
	    mysound.fWave[0][0] *= scale;
	    mysound.fWave[1][0] *= scale;
	    float mix2 = m_pState->m_fWaveSmoothing.eval(GetTime());
	    float mix1 = scale*(1.0f - mix2);
	    for (i=1; i<576; i++)
	    {
		    mysound.fWave[0][i] = mysound.fWave[0][i]*mix1 + mysound.fWave[0][i-1]*mix2;
		    mysound.fWave[1][i] = mysound.fWave[1][i]*mix1 + mysound.fWave[1][i-1]*mix2;
	    }
    }

    bool bOldPresetUsesWarpShader = (m_pOldState->m_nWarpPSVersion > 0);
    bool bNewPresetUsesWarpShader = (m_pState->m_nWarpPSVersion > 0);
    bool bOldPresetUsesCompShader = (m_pOldState->m_nCompPSVersion > 0);
    bool bNewPresetUsesCompShader = (m_pState->m_nCompPSVersion > 0);

    int code = (bOldPresetUsesWarpShader ? 8 : 0) |
               (bOldPresetUsesCompShader ? 4 : 0) |
               (bNewPresetUsesWarpShader ? 2 : 0) |
               (bNewPresetUsesCompShader ? 1 : 0);

	RunPerFrameEquations(code);

    glBindFramebuffer(GL_FRAMEBUFFER, m_render_target_fbo[0]);
    glViewport(0, 0, m_nTexSizeX, m_nTexSizeY);
    glClear(GL_COLOR_BUFFER_BIT);

    DrawMotionVectors();
	DrawCustomShapes();
	DrawCustomWaves();
	DrawWave(mysound.fWave[0], mysound.fWave[1]);
	DrawSprites();

    if (bNewPresetUsesWarpShader)
    {
        WarpedBlit_Shaders(0, false, false, false, false);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, GetWidth(), GetHeight());
    glClear(GL_COLOR_BUFFER_BIT);

    if (bNewPresetUsesCompShader)
    {
        ShowToUser_Shaders(0, false, false, false, false);
    }
    else
    {
        // Fallback for non-shader presets
        glBindFramebuffer(GL_READ_FRAMEBUFFER, m_render_target_fbo[0]);
        glBlitFramebuffer(0, 0, m_nTexSizeX, m_nTexSizeY, 0, 0, GetWidth(), GetHeight(), GL_COLOR_BUFFER_BIT, GL_LINEAR);
    }


	float fProgress = (GetTime() - m_supertext.fStartTime) / m_supertext.fDuration;

	if (m_supertext.fStartTime >= 0 &&
		fProgress >= 1.0f &&
		!m_supertext.bRedrawSuperText)
	{
		ShowSongTitleAnim(m_nTexSizeX, m_nTexSizeY, 1.0f);
	}

	if (m_supertext.fStartTime >= 0 &&
		!m_supertext.bRedrawSuperText)
	{
		ShowSongTitleAnim(GetWidth(), GetHeight(), std::min(fProgress, 0.9999f));
        if (fProgress >= 1.0f)
            m_supertext.fStartTime = -1.0f;
	}

	DrawUserSprites();

	IDirect3DTexture9* pTemp = m_lpVS[0];
	m_lpVS[0] = m_lpVS[1];
	m_lpVS[1] = pTemp;
}

void CPlugin::DrawMotionVectors()
{
	if ((float)*m_pState->var_pf_mv_a < 0.001f)
        return;
}

void CPlugin::GetSafeBlurMinMax(CState* pState, float* blur_min, float* blur_max)
{
    blur_min[0] = (float)*pState->var_pf_blur1min;
    blur_min[1] = (float)*pState->var_pf_blur2min;
    blur_min[2] = (float)*pState->var_pf_blur3min;
    blur_max[0] = (float)*pState->var_pf_blur1max;
    blur_max[1] = (float)*pState->var_pf_blur2max;
    blur_max[2] = (float)*pState->var_pf_blur3max;

    const float fMinDist = 0.1f;
    if (blur_max[0] - blur_min[0] < fMinDist) {
        float avg = (blur_min[0] + blur_max[0])*0.5f;
        blur_min[0] = avg - fMinDist*0.5f;
        blur_max[0] = avg - fMinDist*0.5f;
    }
    blur_max[1] = std::min(blur_max[0], blur_max[1]);
    blur_min[1] = std::max(blur_min[0], blur_min[1]);
    if (blur_max[1] - blur_min[1] < fMinDist) {
        float avg = (blur_min[1] + blur_max[1])*0.5f;
        blur_min[1] = avg - fMinDist*0.5f;
        blur_max[1] = avg - fMinDist*0.5f;
    }
    blur_max[2] = std::min(blur_max[1], blur_max[2]);
    blur_min[2] = std::max(blur_min[1], blur_min[2]);
    if (blur_max[2] - blur_min[2] < fMinDist) {
        float avg = (blur_min[2] + blur_max[2])*0.5f;
        blur_min[2] = avg - fMinDist*0.5f;
        blur_max[2] = avg - fMinDist*0.5f;
    }
}

void CPlugin::BlurPasses()
{
    m_nHighestBlurTexUsedThisFrame = 0;
}

void CPlugin::ComputeGridAlphaValues()
{
}

void CPlugin::WarpedBlit_NoShaders(int nPass, bool bAlphaBlend, bool bFlipAlpha, bool bCullTiles, bool bFlipCulling)
{
    // Simple blit for non-shader presets
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_render_target_fbo[0]);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_render_target_fbo[1]);
    glBlitFramebuffer(0, 0, m_nTexSizeX, m_nTexSizeY, 0, 0, m_nTexSizeX, m_nTexSizeY, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    std::swap(m_render_target_fbo[0], m_render_target_fbo[1]);
    std::swap(m_render_target_tex[0], m_render_target_tex[1]);
}

void CPlugin::WarpedBlit_Shaders(int nPass, bool bAlphaBlend, bool bFlipAlpha, bool bCullTiles, bool bFlipCulling)
{
    // Bind the destination FBO
    glBindFramebuffer(GL_FRAMEBUFFER, m_render_target_fbo[1]);
    glViewport(0, 0, m_nTexSizeX, m_nTexSizeY);

    // Use the warp shader
    PShaderSet* sh = &m_shaders;
    glUseProgram(sh->warp.program);

    // Set uniforms
    ApplyShaderParams(&sh->warp.params, m_pState);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_render_target_tex[0]);
    glUniform1i(glGetUniformLocation(sh->warp.program, "sampler_main"), 0);
    // TODO: Apply other shader params

    // Draw the fullscreen quad
    glBindVertexArray(m_fs_quad_vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // Swap render targets for the next pass
    std::swap(m_render_target_fbo[0], m_render_target_fbo[1]);
    std::swap(m_render_target_tex[0], m_render_target_tex[1]);
}

void CPlugin::DrawCustomShapes()
{
    int num_reps = (m_pState->m_bBlending) ? 2 : 1;
    for (int rep = 0; rep < num_reps; rep++)
    {
        CState* pState = (rep == 0) ? m_pState : m_pOldState;
        float alpha_mult = 1.0f;
        if (num_reps == 2)
        {
            alpha_mult = (rep == 0) ? CosineInterp(m_pState->m_fBlendProgress) : (1.0f - CosineInterp(m_pState->m_fBlendProgress));
        }

        for (int i = 0; i < MAX_CUSTOM_SHAPES; i++)
        {
            if (pState->m_shape[i].enabled)
            {
                for (int instance = 0; instance < pState->m_shape[i].instances; instance++)
                {
                    LoadCustomShapePerFrameEvallibVars(pState, i, instance);

                    if (pState->m_shape[i].m_pf_codehandle)
                    {
                        NSEEL_code_execute(pState->m_shape[i].m_pf_codehandle);
                    }

                    float a = *pState->m_shape[i].var_pf_a * alpha_mult;
                    if (a < 0.001f)
                        continue;

                    int sides = (int)(*pState->m_shape[i].var_pf_sides);
                    if (sides < 3) sides = 3;
                    if (sides > 100) sides = 100;

                    WFVERTEX v[102]; // 100 sides + center + first vertex
                    float x = (float)(*pState->m_shape[i].var_pf_x * 2.0 - 1.0);
                    float y = (float)(*pState->m_shape[i].var_pf_y * -2.0 + 1.0);
                    float rad = (float)*pState->m_shape[i].var_pf_rad;
                    float ang = (float)*pState->m_shape[i].var_pf_ang;

                    v[0].x = x;
                    v[0].y = y;
                    v[0].z = 0.0f;
                    v[0].Diffuse = 0;

                    for (int j = 0; j <= sides; j++)
                    {
                        float t = j / (float)sides;
                        v[j+1].x = x + rad * cosf(t * 6.283185f + ang) * m_fAspectY;
                        v[j+1].y = y + rad * sinf(t * 6.283185f + ang);
                        v[j+1].z = 0.0f;
                        v[j+1].Diffuse = 0;
                    }

                    glUseProgram(m_shape_shader_program);
                    int color_loc = glGetUniformLocation(m_shape_shader_program, "u_color");
                    glUniform4f(color_loc,
                                (float)*pState->m_shape[i].var_pf_r,
                                (float)*pState->m_shape[i].var_pf_g,
                                (float)*pState->m_shape[i].var_pf_b,
                                a);

                    if (*pState->m_shape[i].var_pf_additive > 0.5)
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                    else
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                    glBindVertexArray(m_shape_vao);
                    glBindBuffer(GL_ARRAY_BUFFER, m_shape_vbo);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(WFVERTEX) * (sides + 2), v, GL_DYNAMIC_DRAW);
                    glDrawArrays(GL_TRIANGLE_FAN, 0, sides + 2);
                }
            }
        }
    }
    // Restore default blend func
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(0);
    glBindVertexArray(0);
}

void CPlugin::LoadCustomShapePerFrameEvallibVars(CState* pState, int i, int instance)
{
}

void CPlugin::LoadCustomWavePerFrameEvallibVars(CState* pState, int i)
{
}

int SmoothWave(WFVERTEX* vi, int nVertsIn, WFVERTEX* vo)
{
    return 0;
}

void CPlugin::DrawCustomWaves()
{
}

void CPlugin::DrawWave(float *fL, float *fR)
{
    WFVERTEX v[576];
    float cr = (float)(*m_pState->var_pf_wave_r);
    float cg = (float)(*m_pState->var_pf_wave_g);
    float cb = (float)(*m_pState->var_pf_wave_b);
    float ca = (float)(*m_pState->var_pf_wave_a);

    if (ca < 0.001f)
        return;

    for (int i = 0; i < 576; i++)
    {
        v[i].x = (i / 288.0f) - 1.0f;
        v[i].y = fL[i];
        v[i].z = 0.0f;
        v[i].Diffuse = 0xFFFFFFFF;
    }

    glUseProgram(m_wave_shader_program);
    int color_loc = glGetUniformLocation(m_wave_shader_program, "u_color");
    glUniform4f(color_loc, cr, cg, cb, ca);

    glBindVertexArray(m_wave_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_wave_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(v), v);

    if (*m_pState->var_pf_wave_usedots > 0.5)
    {
        glDrawArrays(GL_POINTS, 0, 576);
    }
    else
    {
        if (*m_pState->var_pf_wave_thick > 0.5)
            glLineWidth(2.0f);
        else
            glLineWidth(1.0f);
        glDrawArrays(GL_LINE_STRIP, 0, 576);
    }

    glBindVertexArray(0);
    glUseProgram(0);
    glLineWidth(1.0f);
}

void CPlugin::DrawSprites()
{
    bool bSpritesToDraw = false;
    for (int i = 0; i < NUM_TEX; i++)
    {
        if (m_texmgr.m_tex[i].nLoaded == 1)
        {
            bSpritesToDraw = true;
            break;
        }
    }
    if (!bSpritesToDraw)
        return;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(m_sprite_shader_program);
    glBindVertexArray(m_sprite_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_sprite_vbo);

    for (int i = 0; i < NUM_TEX; i++)
    {
        if (m_texmgr.m_tex[i].nLoaded != 1)
            continue;

        if (m_texmgr.m_tex[i].m_codehandle)
        {
            *m_texmgr.m_tex[i].var_time = (double)(GetTime() - m_texmgr.m_tex[i].fStartTime);
            *m_texmgr.m_tex[i].var_frame = (double)(GetFrame() - m_texmgr.m_tex[i].nStartFrame);
            *m_texmgr.m_tex[i].var_fps = (double)GetFps();
            *m_texmgr.m_tex[i].var_progress = (GetTime() - m_fPresetStartTime) / (m_fNextPresetTime - m_fPresetStartTime);
            *m_texmgr.m_tex[i].var_bass = (double)mysound.imm_rel[0];
            *m_texmgr.m_tex[i].var_mid = (double)mysound.imm_rel[1];
            *m_texmgr.m_tex[i].var_treb = (double)mysound.imm_rel[2];
            *m_texmgr.m_tex[i].var_bass_att = (double)mysound.avg_rel[0];
            *m_texmgr.m_tex[i].var_mid_att = (double)mysound.avg_rel[1];
            *m_texmgr.m_tex[i].var_treb_att = (double)mysound.avg_rel[2];
            *m_texmgr.m_tex[i].var_done = 0;
            *m_texmgr.m_tex[i].var_burn = 0;

            NSEEL_code_execute(m_texmgr.m_tex[i].m_codehandle);

            if (*m_texmgr.m_tex[i].var_done > 0.5f)
            {
                KillSprite(i);
                continue;
            }
        }

        SPRITEVERTEX v[4];

        float x = *m_texmgr.m_tex[i].var_x;
        float y = *m_texmgr.m_tex[i].var_y;
        float sx = *m_texmgr.m_tex[i].var_sx;
        float sy = *m_texmgr.m_tex[i].var_sy;
        float rot = *m_texmgr.m_tex[i].var_rot;
        float r = *m_texmgr.m_tex[i].var_r;
        float g = *m_texmgr.m_tex[i].var_g;
        float b = *m_texmgr.m_tex[i].var_b;
        float a = *m_texmgr.m_tex[i].var_a;
        bool flipx = (*m_texmgr.m_tex[i].var_flipx > 0.5f);
        bool flipy = (*m_texmgr.m_tex[i].var_flipy > 0.5f);
        int blendmode = (int)(*m_texmgr.m_tex[i].var_blendmode + 0.5f);

        if (blendmode == 1)
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        else
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        unsigned char R = (unsigned char)(std::max(0.0f, std::min(1.0f, r)) * 255.0f);
        unsigned char G = (unsigned char)(std::max(0.0f, std::min(1.0f, g)) * 255.0f);
        unsigned char B = (unsigned char)(std::max(0.0f, std::min(1.0f, b)) * 255.0f);
        unsigned char A = (unsigned char)(std::max(0.0f, std::min(1.0f, a)) * 255.0f);
        for (int j = 0; j < 4; j++)
            v[j].Diffuse = (A << 24) | (R << 16) | (G << 8) | B;

        float u1 = 0, u2 = 1, v_1 = 0, v2 = 1;
        if (flipx) { u1 = 1; u2 = 0; }
        if (flipy) { v_1 = 1; v2 = 0; }
        v[0].tu = u1; v[0].tv = v_1;
        v[1].tu = u2; v[1].tv = v_1;
        v[2].tu = u1; v[2].tv = v2;
        v[3].tu = u2; v[3].tv = v2;

        float p[4][2] = {
            {-0.5f, -0.5f}, { 0.5f, -0.5f},
            {-0.5f,  0.5f}, { 0.5f,  0.5f}
        };
        float cos_rot = cosf(rot);
        float sin_rot = sinf(rot);
        for (int j = 0; j < 4; j++)
        {
            float px = p[j][0] * sx;
            float py = p[j][1] * sy;
            float prx = px * cos_rot - py * sin_rot;
            float pry = px * sin_rot + py * cos_rot;
            prx *= m_fAspectY;
            v[j].x = prx + (x * 2.0f - 1.0f);
            v[j].y = pry + (y * -2.0f + 1.0f);
            v[j].z = 0;
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, (GLuint)(uintptr_t)m_texmgr.m_tex[i].pSurface);

        bool repeatx = (*m_texmgr.m_tex[i].var_repeatx > 0.5f);
        bool repeaty = (*m_texmgr.m_tex[i].var_repeaty > 0.5f);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeatx ? GL_REPEAT : GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeaty ? GL_REPEAT : GL_CLAMP_TO_EDGE);

        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(v), v);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    // Restore default blend func
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(0);
    glBindVertexArray(0);
}

void CPlugin::ShowToUser_NoShaders()
{
    // Fallback for non-shader presets
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_render_target_fbo[0]);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, m_nTexSizeX, m_nTexSizeY, 0, 0, GetWidth(), GetHeight(), GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void CPlugin::ShowToUser_Shaders(int nPass, bool bAlphaBlend, bool bFlipAlpha, bool bCullTiles, bool bFlipCulling)
{
    // Bind the default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, GetWidth(), GetHeight());

    // Use the composite shader
    PShaderSet* sh = &m_shaders;
    glUseProgram(sh->comp.program);

    // Set uniforms
    ApplyShaderParams(&sh->comp.params, m_pState);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_render_target_tex[0]);
    glUniform1i(glGetUniformLocation(sh->comp.program, "sampler_main"), 0);
    // TODO: Apply other shader params

    // Draw the fullscreen quad
    glBindVertexArray(m_fs_quad_vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void CPlugin::ShowSongTitleAnim(int w, int h, float fProgress)
{
}

void CPlugin::DrawUserSprites()
{
}

void CPlugin::RestoreShaderParams()
{
}

void CPlugin::ApplyShaderParams(CShaderParams* p, LPD3DXCONSTANTTABLE pCT, CState* pState)
{
}