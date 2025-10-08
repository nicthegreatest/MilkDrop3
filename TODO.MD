# TODO

This file outlines the remaining tasks to complete the Linux port of MilkDrop3.

## High Priority

- **Reference `MilkDrop3-Windows` for feature implementation:** When implementing or porting features, refer to the `MilkDrop3-Windows` directory for the original implementation details and logic.
- **Fix EEL script compilation and execution:** Presets are not rendering correctly due to errors in the EEL scripts. This is the new highest priority.
- **Implement proper preset file browser:** Replace the hardcoded preset loading with a functional file browser to allow users to select any `.milk` file.
- **Implement "Save Preset" functionality:** Allow users to save modified presets.
- **Implement "Toggle Help" and "Toggle Info" display:** Show actual help text and preset information.

## Medium Priority

- **Implement advanced preset features:** Double-presets (.milk2 files) and their associated UI/logic.
- **Implement advanced key shortcuts:** (majuscule/minuscule, player control, filtering).
- **Implement Always on top window and borderless mode:** (beyond basic fullscreen toggle).
- **Implement Multiple monitor stretching.**
- **Implement Real-time toggling FPS and auto transition seconds.**
- **Implement Increased number of shapes (16 vs 4) and waves (16 vs 4).**
- **Implement `.shape` and `.wave` file export.**
- **Implement Expanded q variables (q1-q64).**
- **Implement Deep-mash-up.**
- **Implement Sprite blending modes and controls.**
- **Implement MilkPanel:** (shader editor, options, playlist management, dark mode, save button).
- **Implement Playlist support:** (add/remove, load/save).
- **Implement Startup playlist selection.**
- **Implement Hide from taskbar/errors.**
- **Implement Select screen number for startup.**
- **Implement Save image directly in .milk/.milk2.**
- **Implement Drag and Drop.**
- **Implement Delete mode.**
- **Implement Auto-update shader on compilation error.**
- **Implement Sprites mode vs. Messages mode.**
- **Implement DPI scaling fixes.**
- **Implement Adjustable font size.**
- **Implement Launch external programs.**
- **Implement Hi-Res audio support.**
- **Implement ATI/AMD PS4 shaders.**
- **Implement New shader cache.**
- **Implement New custom VM.**
- **Implement Modern presets.**
- **Implement Hardcut Mode #7.**
- **Implement VJ mode.**
- **Implement See all Q variables values at once.**
- **Implement New transition effects.**
- **Implement Optimized functions.**

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
- **Fix black screen after preset load:** The initial black screen issue has been resolved by enabling the rendering pipeline and implementing basic drawing functions. Further work is required to fix EEL script execution.
- **Implement basic drawing functions:** `DrawCustomWaves`, `DrawCustomShapes`, and `DrawMotionVectors` now have basic implementations, allowing for some visual output.
- **Fix EEL script parsing:** Corrected a bug in `StripLinefeedCharsAndComments` that was causing EEL script compilation to fail.