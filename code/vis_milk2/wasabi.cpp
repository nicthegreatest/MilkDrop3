#include "wasabi.h"
#include "resource.h"
#include <string>
#include <map>

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
    g_lang_string_table[IDS_PRESET_NOT_FOUND] = "Preset not found.";
    g_lang_string_table[IDS_PRESET_FILE_EMPTY] = "Preset file empty.";
    g_lang_string_table[IDS_NO_PRESETS_IN_DIR] = "No presets in directory.";
    g_lang_string_table[IDS_NO_HELP_AVAILABLE] = "No help available.";
    g_lang_string_table[IDS_NO_SONG_TITLE] = "No song title.";
    g_lang_string_table[IDS_UNKNOWN_ERROR] = "Unknown error.";
    g_lang_string_table[IDS_WARNING_UNKNOWN_VARIABLE_IN_PRESET_X] = "Warning: unknown variable '%s' in preset.";
    g_lang_string_table[IDS_WARNING_UNKNOWN_FUNCTION_IN_PRESET_X] = "Warning: unknown function '%s' in preset.";
    g_lang_string_table[IDS_WARNING_INVALID_PARAMETERS_IN_PRESET_X] = "Warning: invalid parameters for function '%s' in preset.";
    g_lang_string_table[IDS_WARNING_SYNTAX_ERROR_IN_PRESET_X] = "Warning: syntax error in preset '%s'.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_NO_CODE] = "Warning: preset '%s' has no code.";
    g_lang_string_table[IDS_WARNING_PRESET_X_IS_MISSING_A_SECTION] = "Warning: preset '%s' is missing a section.";
    g_lang_string_table[IDS_WARNING_PRESET_X_IS_NOT_A_VALID_PRESET_FILE] = "Warning: preset '%s' is not a valid preset file.";
    g_lang_string_table[IDS_WARNING_PRESET_X_IS_CORRUPT] = "Warning: preset '%s' is corrupt.";
    g_lang_string_table[IDS_WARNING_PRESET_X_IS_TOO_LARGE] = "Warning: preset '%s' is too large.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_VERSION] = "Warning: preset '%s' has an invalid version.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_VERSION] = "Warning: preset '%s' has an unsupported version.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_PS_VERSION] = "Warning: preset '%s' has an invalid pixel shader version.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_PS_VERSION] = "Warning: preset '%s' has an unsupported pixel shader version.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_WAVE_TYPE] = "Warning: preset '%s' has an invalid wave type.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_WAVE_TYPE] = "Warning: preset '%s' has an unsupported wave type.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_SHAPE_TYPE] = "Warning: preset '%s' has an invalid shape type.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_SHAPE_TYPE] = "Warning: preset '%s' has an unsupported shape type.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_BLEND_MODE] = "Warning: preset '%s' has an invalid blend mode.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_BLEND_MODE] = "Warning: preset '%s' has an unsupported blend mode.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_COLOR_MAP] = "Warning: preset '%s' has an invalid color map.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_COLOR_MAP] = "Warning: preset '%s' has an unsupported color map.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_TEXTURE_SIZE] = "Warning: preset '%s' has an invalid texture size.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_TEXTURE_SIZE] = "Warning: preset '%s' has an unsupported texture size.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_GRID_SIZE] = "Warning: preset '%s' has an invalid grid size.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_GRID_SIZE] = "Warning: preset '%s' has an unsupported grid size.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_MOTION_VECTOR_COUNT] = "Warning: preset '%s' has an invalid motion vector count.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_MOTION_VECTOR_COUNT] = "Warning: preset '%s' has an unsupported motion vector count.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_SPRITE_COUNT] = "Warning: preset '%s' has an invalid sprite count.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_SPRITE_COUNT] = "Warning: preset '%s' has an unsupported sprite count.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_CUSTOM_WAVE_COUNT] = "Warning: preset '%s' has an invalid custom wave count.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_CUSTOM_WAVE_COUNT] = "Warning: preset '%s' has an unsupported custom wave count.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_CUSTOM_SHAPE_COUNT] = "Warning: preset '%s' has an invalid custom shape count.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_CUSTOM_SHAPE_COUNT] = "Warning: preset '%s' has an unsupported custom shape count.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_CUSTOM_MESSAGE_COUNT] = "Warning: preset '%s' has an invalid custom message count.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_CUSTOM_MESSAGE_COUNT] = "Warning: preset '%s' has an unsupported custom message count.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_CUSTOM_MESSAGE_FONT_COUNT] = "Warning: preset '%s' has an invalid custom message font count.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_CUSTOM_MESSAGE_FONT_COUNT] = "Warning: preset '%s' has an unsupported custom message font count.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_CUSTOM_MESSAGE_FONT] = "Warning: preset '%s' has an invalid custom message font.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_CUSTOM_MESSAGE_FONT] = "Warning: preset '%s' has an unsupported custom message font.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_CUSTOM_MESSAGE] = "Warning: preset '%s' has an invalid custom message.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_CUSTOM_MESSAGE] = "Warning: preset '%s' has an unsupported custom message.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_SPRITE] = "Warning: preset '%s' has an invalid sprite.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_SPRITE] = "Warning: preset '%s' has an unsupported sprite.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_CUSTOM_WAVE] = "Warning: preset '%s' has an invalid custom wave.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_CUSTOM_WAVE] = "Warning: preset '%s' has an unsupported custom wave.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_CUSTOM_SHAPE] = "Warning: preset '%s' has an invalid custom shape.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_CUSTOM_SHAPE] = "Warning: preset '%s' has an unsupported custom shape.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_BORDER] = "Warning: preset '%s' has an invalid border.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_BORDER] = "Warning: preset '%s' has an unsupported border.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_MOTION_VECTORS] = "Warning: preset '%s' has an invalid motion vectors.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_MOTION_VECTORS] = "Warning: preset '%s' has an unsupported motion vectors.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_VIDEO_ECHO] = "Warning: preset '%s' has an invalid video echo.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_VIDEO_ECHO] = "Warning: preset '%s' has an unsupported video echo.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_STEREO_3D_MODE] = "Warning: preset '%s' has an invalid stereo 3d mode.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_STEREO_3D_MODE] = "Warning: preset '%s' has an unsupported stereo 3d mode.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_TEXTURE_WRAP_MODE] = "Warning: preset '%s' has an invalid texture wrap mode.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_TEXTURE_WRAP_MODE] = "Warning: preset '%s' has an unsupported texture wrap mode.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_FILTER_MODE] = "Warning: preset '%s' has an invalid filter mode.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_FILTER_MODE] = "Warning: preset '%s' has an unsupported filter mode.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_GAMMA_VALUE] = "Warning: preset '%s' has an invalid gamma value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_GAMMA_VALUE] = "Warning: preset '%s' has an unsupported gamma value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_DECAY_VALUE] = "Warning: preset '%s' has an invalid decay value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_DECAY_VALUE] = "Warning: preset '%s' has an unsupported decay value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_WAVE_ALPHA_VALUE] = "Warning: preset '%s' has an invalid wave alpha value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_WAVE_ALPHA_VALUE] = "Warning: preset '%s' has an unsupported wave alpha value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_WAVE_SCALE_VALUE] = "Warning: preset '%s' has an invalid wave scale value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_WAVE_SCALE_VALUE] = "Warning: preset '%s' has an unsupported wave scale value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_WAVE_SMOOTHING_VALUE] = "Warning: preset '%s' has an invalid wave smoothing value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_WAVE_SMOOTHING_VALUE] = "Warning: preset '%s' has an unsupported wave smoothing value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_WAVE_PARAM_VALUE] = "Warning: preset '%s' has an invalid wave param value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_WAVE_PARAM_VALUE] = "Warning: preset '%s' has an unsupported wave param value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_MOD_WAVE_ALPHA_START_VALUE] = "Warning: preset '%s' has an invalid mod wave alpha start value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_MOD_WAVE_ALPHA_START_VALUE] = "Warning: preset '%s' has an unsupported mod wave alpha start value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_MOD_WAVE_ALPHA_END_VALUE] = "Warning: preset '%s' has an invalid mod wave alpha end value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_MOD_WAVE_ALPHA_END_VALUE] = "Warning: preset '%s' has an unsupported mod wave alpha end value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_WARP_ANIM_SPEED_VALUE] = "Warning: preset '%s' has an invalid warp anim speed value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_WARP_ANIM_SPEED_VALUE] = "Warning: preset '%s' has an unsupported warp anim speed value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_WARP_SCALE_VALUE] = "Warning: preset '%s' has an invalid warp scale value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_WARP_SCALE_VALUE] = "Warning: preset '%s' has an unsupported warp scale value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_ZOOM_EXPONENT_VALUE] = "Warning: preset '%s' has an invalid zoom exponent value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_ZOOM_EXPONENT_VALUE] = "Warning: preset '%s' has an unsupported zoom exponent value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_SHADER_VALUE] = "Warning: preset '%s' has an invalid shader value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_SHADER_VALUE] = "Warning: preset '%s' has an unsupported shader value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_ZOOM_VALUE] = "Warning: preset '%s' has an invalid zoom value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_ZOOM_VALUE] = "Warning: preset '%s' has an unsupported zoom value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_ROT_VALUE] = "Warning: preset '%s' has an invalid rot value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_ROT_VALUE] = "Warning: preset '%s' has an unsupported rot value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_CX_VALUE] = "Warning: preset '%s' has an invalid cx value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_CX_VALUE] = "Warning: preset '%s' has an unsupported cx value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_CY_VALUE] = "Warning: preset '%s' has an invalid cy value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_CY_VALUE] = "Warning: preset '%s' has an unsupported cy value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_DX_VALUE] = "Warning: preset '%s' has an invalid dx value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_DX_VALUE] = "Warning: preset '%s' has an unsupported dx value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_DY_VALUE] = "Warning: preset '%s' has an invalid dy value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_DY_VALUE] = "Warning: preset '%s' has an unsupported dy value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_WARP_VALUE] = "Warning: preset '%s' has an invalid warp value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_WARP_VALUE] = "Warning: preset '%s' has an unsupported warp value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_SX_VALUE] = "Warning: preset '%s' has an invalid sx value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_SX_VALUE] = "Warning: preset '%s' has an unsupported sx value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_SY_VALUE] = "Warning: preset '%s' has an invalid sy value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_SY_VALUE] = "Warning: preset '%s' has an unsupported sy value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_WAVE_R_VALUE] = "Warning: preset '%s' has an invalid wave_r value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_WAVE_R_VALUE] = "Warning: preset '%s' has an unsupported wave_r value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_WAVE_G_VALUE] = "Warning: preset '%s' has an invalid wave_g value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_WAVE_G_VALUE] = "Warning: preset '%s' has an unsupported wave_g value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_WAVE_B_VALUE] = "Warning: preset '%s' has an invalid wave_b value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_WAVE_B_VALUE] = "Warning: preset '%s' has an unsupported wave_b value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_WAVE_X_VALUE] = "Warning: preset '%s' has an invalid wave_x value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_WAVE_X_VALUE] = "Warning: preset '%s' has an unsupported wave_x value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_WAVE_Y_VALUE] = "Warning: preset '%s' has an invalid wave_y value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_WAVE_Y_VALUE] = "Warning: preset '%s' has an unsupported wave_y value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_OB_SIZE_VALUE] = "Warning: preset '%s' has an invalid ob_size value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_OB_SIZE_VALUE] = "Warning: preset '%s' has an unsupported ob_size value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_OB_R_VALUE] = "Warning: preset '%s' has an invalid ob_r value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_OB_R_VALUE] = "Warning: preset '%s' has an unsupported ob_r value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_OB_G_VALUE] = "Warning: preset '%s' has an invalid ob_g value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_OB_G_VALUE] = "Warning: preset '%s' has an unsupported ob_g value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_OB_B_VALUE] = "Warning: preset '%s' has an invalid ob_b value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_OB_B_VALUE] = "Warning: preset '%s' has an unsupported ob_b value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_OB_A_VALUE] = "Warning: preset '%s' has an invalid ob_a value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_OB_A_VALUE] = "Warning: preset '%s' has an unsupported ob_a value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_IB_SIZE_VALUE] = "Warning: preset '%s' has an invalid ib_size value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_IB_SIZE_VALUE] = "Warning: preset '%s' has an unsupported ib_size value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_IB_R_VALUE] = "Warning: preset '%s' has an invalid ib_r value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_IB_R_VALUE] = "Warning: preset '%s' has an unsupported ib_r value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_IB_G_VALUE] = "Warning: preset '%s' has an invalid ib_g value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_IB_G_VALUE] = "Warning: preset '%s' has an unsupported ib_g value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_IB_B_VALUE] = "Warning: preset '%s' has an invalid ib_b value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_IB_B_VALUE] = "Warning: preset '%s' has an unsupported ib_b value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_IB_A_VALUE] = "Warning: preset '%s' has an invalid ib_a value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_IB_A_VALUE] = "Warning: preset '%s' has an unsupported ib_a value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_MV_X_VALUE] = "Warning: preset '%s' has an invalid mv_x value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_MV_X_VALUE] = "Warning: preset '%s' has an unsupported mv_x value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_MV_Y_VALUE] = "Warning: preset '%s' has an invalid mv_y value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_MV_Y_VALUE] = "Warning: preset '%s' has an unsupported mv_y value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_MV_DX_VALUE] = "Warning: preset '%s' has an invalid mv_dx value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_MV_DX_VALUE] = "Warning: preset '%s' has an unsupported mv_dx value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_MV_DY_VALUE] = "Warning: preset '%s' has an invalid mv_dy value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_MV_DY_VALUE] = "Warning: preset '%s' has an unsupported mv_dy value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_MV_L_VALUE] = "Warning: preset '%s' has an invalid mv_l value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_MV_L_VALUE] = "Warning: preset '%s' has an unsupported mv_l value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_MV_R_VALUE] = "Warning: preset '%s' has an invalid mv_r value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_MV_R_VALUE] = "Warning: preset '%s' has an unsupported mv_r value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_MV_G_VALUE] = "Warning: preset '%s' has an invalid mv_g value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_MV_G_VALUE] = "Warning: preset '%s' has an unsupported mv_g value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_MV_B_VALUE] = "Warning: preset '%s' has an invalid mv_b value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_MV_B_VALUE] = "Warning: preset '%s' has an unsupported mv_b value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_INVALID_MV_A_VALUE] = "Warning: preset '%s' has an invalid mv_a value.";
    g_lang_string_table[IDS_WARNING_PRESET_X_HAS_AN_UNSUPPORTED_MV_A_VALUE] = "Warning: preset '%s' has an unsupported mv_a value.";
    g_lang_string_table[IDS_RATING_5_STARS] = "5 stars";
    g_lang_string_table[IDS_RATING_4_STARS] = "4 stars";
    g_lang_string_table[IDS_RATING_3_STARS] = "3 stars";
    g_lang_string_table[IDS_RATING_2_STARS] = "2 stars";
    g_lang_string_table[IDS_RATING_1_STAR] = "1 star";
    g_lang_string_table[IDS_RATING_NOT_RATED] = "Not rated";

    g_lang_table_initialized = true;
}

const char* wasabiApiLangString(int resource_id)
{
    if (!g_lang_table_initialized)
    {
        InitLangStringTable();
    }

    if (g_lang_string_table.count(resource_id))
    {
        return g_lang_string_table[resource_id].c_str();
    }

    static char buf[256];
    sprintf(buf, "LangString %d", resource_id);
    return buf;
}

std::string& GetString(int resource_id, std::string& str)
{
    str = wasabiApiLangString(resource_id);
    return str;
}