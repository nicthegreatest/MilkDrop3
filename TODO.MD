# TODO

This file outlines the remaining tasks to complete the Linux port of MilkDrop3.

## High Priority

- **Complete UI and Event Handling Port:** The initial refactoring of `pluginshell` and `menu` has removed the direct Windows API dependencies from the class definitions, but the work is incomplete. The next critical step is to fully implement the cross-platform UI and event handling.
    - **Implement `MyKeyHandler` Call Site:** The main application loop in `main.cpp` must be updated to set up a GLFW key callback that calls the `MyKeyHandler` function on the `CPlugin` instance. This will reconnect keyboard input.
    - **Implement Menu Logic:** The `HandleKeydown` function in `menu.cpp` needs to be implemented to process key events for menu navigation.
    - **Implement Menu Rendering:** The `DrawMenu` function in `menu.cpp` must be implemented to render the menu using OpenGL, as the original GDI-based implementation has been removed.
    - **Remove Remaining Stubs:** Any remaining UI-related stubs or placeholder functions should be fully implemented or removed.

- **Debug Blank Screen Issue:** With the UI and event handling refactored, the primary focus can return to the blank screen issue. The goal is to get the visualizer to render correctly. This will likely involve:
    - Verifying that the vertex data is being passed to the shaders correctly.
    - Checking the shader compilation and linking for errors.
    - Ensuring that textures are being loaded and bound correctly.
    - Using `glGetError()` to check for OpenGL errors.

- **(Partially Complete) Remove Windows API Dependencies:** The core `pluginshell` and `menu` classes have been refactored to remove Windows-specific types from their public interfaces. However, other dependencies may remain elsewhere in the codebase.

## Medium Priority

- **`libsamplerate` Dependency:** The new `EEL_VM` library has an optional dependency on `libsamplerate` which is currently missing. The build may fail on code paths that require it. We need to either provide this dependency or ensure the code paths are not used.

- **Cleanup Stubbed Headers:** The headers `support.h` and `texmgr.h` are currently stubbed out on Linux. As the OpenGL port progresses, these stubs should be replaced with proper OpenGL-based implementations.

- **Address Compiler Warnings:** The build still produces a number of warnings related to `const`-correctness and other issues in the `ns-eel2` library. These should be cleaned up.

## Low Priority

- **Review and Refine Build System:** The `CMakeLists.txt` file has been modified to get the project compiling, but it could be improved and organized for better cross-platform support.

## Completed

- **Port Rendering from DirectX to OpenGL:** The core rendering logic in `vis_milk2/` has been ported to OpenGL.
    - **Vertex and Texture Management:** All code related to creating and managing vertex buffers, vertex declarations, and textures has been ported from DirectX to OpenGL (VBOs, VAOs, `glTexImage2D`, etc.).
    - **Shaders:** The DirectX HLSL shaders have been ported to GLSL.