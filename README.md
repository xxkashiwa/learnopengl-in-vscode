- [README English](./README_en.md)
- [README Chinese](./README.md)

## learnopengl_proj(MinGW+VSCode)

如果你只想获得vscode环境的从头开始的learnopengl，请从base分支clone项目。

一个基于 [LearnOpenGL](https://learnopengl.com/) 的学习 / 练习工程，使用 CMake 管理构建，依赖 GLFW 和 GLAD。

主要结构：

- CMakeLists.txt：工程入口 CMake 配置
- glfw-3.4/：GLFW 源码（作为子目录构建）
- include/、glad/、GLFW/、KHR/：头文件
- shaders/：着色器文件
- src/：源码目录（例如 main.cpp、glad.c）

### 开发环境

推荐环境：

- Windows 10/11
- CMake ≥ 3.20
- MinGW-w64（例如 MSYS2 提供的 ucrt64 工具链）
- Ninja 或 MinGW 自带 make（本工程默认使用 `MinGW Makefiles` 生成器）
- VS Code + C/C++ 扩展（ms-vscode.cpptools）

请确认 `cmake` 和 MinGW 的 `gcc`/`g++` 在 PATH 中，例如：

```powershell
$ cmake --version
$ gcc --version
```

### 从命令行启动

在项目根目录执行以下命令完成配置和构建：

```powershell
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

构建成功后，可执行文件（例如 `learnopengl.exe`）会生成在 `build/` 目录下。可以在 PowerShell 中运行：

```powershell
./build/learnopengl.exe
```

如果你在 `CMakeLists.txt` 中修改了目标名，请相应地调整可执行文件名称。

### 从VSCode启动

在安装VS Code + C/C++ 扩展（ms-vscode.cpptools）扩展之后，直接点击编辑器窗口右上角的启动/调试按钮，然后选择Debug learnopengl (MinGW)，它会先执行cmake configure然后再进行build（详细内容查看.vscode/launch.json和tasks.json）
