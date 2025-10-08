# MilkDrop 3 - Linux Port

This is a fork of the original MilkDrop 3 visualizer, with the goal of porting it from its original Windows/DirectX architecture to a modern, cross-platform C++ application that runs on Linux using OpenGL.

## Original Authors

The original MilkDrop codebase was created by Nullsoft. All credit for the original visualization engine and algorithms goes to them.

---

## Project Documentation

For a detailed list of the major changes that have been completed, see [CHANGELOG.MD](CHANGELOG.MD).

For a list of the remaining tasks required to get the project running, see [TODO.MD](TODO.MD).

---

## Project Status (Linux Port)

This project is currently undergoing a significant refactoring effort to port the original Windows/DirectX codebase to a modern, cross-platform C++ application that can be compiled and run on Linux using OpenGL.

The menu system is now visible and functional, with correct text rendering and navigation. The "Next Preset" and "Previous Preset" menu items now correctly cycle through presets. Presets can be loaded, and the application attempts to render them, although a black screen is currently displayed after loading a preset, with no errors in the console. The `plugins/MilkDrop2/presets` directory is now included in the build process.


## Building and Running

### Prerequisites

- A C++ compiler (g++)
- CMake
- Git
- The following development libraries:
    - `glfw3`
    - `portaudio-2.0`
    - `opengl`
    - `libglm-dev`
    - `libfreetype6-dev`

### Building

1.  Clone the repository.
2.  Create a build directory: `mkdir build`
3.  Navigate to the build directory: `cd build`
4.  Run CMake: `cmake ../code`
5.  Run Make: `make`

### Running

After a successful build, the executable will be located at `build/milkdrop3`. Run it from the `build` directory:

```
cd build
./milkdrop3
```