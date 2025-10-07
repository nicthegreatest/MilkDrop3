# TODO

This file outlines the remaining tasks to complete the Linux port of MilkDrop3.

## High Priority

- **Implement Full Menu Rendering:** The menu's background and selector bar are now rendering, but the text for menu items is still missing. The next major task is to implement a text rendering solution to draw the menu items and make the menu fully interactive. This will likely involve integrating a library like FreeType.

- **Implement Shader-based Rendering Effects:** The `WarpedBlit_Shaders` and `ShowToUser_Shaders` functions are currently placeholders. These need to be fully implemented to support the advanced visual effects from presets, which are a core feature of MilkDrop.

## Medium Priority

- **Cleanup Stubbed Headers:** The headers `support.h` and `texmgr.h` are currently stubbed out on Linux. As the OpenGL port progresses, these stubs should be replaced with proper OpenGL-based implementations.

- **Address Compiler Warnings:** The build still produces a number of warnings related to `const`-correctness and other issues in the `ns-eel2` library. These should be cleaned up.

## Low Priority

- **Review and Refine Build System:** The `CMakeLists.txt` file has been modified to get the project compiling, but it could be improved and organized for better cross-platform support.

## Completed

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