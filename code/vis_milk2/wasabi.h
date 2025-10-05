#pragma once

// Forward declarations for cross-platform compatibility
struct HMENU__;
typedef HMENU__* HMENU;
struct HWND__;
typedef HWND__* HWND;
typedef int (*DLGPROC)(HWND, unsigned int, unsigned int, long);

// Stub functions for cross-platform build.
// These will need to be implemented with a cross-platform UI/localization library.
const char* wasabiApiLangString(int id, char* buffer, int len);
const char* wasabiApiLangString(int id);
HMENU wasabiApiLoadMenu(int id);
HWND wasabiApiCreateDialogParam(int templateName, HWND parent, DLGPROC proc, long initParam);