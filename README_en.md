- [README English](./README_en.md)
- [README Chinese](./README.md)

## learnopengl_proj (MinGW + VS Code)

This is a learning / practice project based on [LearnOpenGL](https://learnopengl.com/). It uses CMake for build management and depends on GLFW and GLAD.

### Project Structure

- [CMakeLists.txt](CMakeLists.txt): Root CMake configuration for the project
- [glfw-3.4/](glfw-3.4): GLFW source code (built as a subdirectory)
- [include/](include), [glad/](glad), [GLFW/](GLFW), [KHR/](KHR): Header files
- [shaders/](shaders): Shader source files
- [src/](src): Source code directory (e.g. `main.cpp`, `glad.c`)

### Recommended Environment

- Windows 10/11
- CMake ≥ 3.20
- MinGW-w64 toolchain (for example, the `ucrt64` environment from MSYS2)
- Ninja or MinGW `make` (this project is configured by default for the `MinGW Makefiles` generator)
- VS Code + C/C++ extension (`ms-vscode.cpptools`)

Make sure `cmake` and MinGW `gcc` / `g++` are available in your `PATH`, for example:

```powershell
cmake --version
gcc --version
```

### Run from Command Line

From the project root, run the following commands to configure and build:

```powershell
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

After a successful build, the executable (for example `learnopengl.exe`) will be generated under `build/`. You can run it from PowerShell:

```powershell
./build/learnopengl.exe
```

If you changed the target name in `CMakeLists.txt`, adjust the executable name accordingly.

### Develop and Debug in VS Code

After installing the VS Code C/C++ extension (`ms-vscode.cpptools`), you can start debugging directly from the editor:

- Click the Run/Debug button in the top-right corner of the VS Code window
- Choose **Debug learnopengl (MinGW)**

The configured launch task will first run CMake configure and then build the project (see `.vscode/launch.json` and `.vscode/tasks.json` for details). Once the build succeeds, VS Code will launch the program under the MinGW GDB debugger.

### Notes

- If you switch toolchains (e.g. a different MinGW or generator), delete the `build` directory and re-run CMake configuration.
- If CMake cannot find `gcc`/`g++`, verify that your MinGW `bin` directory is in the `PATH` of the shell where you run VS Code / CMake.
