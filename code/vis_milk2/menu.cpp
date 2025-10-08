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
#include <GLFW/glfw3.h>
#include <math.h>
#include <assert.h>
#include "resource.h"

extern CPlugin *g_plugin;

CMilkMenuItem::CMilkMenuItem()
{
	wasabiApiLangString(IDS_UNTITLED_MENU_ITEM, m_szName, sizeof(m_szName));
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
	wasabiApiLangString(IDS_UNTITLED_MENU, m_szMenuName, sizeof(m_szMenuName));
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
						float min, float max, float step, MilkMenuCallbackFnPtr pCallback,
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
	pLastItem->m_var_offset = (size_t)var - (size_t)(g_plugin->m_pState);
	pLastItem->m_type = type;
	pLastItem->m_fMin = min;
	pLastItem->m_fMax = max;
    pLastItem->m_fStep = step;
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

void CMilkMenu::DrawMenu()
{
    int w = g_plugin->GetWidth();
    int h = g_plugin->GetHeight();
    int nItems = m_nChildMenus + m_nChildItems;
    int font_h = 14;
    int line_h = 16;
    int menu_h = (nItems + 1) * line_h;
    int menu_w = 300;
    int x = w/2 - menu_w/2;
    int y = h/2 - menu_h/2;

    // Draw background
    RECT r = { x, y, x + menu_w, y + menu_h };
    g_plugin->DrawRect(&r, 0xC0000000);

    // Draw selector bar
    RECT sel_r = { x, y + (m_nCurSel) * line_h, x + menu_w, y + (m_nCurSel + 1) * line_h };
    g_plugin->DrawRect(&sel_r, 0xC0FFFFFF);

    // Draw menu items
    int i = 0;
    for (i = 0; i < m_nChildMenus; i++)
    {
        glm::vec3 color = (i == m_nCurSel) ? glm::vec3(0.0f, 0.0f, 0.0f) : glm::vec3(1.0f, 1.0f, 1.0f);
        g_plugin->m_text_renderer->RenderText(m_ppChildMenu[i]->GetName(), x + 10, y + i * line_h + 2, 1.0f, color);
    }

    CMilkMenuItem *pItem = m_pFirstChildItem;
    while (pItem)
    {
        glm::vec3 color = (i == m_nCurSel) ? glm::vec3(0.0f, 0.0f, 0.0f) : glm::vec3(1.0f, 1.0f, 1.0f);
        g_plugin->m_text_renderer->RenderText(pItem->m_szName, x + 10, y + i * line_h + 2, 1.0f, color);
        pItem = pItem->m_pNext;
        i++;
    }
}

void CMilkMenu::OnWaitStringAccept(char *szNewString)
{
	m_bEditingCurSel = false;
	CMilkMenuItem *pItem = GetCurItem();
	size_t addr = pItem->m_var_offset + (size_t)g_plugin->m_pState;
	assert(pItem->m_type == MENUITEMTYPE_STRING);
	strcpy((char *)(addr), szNewString);
	if (pItem->m_pCallbackFn)
	{
		pItem->m_pCallbackFn(0, 0);
	}
	pItem->m_nLastCursorPos = g_plugin->m_waitstring.nCursorPos;
}

void CMilkMenu::HandleKeydown(int key)
{
    int nItems = m_nChildMenus + m_nChildItems;
    if (nItems == 0) return;

    if (key == GLFW_KEY_UP)
    {
        m_nCurSel = (m_nCurSel - 1 + nItems) % nItems;
    }
    else if (key == GLFW_KEY_DOWN)
    {
        m_nCurSel = (m_nCurSel + 1) % nItems;
    }
    else if (key == GLFW_KEY_LEFT)
    {
        if (m_nCurSel >= m_nChildMenus)
        {
            CMilkMenuItem* pItem = GetCurItem();
            if (pItem)
            {
                size_t addr = pItem->m_var_offset + (size_t)g_plugin->m_pState;
                switch (pItem->m_type)
                {
                    case MENUITEMTYPE_FLOAT:
                    case MENUITEMTYPE_LOGFLOAT:
                    case MENUITEMTYPE_BLENDABLE:
                    case MENUITEMTYPE_LOGBLENDABLE:
                        *(float*)addr -= pItem->m_fStep * (pItem->m_fMax - pItem->m_fMin);
                        if (*(float*)addr < pItem->m_fMin) *(float*)addr = pItem->m_fMin;
                        break;
                    case MENUITEMTYPE_INT:
                        *(int*)addr -= 1;
                        if (*(int*)addr < pItem->m_fMin) *(int*)addr = pItem->m_fMin;
                        break;
                }
            }
        }
    }
    else if (key == GLFW_KEY_RIGHT)
    {
        if (m_nCurSel >= m_nChildMenus)
        {
            CMilkMenuItem* pItem = GetCurItem();
            if (pItem)
            {
                size_t addr = pItem->m_var_offset + (size_t)g_plugin->m_pState;
                switch (pItem->m_type)
                {
                    case MENUITEMTYPE_FLOAT:
                    case MENUITEMTYPE_LOGFLOAT:
                    case MENUITEMTYPE_BLENDABLE:
                    case MENUITEMTYPE_LOGBLENDABLE:
                        *(float*)addr += pItem->m_fStep * (pItem->m_fMax - pItem->m_fMin);
                        if (*(float*)addr > pItem->m_fMax) *(float*)addr = pItem->m_fMax;
                        break;
                    case MENUITEMTYPE_INT:
                        *(int*)addr += 1;
                        if (*(int*)addr > pItem->m_fMax) *(int*)addr = pItem->m_fMax;
                        break;
                }
            }
        }
    }
    else if (key == GLFW_KEY_ENTER)
    {
        if (m_nCurSel < m_nChildMenus)
        {
            g_plugin->m_pCurMenu = m_ppChildMenu[m_nCurSel];
        }
        else
        {
            CMilkMenuItem* pItem = GetCurItem();
            if (pItem)
            {
                if (pItem->m_pCallbackFn)
                {
                    pItem->m_pCallbackFn(pItem->m_wParam, pItem->m_lParam);
                }
                else
                {
                    size_t addr = pItem->m_var_offset + (size_t)g_plugin->m_pState;
                    if (pItem->m_type == MENUITEMTYPE_BOOL)
                    {
                        *(bool*)addr = !*(bool*)addr;
                    }
                }
            }
        }
    }
    else if (key == GLFW_KEY_ESCAPE)
    {
        if (m_pParentMenu)
        {
            g_plugin->m_pCurMenu = m_pParentMenu;
        }
        else
        {
            g_plugin->m_bShowMenu = false;
        }
    }
}