# MilkDrop 3 - Linux Port

This is a fork of the original MilkDrop 3 visualizer, with the goal of porting it from its original Windows/DirectX architecture to a modern, cross-platform C++ application that runs on Linux using OpenGL.

## Original Authors

The original MilkDrop codebase was created by Nullsoft. All credit for the original visualization engine and algorithms goes to them.

---

## Project Status (Linux Port)

This project is currently undergoing a significant refactoring effort to port the original Windows/DirectX codebase to a modern, cross-platform C++ application that can be compiled and run on Linux using OpenGL.

The porting process is ongoing. The application currently compiles and runs, but displays a **blank black screen**.

For a detailed list of the major changes that have been completed, see [CHANGELOG.MD](CHANGELOG.MD).

For a list of the remaining tasks required to get the project running, see [TODO.MD](TODO.MD).

### Current Issue: Blank Screen

The main blocker is an issue with the OpenGL rendering context. Although the application creates a window, it fails to render any content, resulting in a black screen. This is due to an issue with GLEW initialization, which is preventing any OpenGL calls from succeeding.

## Building and Running

### Prerequisites

- A C++ compiler (g++)
- CMake
- Git
- The following development libraries:
    - `glfw3`
    - `glew`
    - `portaudio-2.0`
    - `opengl`

### Building

1.  Clone the repository.
2.  Create a build directory: `mkdir code/build`
3.  Navigate to the build directory: `cd code/build`
4.  Run CMake: `cmake ..`
5.  Run Make: `make`

### Running

After a successful build, the executable will be located at `code/build/milkdrop3`. Run it from the `code/build` directory:

```
./milkdrop3
```
