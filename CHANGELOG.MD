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

### Added
- Implemented copying of the `plugins/MilkDrop2/presets` directory to the build directory during the CMake process.

### Changed
- Modified the initial preset loading and "Load Preset" menu item to load a specific preset (`flexi - bouncing balls [mindblob terraforming] flx roams domikleasing undergraeduhate.milk`) for testing purposes.

### Fixed
- Resolved multiple definition and undefined reference linker errors by correctly defining `CPlugin::MyRenderFn` and ensuring `CPlugin::RenderFrame` is only defined once.
- Corrected the logic for "Next Preset" and "Previous Preset" menu items to cycle through presets instead of loading random ones.
- Corrected the texture coordinates in `TextRenderer::RenderText` to fix the horizontally reversed text issue.
- Ensured the UI elements are rendered by adding a call to `CPlugin::MyRenderUI` in the main application loop.

### Documentation
- Updated `README.md` to include a proper section for project documentation.
- Ensured `TODO.MD` is tracked by version control.

### Added
- Implemented the full menu system, including the main menu and sub-menus for Wave, Custom Waves, Custom Shapes, Motion, and Post Processing.
- Populated all menus with their respective controls, linking them to the application's state variables.
- Implemented full keyboard navigation for the menu system, including up/down for selection, left/right for value changes, Enter for activation, and Escape for exiting.
- Added callbacks for all menu actions, including preset loading/saving, fullscreen toggling, and info display.

### Changed
- Refactored the menu callback system to use static member functions, resolving build errors related to non-static member function pointers.
- The `CPlugin::ToggleFullscreen` function is now fully implemented using GLFW for cross-platform window management.
- The `CPluginShell::m_lpDX` member is now `protected` to allow derived classes to access the `GLContext`.

### Fixed
- Resolved all compiler warnings, including `const`-correctness issues and potential buffer overflows.
- Fixed several build errors to get the project to compile successfully.

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