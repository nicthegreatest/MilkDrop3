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

#ifndef _MILKDROP_MENU_H_
#define _MILKDROP_MENU_H_ 1

#include <stddef.h> // for ptrdiff_t
#include "shell_defines.h"

// Windows-specific types are now defined in shell_defines.h.

//----------------------------------------

typedef enum {
	MENUITEMTYPE_BUNK,
	MENUITEMTYPE_BOOL,
	MENUITEMTYPE_INT,
	MENUITEMTYPE_FLOAT,
	MENUITEMTYPE_LOGFLOAT,
	MENUITEMTYPE_BLENDABLE,
	MENUITEMTYPE_LOGBLENDABLE,
	MENUITEMTYPE_STRING,
    MENUITEMTYPE_UIMODE,
	//MENUITEMTYPE_OSC,
} MENUITEMTYPE;
#define MAX_CHILD_MENUS 16
typedef void (*MilkMenuCallbackFnPtr)(LPARAM param1, LPARAM param2);

//----------------------------------------
class CMilkMenuItem
{
public:
	CMilkMenuItem();
	~CMilkMenuItem();

	char			m_szName[64];
	char			m_szToolTip[1024];
	MENUITEMTYPE	m_type;
	float			m_fMin;
	float			m_fMax;
    unsigned int    m_wParam;
    unsigned int    m_lParam;
	MilkMenuCallbackFnPtr m_pCallbackFn;
	ptrdiff_t       m_var_offset;
	LPARAM			m_original_value;
	int				m_nLastCursorPos;
    bool            m_bEnabled;
	CMilkMenuItem	*m_pNext;
};
//----------------------------------------

//----------------------------------------
class CMilkMenu
{
public:
	CMilkMenu();
	~CMilkMenu();

	void	Init(const char *szName);
    void    Finish();
	void	AddChildMenu(CMilkMenu *pChildMenu);
	void	AddItem(const char *szName, void *var, MENUITEMTYPE type, const char *szToolTip,
					float min=0, float max=0, MilkMenuCallbackFnPtr pCallback=NULL,
                    unsigned int wParam=0, unsigned int lParam=0);
	void	SetParentPointer(CMilkMenu *pParentMenu) { m_pParentMenu = pParentMenu; }
	LRESULT HandleKeydown(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	void	DrawMenu(RECT rect, int xR, int yB, int bCalcRect=0, RECT* pCalcRect=NULL);
	void	OnWaitStringAccept(char *szNewString);
    void    EnableItem(const char* szName, bool bEnable);
    CMilkMenuItem* GetCurItem()
    {
		CMilkMenuItem *pItem = m_pFirstChildItem;
		for (int i=m_nChildMenus; i < m_nCurSel; i++)
			pItem = pItem->m_pNext;
        return pItem;
    }
    const char* GetName() { return m_szMenuName; }
    void Enable(bool bEnabled) { m_bEnabled = bEnabled; }
    bool IsEnabled() { return m_bEnabled; }
    bool ItemIsEnabled(int i);

protected:
    void            Reset();
	CMilkMenu		*m_pParentMenu;
	CMilkMenu		*m_ppChildMenu[MAX_CHILD_MENUS];
	CMilkMenuItem	*m_pFirstChildItem;
	char			m_szMenuName[64];
	int				m_nChildMenus;
	int				m_nChildItems;
	int				m_nCurSel;
	bool			m_bEditingCurSel;
    bool            m_bEnabled;
};
//----------------------------------------

#endif //_MILKDROP_MENU_H_