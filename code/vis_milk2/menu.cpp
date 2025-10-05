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

#include "state.h"
#include "menu.h"
#include "plugin.h"
#include "wasabi.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "resource.h"

// Virtual-key codes
#define VK_BACK           0x08
#define VK_RETURN         0x0D
#define VK_SHIFT          0x10
#define VK_CONTROL        0x11
#define VK_ESCAPE         0x1B
#define VK_SPACE          0x20
#define VK_PRIOR          0x21
#define VK_NEXT           0x22
#define VK_END            0x23
#define VK_HOME           0x24
#define VK_LEFT           0x25
#define VK_UP             0x26
#define VK_RIGHT          0x27
#define VK_DOWN           0x28
#define VK_INSERT         0x2D
#define VK_DELETE         0x2E

extern CPlugin g_plugin;

CMilkMenuItem::CMilkMenuItem()
{
	wasabiApiLangString(IDS_UNTITLED_MENU_ITEM,m_szName,64);
	m_szToolTip[0] = 0;
	m_type = MENUITEMTYPE_BUNK;
	m_fMin = 0.0f;
	m_fMax = 0.0f;
	m_var_offset = 0;
	m_pCallbackFn = NULL;
	m_pNext = NULL;
	m_original_value = 0;
	m_nLastCursorPos = 0;
    m_bEnabled = true;
}

CMilkMenuItem::~CMilkMenuItem()
{
	if (m_pNext)
	{
		delete m_pNext;
		m_pNext = NULL;
	}
}

CMilkMenu::CMilkMenu() {}
CMilkMenu::~CMilkMenu() {}

bool CMilkMenu::ItemIsEnabled(int j)
{
    if (j < m_nChildMenus)
        return m_ppChildMenu[j]->IsEnabled();

    int i = m_nChildMenus;
    CMilkMenuItem *pChild = m_pFirstChildItem;
    while (pChild && i<j)
    {
        pChild = pChild->m_pNext;
        i++;
    }
    if (pChild)
        return pChild->m_bEnabled;

    return false;
}

void CMilkMenu::EnableItem(const char* szName, bool bEnable)
{
    for (int i=0; i<m_nChildMenus; i++) {
        if (!strcmp(m_ppChildMenu[i]->GetName(), szName))
        {
            m_ppChildMenu[i]->Enable(bEnable);
            return;
        }
    }

    CMilkMenuItem *pChild = m_pFirstChildItem;
    while (pChild)
    {
        if (!strcmp(pChild->m_szName, szName))
        {
            pChild->m_bEnabled = bEnable;
            return;
        }
        pChild = pChild->m_pNext;
    }
}

void CMilkMenu::Reset()
{
	m_pParentMenu = NULL;
	for (int i=0; i<MAX_CHILD_MENUS; i++)
		m_ppChildMenu[i] = NULL;
	m_pFirstChildItem = NULL;
	wasabiApiLangString(IDS_UNTITLED_MENU,m_szMenuName,64);
	m_nChildMenus = 0;
	m_nChildItems = 0;
	m_nCurSel = 0;
	m_bEditingCurSel = false;
    m_bEnabled = true;
}

void CMilkMenu::Init(const char *szName)
{
    Reset();
    if (szName && szName[0])
        strncpy(m_szMenuName, szName, 64);
}

void CMilkMenu::Finish()
{
	if (m_pFirstChildItem)
	{
		delete m_pFirstChildItem;
		m_pFirstChildItem = NULL;
	}
}

void CMilkMenu::AddChildMenu(CMilkMenu *pMenu)
{
	if (m_nChildMenus < MAX_CHILD_MENUS)
	{
		m_ppChildMenu[m_nChildMenus++] = pMenu;
		pMenu->SetParentPointer(this);
	}
}

void CMilkMenu::AddItem(const char *szName, void *var, MENUITEMTYPE type, const char *szToolTip,
						float min, float max, MilkMenuCallbackFnPtr pCallback,
						unsigned int wParam, unsigned int lParam)
{
	CMilkMenuItem *pLastItem = NULL;
	if (!m_pFirstChildItem)
	{
		m_pFirstChildItem = new CMilkMenuItem;
		pLastItem = m_pFirstChildItem;
	}
	else
	{
		pLastItem = m_pFirstChildItem;
		while (pLastItem->m_pNext)
			pLastItem = pLastItem->m_pNext;
		pLastItem->m_pNext = new CMilkMenuItem;
		pLastItem = pLastItem->m_pNext;
	}
	strncpy(pLastItem->m_szName, szName, 64);
	strncpy(pLastItem->m_szToolTip, szToolTip, 1024);
	pLastItem->m_var_offset = (size_t)var - (size_t)(g_plugin.m_pState);
	pLastItem->m_type = type;
	pLastItem->m_fMin = min;
	pLastItem->m_fMax = max;
    pLastItem->m_wParam = wParam;
    pLastItem->m_lParam = lParam;
	if ((type==MENUITEMTYPE_LOGBLENDABLE || type==MENUITEMTYPE_LOGFLOAT) && min==max)
	{
		pLastItem->m_fMin = 0.01f;
		pLastItem->m_fMax = 100.0f;
	}
	pLastItem->m_pCallbackFn = pCallback;
	m_nChildItems++;
}

void MyMenuTextOut(eFontIndex font_index, const char* str, DWORD color, RECT* pRect, int bCalcRect, RECT* pCalcRect)
{
    // Stubbed out for now
}

void CMilkMenu::DrawMenu(RECT rect, int xR, int yB, int bCalcRect, RECT* pCalcRect)
{
    // Stubbed out
}

void CMilkMenu::OnWaitStringAccept(char *szNewString)
{
	m_bEditingCurSel = false;
	CMilkMenuItem *pItem = GetCurItem();
	size_t addr = pItem->m_var_offset + (size_t)g_plugin.m_pState;
	assert(pItem->m_type == MENUITEMTYPE_STRING);
	strcpy((char *)(addr), szNewString);
	if (pItem->m_pCallbackFn)
	{
		pItem->m_pCallbackFn(0, 0);
	}
	pItem->m_nLastCursorPos = g_plugin.m_waitstring.nCursorPos;
}

LRESULT CMilkMenu::HandleKeydown(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // Stubbed out - keyboard handling will be done in main loop
    return 1;
}