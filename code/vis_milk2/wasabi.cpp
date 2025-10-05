#include "wasabi.h"
#include <stdio.h>

// Stub implementation for wasabi API functions.
// These functions will need to be replaced with a proper cross-platform implementation.

const char* wasabiApiLangString(int id, char* buffer, int len) {
    if (buffer != NULL && len > 0) {
        snprintf(buffer, len, "LangString %d", id);
        return buffer;
    }
    return "Error: Invalid buffer";
}

const char* wasabiApiLangString(int id) {
    static char buffer[1024];
    snprintf(buffer, sizeof(buffer), "LangString %d", id);
    return buffer;
}

HMENU wasabiApiLoadMenu(int id) {
    // Return a dummy value.
    return (HMENU)1;
}

HWND wasabiApiCreateDialogParam(int templateName, HWND parent, DLGPROC proc, long initParam) {
    // Return a dummy value.
    return (HWND)1;
}