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

#include "textmgr.h"
#include "support.h"
#include "utility.h"
#include <string.h>
#include <stdio.h>

#define MAX_MSG_CHARS (65536*2)

char g_szMsgPool[2][MAX_MSG_CHARS];

CTextManager::CTextManager()
{
}

CTextManager::~CTextManager()
{
}

void CTextManager::Init(LPDIRECT3DDEVICE9 lpDevice, IDirect3DTexture9* lpTextSurface, int bAdditive)
{
    m_lpDevice = lpDevice;
    m_lpTextSurface = lpTextSurface;
    m_blit_additively = bAdditive;

    m_b = 0;
    m_nMsg[0] = 0;
    m_nMsg[1] = 0;
    m_next_msg_start_ptr = g_szMsgPool[m_b];
}

void CTextManager::Finish()
{
}

void CTextManager::ClearAll()
{
    m_nMsg[m_b] = 0;
    m_next_msg_start_ptr = g_szMsgPool[m_b];
}

void CTextManager::DrawBox(LPRECT pRect, DWORD boxColor)
{
    if (!pRect)
        return;

    if ((m_nMsg[m_b] < MAX_MSGS) &&
        (size_t)m_next_msg_start_ptr - (size_t)g_szMsgPool[m_b] + 1 < MAX_MSG_CHARS)
    {
        *m_next_msg_start_ptr = 0;

        m_msg[m_b][m_nMsg[m_b]].msg   = m_next_msg_start_ptr;
        m_msg[m_b][m_nMsg[m_b]].pfont = NULL;
        m_msg[m_b][m_nMsg[m_b]].rect  = *pRect;
        m_msg[m_b][m_nMsg[m_b]].flags = 0;
        m_msg[m_b][m_nMsg[m_b]].color = 0xFFFFFFFF;
        m_msg[m_b][m_nMsg[m_b]].bgColor = boxColor;
        m_nMsg[m_b]++;
        m_next_msg_start_ptr += 1;
    }
}

int CTextManager::DrawTextA(LPD3DXFONT pFont, const char* szText, int len, RECT* pRect, DWORD flags, DWORD color, bool bBox, DWORD boxColor)
{
    if (!(pFont && pRect && szText))
        return 0;

    if (flags & 0x400 /*DT_CALCRECT*/) // Stub for DT_CALCRECT
    {
        // This should calculate text bounds, but we'll stub it.
        // A real implementation would use FreeType or similar.
        pRect->right = pRect->left + len * 8; // Estimate width
        pRect->bottom = pRect->top + 16;      // Estimate height
        return 16;
    }

    if (!m_lpDevice)
        return 0;

    if (len == -1)
        len = strlen(szText);

    if ((m_nMsg[m_b] < MAX_MSGS) &&
        (size_t)m_next_msg_start_ptr - (size_t)g_szMsgPool[m_b] + len + 1 < MAX_MSG_CHARS)
    {
        strcpy(m_next_msg_start_ptr, szText);

        m_msg[m_b][m_nMsg[m_b]].msg   = m_next_msg_start_ptr;
        m_msg[m_b][m_nMsg[m_b]].pfont = pFont;
        m_msg[m_b][m_nMsg[m_b]].rect  = *pRect;
        m_msg[m_b][m_nMsg[m_b]].flags = flags;
        m_msg[m_b][m_nMsg[m_b]].color = color;
        m_msg[m_b][m_nMsg[m_b]].bgColor = boxColor;

        m_nMsg[m_b]++;
        m_next_msg_start_ptr += len + 1;

        if (bBox)
        {
            DrawBox(&m_msg[m_b][m_nMsg[m_b]-1].rect, boxColor);
            td_string x = m_msg[m_b][m_nMsg[m_b]-1];
            m_msg[m_b][m_nMsg[m_b]-1] = m_msg[m_b][m_nMsg[m_b]-2];
            m_msg[m_b][m_nMsg[m_b]-2] = x;
        }
        return 16; // estimated height
    }

    return 16; // estimated height
}

int CTextManager::DrawTextW(LPD3DXFONT pFont, const wchar_t* szText, int len, RECT* pRect, DWORD flags, DWORD color, bool bBox, DWORD boxColor)
{
    // This function is now a stub. All text rendering should go through DrawTextA.
    // A proper implementation would convert wchar_t to char* and call DrawTextA.
    return 0;
}


void CTextManager::DrawNow()
{
    // This function originally handled the rendering of text to a texture and then
    // blitting it to the screen. Since we've removed DirectX, this logic needs to be
    // replaced with an OpenGL-based text rendering solution. For now, this is a stub.
    // A real implementation would iterate through m_msg and draw using something like FreeType.

    // flip buffers and clear for next frame
    m_b = 1 - m_b;
    ClearAll();
}