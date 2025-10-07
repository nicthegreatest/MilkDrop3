# Changelog

## [Unreleased]

### Added
- Implemented full menu rendering using FreeType for text rendering.
- Implemented shader-based rendering effects for warp and composite shaders, including support for FBOs and a fullscreen quad.
- Added a `TextRenderer` class to handle font loading and text drawing.
- Added a font file (`DejaVuSans.ttf`) and GLSL shaders for text rendering.
- Implemented `LoadShaders` function to compile shaders from presets.
- Added `LoadShaderFromStrings` helper function to compile shaders from source strings.
- Added `stb_image.h` for cross-platform texture loading.

### Fixed
- Resolved all remaining build errors from the initial DirectX to OpenGL port.
- Replaced Windows-specific `PluginShellWindowProc` with cross-platform `MyKeyHandler`.
- Removed legacy DirectX calls to `GetDevice()`.
- Fixed duplicate function definition for `DrawRect`.
- Corrected protected access level for `GetWidth` and `GetHeight` in `CPluginShell`.
- Added missing includes for `<string>`, `<fstream>`, and `<sstream>` in `pluginshell.cpp`.
- Corrected various build issues by installing missing dependencies and fixing incorrect paths.

### Changed
- The application now renders the main visual components instead of a blank screen.
- The menu is now fully rendered with text.
- Replaced DirectX-specific code in `support.h` and `support.cpp` with cross-platform OpenGL implementations using `glm`.
- Replaced DirectX-specific code in `texmgr.h` and `texmgr.cpp` with a cross-platform OpenGL implementation using `stb_image`.
- Refined the `CMakeLists.txt` file for better organization, dependency handling, and build configurations.