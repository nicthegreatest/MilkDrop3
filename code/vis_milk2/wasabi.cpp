#include "wasabi.h"
#include "resource.h"
#include <string>
#include <map>
#include <stdio.h>
#include <string.h>

static std::map<int, std::string> g_lang_string_table;
static bool g_lang_table_initialized = false;

void InitLangStringTable()
{
    if (g_lang_table_initialized) return;

    g_lang_string_table[IDS_NULLSOFT_MILKDROP_201] = "Nullsoft MilkDrop 2.01";
    g_lang_string_table[IDS_DESKTOP_MODE_IS_DISABLED_IN_THE_CONFIG_PANEL] = "Desktop mode is disabled in the config panel.";
    g_lang_string_table[IDS_PLUGIN_ERROR] = "Plugin Error";
    g_lang_string_table[IDS_ERROR_DRAWING_THE_PRESET_LIST_IN_THE_MENU] = "Error drawing the preset list in the menu.";
    g_lang_string_table[IDS_ERROR_ENTERING_DESKTOP_MODE] = "Error entering desktop mode.";
    g_lang_string_table[IDS_ERROR_INITIALIZING_DIRECT3D] = "Error initializing Direct3D.";
    g_lang_string_table[IDS_ERROR_LOADING_A_TEXTURE] = "Error loading a texture.";
    g_lang_string_table[IDS_ERROR_LOADING_DEFAULT_PRESET] = "Error loading default preset.";
    g_lang_string_table[IDS_ERROR_LOADING_PRESET] = "Error loading preset.";
    g_lang_string_table[IDS_ERROR_LOADING_PRESET_FILE_LIST] = "Error loading preset file list.";
    g_lang_string_table[IDS_ERROR_LOADING_SPRITE_TEXTURE] = "Error loading sprite texture.";
    g_lang_string_table[IDS_ERROR_READING_CUSTOM_MESSAGE_FONTS_FROM_CONFIG_FILE] = "Error reading custom message fonts from config file.";
    g_lang_string_table[IDS_ERROR_READING_CUSTOM_MESSAGES_FROM_CONFIG_FILE] = "Error reading custom messages from config file.";
    g_lang_string_table[IDS_ERROR_SAVING_A_TEXTURE] = "Error saving a texture.";
    g_lang_string_table[IDS_ERROR_SAVING_PRESET] = "Error saving preset.";
    g_lang_string_table[IDS_ERROR_SETTING_DISPLAY_MODE] = "Error setting display mode.";
    g_lang_string_table[IDS_ERROR_SETTING_DESKTOP_TO_CORRECT_MODE] = "Error setting desktop to correct mode.";
    g_lang_string_table[IDS_ERROR_CREATING_VERTEX_DECLARATION_FOR_CUSTOM_WAVES_AND_SHAPES] = "Error creating vertex declaration for custom waves and shapes.";
    g_lang_string_table[IDS_ERROR_CREATING_VERTEX_DECLARATION_FOR_SPRITES] = "Error creating vertex declaration for sprites.";
    g_lang_string_table[IDS_ERROR_CREATING_VERTEX_DECLARATION_FOR_THE_DEFORMATION_MESH] = "Error creating vertex declaration for the deformation mesh.";
    g_lang_string_table[IDS_GDI_DESKTOP_MODE_REQUIRES_A_RESTART] = "GDI desktop mode requires a restart.";
    g_lang_string_table[IDS_HELP_TEXT_NOT_IMPLEMENTED_YET] = "Help text not implemented yet.";
    g_lang_string_table[IDS_INSTASCAN_IS_NOW_OFF] = "Instascan is now OFF.";
    g_lang_string_table[IDS_INSTASCAN_IS_NOW_ON] = "Instascan is now ON.";
    g_lang_string_table[IDS_NO_16_BIT_DESKTOP_SUPPORT] = "No 16-bit desktop support.";
    g_lang_string_table[IDS_NO_PRESETS_FOUND] = "No presets found.";
    g_lang_string_table[IDS_NO_SPRITE_TEXTURES_FOUND] = "No sprite textures found.";
    g_lang_string_table[IDS_PRESET_LOCKED] = "Preset locked.";
    g_lang_string_table[IDS_PRESET_UNLOCKED] = "Preset unlocked.";
    g_lang_string_table[IDS_PRESS_F1_FOR_HELP] = "Press F1 for help.";
    g_lang_string_table[IDS_PRESS_L_TO_LOAD_A_PRESET] = "Press 'L' to load a preset.";
    g_lang_string_table[IDS_RATING_cleared] = "Rating cleared.";
    g_lang_string_table[IDS_SCROLL_LOCK_IS_ON_PRESET_LOCKED] = "Scroll lock is ON. Preset locked.";
    g_lang_string_table[IDS_SCROLL_LOCK_IS_OFF_PRESET_UNLOCKED] = "Scroll lock is OFF. Preset unlocked.";
    g_lang_string_table[IDS_SEQUENTIAL_PRESET_ORDER_IS_NOW_OFF] = "Sequential preset order is now OFF.";
    g_lang_string_table[IDS_SEQUENTIAL_PRESET_ORDER_IS_NOW_ON] = "Sequential preset order is now ON.";
    g_lang_string_table[IDS_SHADER_HELP] = "Shader Help";
    g_lang_string_table[IDS_SPRITE_MODE_IS_NOW_OFF] = "Sprite mode is now OFF.";
    g_lang_string_table[IDS_SPRITE_MODE_IS_NOW_ON] = "Sprite mode is now ON.";
    g_lang_string_table[IDS_UNTITLED_MENU] = "Untitled Menu";
    g_lang_string_table[IDS_UNTITLED_MENU_ITEM] = "Untitled Menu Item";
    g_lang_string_table[IDS_WARNING_FALLING_BACK_TO_PS_1_1] = "Warning: falling back to PS_1_1.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAD_AN_ERROR_IN_THE_COMPOSITE_SHADER] = "Warning: preset '%s' had an error in the composite shader.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAD_AN_ERROR_IN_THE_WARP_SHADER] = "Warning: preset '%s' had an error in the warp shader.";
    g_lang_string_table[IDS_WARNING_PRESET_X_ERROR_IN_PRESET_INIT_CODE] = "Warning: preset '%s' had an error in the 'preset init' code.";
    g_lang_string_table[IDS_WARNING_PRESET_X_ERROR_IN_PER_FRAME_CODE] = "Warning: preset '%s' had an error in the 'per_frame' code.";
    g_lang_string_table[IDS_WARNING_PRESET_X_ERROR_IN_PER_VERTEX_CODE] = "Warning: preset '%s' had an error in the 'per_vertex' code.";
    g_lang_string_table[IDS_WARNING_PRESET_X_ERROR_IN_WAVE_X_INIT_CODE] = "Warning: preset '%s' had an error in wave %d's init code.";
    g_lang_string_table[IDS_WARNING_PRESET_X_ERROR_IN_WAVE_X_PER_FRAME_CODE] = "Warning: preset '%s' had an error in wave %d's per-frame code.";
    g_lang_string_table[IDS_WARNING_PRESET_X_ERROR_IN_WAVE_X_PER_POINT_CODE] = "Warning: preset '%s' had an error in wave %d's per-point code.";
    g_lang_string_table[IDS_WARNING_PRESET_X_ERROR_IN_SHAPE_X_INIT_CODE] = "Warning: preset '%s' had an error in shape %d's init code.";
    g_lang_string_table[IDS_WARNING_PRESET_X_ERROR_IN_SHAPE_X_PER_FRAME_CODE] = "Warning: preset '%s' had an error in shape %d's per-frame code.";
    g_lang_string_table[IDS_WARNING_THE_FOLLOWING_SPRITE_TEXTURE_WAS_NOT_FOUND] = "Warning: the following sprite texture was not found: ";
    g_lang_string_table[IDS_YOU_HAVE_RATED_THIS_PRESET_X_5] = "You have rated this preset %d/5.";
    g_lang_string_table[IDS_INVALID_PRESET_FILE] = "Invalid preset file.";

    g_lang_table_initialized = true;
}

const char* wasabiApiLangString(int resource_id, char* buf, int buf_len)
{
    if (!g_lang_table_initialized)
    {
        InitLangStringTable();
    }

    if (g_lang_string_table.count(resource_id))
    {
        strncpy(buf, g_lang_string_table[resource_id].c_str(), buf_len - 1);
        buf[buf_len - 1] = '\0';
        return buf;
    }

    snprintf(buf, buf_len, "LangString %d", resource_id);
    return buf;
}