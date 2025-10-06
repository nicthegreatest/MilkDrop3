# MilkDrop 3 - Linux Port

This is a fork of the original MilkDrop 3 visualizer, with the goal of porting it from its original Windows/DirectX architecture to a modern, cross-platform C++ application that runs on Linux using OpenGL.

## Original Authors

The original MilkDrop codebase was created by Nullsoft. All credit for the original visualization engine and algorithms goes to them.

---

## Project Status (Linux Port)

This project is currently undergoing a significant refactoring effort to port the original Windows/DirectX codebase to a modern, cross-platform C++ application that can be compiled and run on Linux using OpenGL.

The UI and event-handling components (`pluginshell` and `menu`) have been refactored to remove Windows-specific dependencies and replace them with a cross-platform approach. However, persistent build environment issues are preventing the application from being compiled and tested, so the impact of these changes on the blank screen issue is currently unverified.

The application now compiles and runs, opening a window. However, the screen is currently black, and the rendering pipeline is being actively debugged.

For a detailed list of the major changes that have been completed, see [CHANGELOG.MD](CHANGELOG.MD).

For a list of the remaining tasks required to get the project running, see [TODO.MD](TODO.MD).

## Building and Running

### Prerequisites

- A C++ compiler (g++)
- CMake
- Git
- The following development libraries:
    - `glfw3`
    - `portaudio-2.0`
    - `opengl`

### Building

1.  Clone the repository.
2.  Create a build directory: `mkdir build`
3.  Navigate to the build directory: `cd build`
4.  Run CMake: `cmake ../code`
5.  Run Make: `make`

### Running

After a successful build, the executable will be located at `build/milkdrop3`. Run it from the `build` directory:

```
./milkdrop3
```