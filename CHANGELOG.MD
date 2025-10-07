# Changelog

## [Unreleased]

### Added
- Implemented core rendering pipeline using OpenGL.
- Implemented `DrawWave`, `DrawCustomShapes`, and `DrawSprites` functions.
- Added OpenGL shaders for waves, shapes, and sprites.
- Added VAO and VBO management for rendering resources.
- Implemented `LoadShader` and `LoadShaderFromStrings` to handle shader compilation.
- Implemented basic menu rendering with background and selector bar.
- Added `DrawRect` helper function for drawing colored rectangles.

### Fixed
- Resolved all remaining build errors from the initial DirectX to OpenGL port.
- Replaced Windows-specific `PluginShellWindowProc` with cross-platform `MyKeyHandler`.
- Removed legacy DirectX calls to `GetDevice()`.
- Fixed duplicate function definition for `DrawRect`.
- Corrected protected access level for `GetWidth` and `GetHeight` in `CPluginShell`.
- Added missing includes for `<string>`, `<fstream>`, and `<sstream>` in `pluginshell.cpp`.

### Changed
- The application now renders the main visual components instead of a blank screen.
- The menu is now partially visible, though text rendering is not yet implemented.