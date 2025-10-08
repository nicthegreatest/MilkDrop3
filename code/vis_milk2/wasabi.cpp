#include "wasabi.h"
#include <stdio.h>
#include "resource.h"
#include <string.h>

// Stub implementation for wasabi API functions.
// These functions will need to be replaced with a proper cross-platform implementation.

const char* wasabiApiLangString(int id, char* buffer, int len) {
    if (buffer != NULL && len > 0) {
        const char* str = wasabiApiLangString(id);
        strncpy(buffer, str, len);
        buffer[len-1] = 0;
        return buffer;
    }
    return "Error: Invalid buffer";
}

const char* wasabiApiLangString(int id) {
    static char buffer[1024];

    switch(id) {
        case IDS_WARNING_PRESET_X_ERROR_IN_PER_FRAME_CODE:
            return "Warning: preset '%s' had an error in the 'per_frame' code.";
        case IDS_WARNING_PRESET_X_ERROR_IN_PER_VERTEX_CODE:
            return "Warning: preset '%s' had an error in the 'per_vertex' code.";
        case IDS_WARNING_PRESET_X_ERROR_IN_WAVE_X_INIT_CODE:
            return "Warning: preset '%s' had an error in wave %d's init code.";
        case IDS_WARNING_PRESET_X_ERROR_IN_WAVE_X_PER_FRAME_CODE:
            return "Warning: preset '%s' had an error in wave %d's per-frame code.";
        case IDS_WARNING_PRESET_X_ERROR_IN_WAVE_X_PER_POINT_CODE:
            return "Warning: preset '%s' had an error in wave %d's per-point code.";
        case IDS_WARNING_PRESET_X_ERROR_IN_SHAPE_X_INIT_CODE:
             return "Warning: preset '%s' had an error in shape %d's init code.";
        case IDS_WARNING_PRESET_X_ERROR_IN_SHAPE_X_PER_FRAME_CODE:
             return "Warning: preset '%s' had an error in shape %d's per-frame code.";
        default:
            snprintf(buffer, sizeof(buffer), "LangString %d", id);
            return buffer;
    }
}

HMENU wasabiApiLoadMenu(int id) {
    // Return a dummy value.
    return (HMENU)1;
}

HWND wasabiApiCreateDialogParam(int templateName, HWND parent, DLGPROC proc, long initParam) {
    // Return a dummy value.
    return (HWND)1;
}