# 🎮 SDL2Lib

A lightweight wrapper library for SDL2, designed to simplify common tasks such as rendering, event handling, and logging.

---

## 📚 Table of Contents
- [🛠 Installation](#-installation)
- [🛠️ Build](#-build)
- [💡 Usage](#-usage)
- [📂 Project Structure](#-project-structure)

---

## 🛠 Installation

Clone the repository via HTTPS or SSH:

```bash
git clone https://github.com/your-repo/SDL2Game.git
cd SDL2Game
```

### Required Packages

Make sure the following dependencies are installed on your system:

- `git`
- `cmake`
- `g++`
- `clang`
- `valgrind`
- `clang-tidy`
- `clang-format`
- `libsdl2-dev`
- `libsdl2-ttf-dev`
- `libsdl2-image-dev`
- `libsdl2-mixer-dev`
- `lcov`

To install these on a Debian-based system, run:

```bash
sudo apt-get install git cmake g++ clang valgrind clang-tidy clang-format libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev lcov
```

---

## 🛠️ Build

To build the library, follow these steps:

1. Create a build directory:
   ```bash
   mkdir build
   ```

2. Generate the build files using CMake:
   ```bash
   cmake -S . -B build/
   ```

3. Build the project:
   ```bash
   cd build
   make
   ```

Alternatively, if you are in the workspace folder, you can use:
```bash
make all
```

The compiled library and any executables will be available in the `build/` directory.

---

## 💡 Usage

Here is an example of how to initialize the library and use its features:

```cpp
#include "Logger.h"
#include "SDLSystem.h"
#include "Window.h"
#include "Renderer.h"
#include "Container.h"

int main() {
    Logger::initialize("logs/log.txt", Logger::LogLevel::info);

    SDLSystem sdl(SDL_INIT_VIDEO, static_cast<SDLSystem::InitOptions>(SDLSystem::ttf | SDLSystem::audio));

    Window window("SDL2",
                  SDL_WINDOWPOS_CENTERED,
                  SDL_WINDOWPOS_CENTERED,
                  DEFAULT_SCREEN_WIDTH,
                  DEFAULT_SCREEN_HEIGHT,
                  SDL_WINDOW_SHOWN);

    Renderer renderer(window.getWindow(), -1, SDL_RENDERER_ACCELERATED);
    renderer.setRenderDrawColor(Color(0, 0, 0, 255));

    Container container;
    container.setRenderer(renderer.getRenderer());

    // Your game logic here...

    return 0;
}
```

---

## 📂 Project Structure

```
SDL2Game/
├── .github/              # github workflows
├── assets/               # Game assets (fonts, images, sounds)
├── build/                # Build artifacts
├── lib/                  # Libraries (cpputest)
├── logs/                 # Log files
├── tests/                # Lib tests
├── tests/                # Lib classes
├── .clang-format         # Clang format configuration
├── .clang-tidy           # Clang tidy configuration
├── CMakeLists.txt        # CMake build configuration
└── Readme.md             # Project documentation
```