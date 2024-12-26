# CPPGAME
cppgame is a C++20 game development framework designed to simplify the creation and management of 2D games. It provides a comprehensive set of tools and abstractions to handle common game development tasks, such as window management, rendering, scene management, and game object manipulation. The library is structured to be modular and extensible, allowing developers to focus on game logic rather than low-level details.

# Key Features
- **Rendering** - cppgame provides a simple and efficient rendering system based on OpenGL. It supports rendering of sprites, text, and shapes, as well as custom shaders.
- **Input Handling** - cppgame provides a flexible input handling system that supports keyboard, mouse, and gamepad input.
- **Scene Management** - cppgame provides a scene management system that allows developers to easily switch between different game scenes.

# Getting Started
To get started with cppgame, you will need to download the library and add the include folder to your projects additional include directories. You will also need to link against cppgame.lib and copy the cppgame.dll file to your projects output directory to be available at runtime.

# Dependencies
- **GLFW** - cppgame uses GLFW to create and manage windows.
- **stb_image** - cppgame uses stb_image to load textures from disk.