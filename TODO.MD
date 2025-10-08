# TODO

This file outlines the remaining tasks to complete the Linux port of MilkDrop3.

## High Priority

- **Implement a proper preset file browser:** Currently, presets are loaded via hardcoded paths. A user-friendly interface to browse and select preset files is needed.
- **Fix black screen after preset load:** Investigate why presets are not rendering after being loaded, even though no errors are reported.

## Completed

- **Include presets folder in build:** The `plugins/MilkDrop2/presets` directory is now copied to the build directory during the CMake process.
- **Fix linker errors:** Resolved multiple definition and undefined reference linker errors.
- **Fix menu item logic:** Corrected the logic for "Next Preset" and "Previous Preset" menu items.
- **Fix horizontally reversed text:** Corrected the texture coordinates in `TextRenderer::RenderText`.
- **Ensure UI elements are rendered:** Added a call to `CPlugin::MyRenderUI` in the main application loop.
- **Address Compiler Warnings:** The build still produces a number of warnings related to `const`-correctness and other issues in the `ns-eel2` library. These should be cleaned up.

- **Implement Full Menu Rendering:**
    - Integrated FreeType for text rendering.
    - Added a `TextRenderer` class to handle font loading and text drawing.
    - The menu now renders with text.

- **Implement Shader-based Rendering Effects:**
    - The `WarpedBlit_Shaders` and `ShowToUser_Shaders` functions are now fully implemented.
    - Added support for FBOs for off-screen rendering.
    - Implemented shader loading from presets.

- **Cleanup Stubbed Headers:**
    - Replaced DirectX-specific code in `support.h` and `support.cpp` with OpenGL/glm.
    - Replaced DirectX-specific code in `texmgr.h` and `texmgr.cpp` with OpenGL/stb_image.

- **Review and Refine Build System:**
    - Reorganized the `CMakeLists.txt` file for better readability.
    - Improved dependency handling using modern CMake practices.
    - Set build-type-specific compiler flags.
    - Added install rules for the application and its data files.

- **Core Rendering Pipeline:**
    - The `DrawWave`, `DrawCustomShapes`, and `DrawSprites` functions have been implemented using OpenGL, shaders, VAOs, and VBOs. The application now renders the waveform, custom shapes, and sprites.
    - The application now successfully builds and runs without any major rendering errors.

- **UI and Event Handling Port:**
    - **`MyKeyHandler` Call Site:** The main application loop in `main.cpp` now correctly calls the `MyKeyHandler` function on the `CPlugin` instance, connecting keyboard input.
    - **Menu Logic:** The `HandleKeydown` function in `menu.cpp` has been implemented to process key events for menu navigation.

- **Build and Runtime Stability:**
    - Resolved numerous build and runtime errors, including a segmentation fault on startup.
    - Installed all necessary dependencies (`portaudio`, `glfw`, `opengl`, `libsamplerate`).
    - The application now compiles and runs reliably in a headless environment using `Xvfb`.

- **Removed Windows API Dependencies:** The core `pluginshell` and `menu` classes have been refactored to remove Windows-specific types from their public interfaces. Most Windows-specific functions have been stubbed out or replaced.