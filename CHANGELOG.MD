# Instructions for Future Agents

**Please read carefully before making any changes.**

This file is the single source of truth for the project's changelog. To ensure consistency and maintain a clear historical record, please adhere to the following rules:

1.  **Chronological Order:** All new entries must be added to the `[Unreleased]` section at the top. Do not create new version sections.
2.  **Versioning:** Follow the [Semantic Versioning](https://semver.org/) guidelines.
3.  **Formatting:** Maintain the existing format for all entries (`### Added`, `### Changed`, `### Fixed`, etc.).
4.  **Do Not Create New Files:** Do not create separate changelog files. All changes must be recorded in this file.

By following these instructions, you will help us maintain a clean, accurate, and easily parsable changelog.

---

# Changelog

## [Unreleased]

### Fixed
- Fixed several build errors to get the project to compile successfully.

### Documentation
- Updated `README.md` to include a proper section for project documentation.
- Ensured `TODO.MD` is tracked by version control.

## [0.2.0] - 2025-10-07

### Added
- Implemented full menu rendering using FreeType for text rendering.
- Implemented shader-based rendering effects for warp and composite shaders, including support for FBOs and a fullscreen quad.
- Added a `TextRenderer` class to handle font loading and text drawing.
- Added a font file (`DejaVuSans.ttf`) and GLSL shaders for text rendering.
- Implemented `LoadShaders` function to compile shaders from presets.
- Added `LoadShaderFromStrings` helper function to compile shaders from source strings.
- Added `stb_image.h` for cross-platform texture loading.
- **OpenGL Rendering Pipeline:** Implemented the full rendering pipeline for the main visualization components:
    - `DrawWave`: Renders the audio waveform.
    - `DrawCustomShapes`: Renders custom geometric shapes.
    - `DrawSprites`: Renders sprites from texture files.
- **UI Rendering:**
    - Implemented the `DrawRect` function to draw solid-colored rectangles for the menu background and selector bar.
- **Build System:**
    - Added `find_package` calls for `Freetype` and `glm` in `CMakeLists.txt`.
    - Added the `text_renderer.cpp` source file to the build.
- **Shaders:** Added GLSL shaders for the wave, shape, sprite, and menu rendering.

### Changed
- The menu is now fully rendered with text.
- Replaced DirectX-specific code in `support.h` and `support.cpp` with cross-platform OpenGL implementations using `glm`.
- Replaced DirectX-specific code in `texmgr.h` and `texmgr.cpp` with a cross-platform OpenGL implementation using `stb_image`.
- Refined the `CMakeLists.txt` file for better organization, dependency handling, and build configurations.
- **DirectX to OpenGL:** Replaced all remaining DirectX-specific code with their OpenGL equivalents.
- **Input Handling:** Rerouted keyboard input to the `CMilkMenu::HandleKeydown` function, making the menu fully interactive.
- **Dependencies:** The project now depends on `libfreetype-dev` and `libglm-dev` on Debian-based systems.

### Fixed
- Resolved various build issues by installing missing dependencies and fixing incorrect paths.
- Resolved the "blank screen" issue by implementing the full rendering pipeline.
- Fixed the non-interactive menu by correctly handling keyboard input.
- Resolved numerous compilation and linking errors related to the incomplete port.
- Fixed the missing `CPlugin::DrawRect` function, which was causing a linker error.

### Removed
- All stubbed-out functions related to Windows/DirectX have been replaced with functional, cross-platform implementations.
- Removed all calls to the DirectX API, including `GetDevice()`, `SetTexture()`, etc.

### Documentation
- Updated `README.md` to reflect the completed port and the new build instructions.
- Updated `TODO.MD` to mark the completed tasks.

## [0.1.0] - 2025-10-06

### Added
- Implemented core rendering pipeline using OpenGL.