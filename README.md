# Raycasting_doomlike

[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

![rendering](<screenshot.png>)


**A 2D raycasting engine inspired by the classic game Doom, built from scratch.**

## Table of Contents

- [About](#about)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## About

Raycasting_doomlike is a project that implements a 2D raycasting engine, similar to the rendering technique used in the original Doom. This project aims to recreate the core visual effect of Doom's pseudo-3D environment using only 2D techniques. It's a great way to learn about raycasting algorithms, game development fundamentals, and low-level graphics programming. This project is a personal project, and is not meant to be a full game, but rather a demonstration of the raycasting technique. As developped from the video that inspired 
[this](https://www.youtube.com/watch?v=gYRrGTC7GtA) from 3DSage

## Features

*   **Raycasting Engine:** Implements the core raycasting algorithm to render a 3D-like environment from a 2D map.
*   **Wall Rendering:** Renders vertical walls based on ray intersections with the map.
*   **Textured Walls:** Supports textured walls to enhance the visual experience.
*   **Basic Movement:** Allows the player to move around the map using keyboard controls.
*   **Map Loading:** Loads map data from a simple text file format.
*   **Mini-map:** Displays a top-down view of the map.
* **Sprites:** Displays sprites on the map.

## Getting Started

Get started with the project by following these steps.

### Prerequisites

*   **C Compiler:** A C compiler (like GCC or Clang) is required to build the project.
*   **Make:** The `make` utility is used to automate the build process.
*   **CSFML:** The C wrapper of the SFML Library

### Installation

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/zachmae/Raycasting_doomlike
    cd Raycasting_doomlike
    ```
2.  **Compile the project:**
    ```bash
    make
    ```
3. **Run the project:**
    ```bash
    ./raycaster mapname.wolf
    ```

## Usage

*   **Movement:**
    *   `Space`: Start the game from the main menu.
    *   `Up Arrow`: Move forward.
    *   `Down Arrow`: Move backward.
    *   `Left Arrow`: Rotate left.
    *   `Right Arrow`: Rotate right.
    *   `P`: Pause the game and show the menu.
    *   `Escape`: Quit the game.
* **Map:**
    * The map is loaded from the `map.wolf` file.
    * The map is a grid of characters, where `1` represents a wall and `0` represents an empty space.
* **Sprites:**
    * Sprites are loaded from the sprite_manager.h file in the include folder
    * Sprites are defined by their position and their texture.

## Contributing

Contributions are welcome! If you'd like to contribute to the project, please follow these steps:

1.  Fork the repository.
2.  Create a new branch for your feature or bug fix.
3.  Make your changes and commit them.
4.  Push your changes to your fork.
5.  Submit a pull request to the main repository.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contact

*   **Zachmae** : zach.mlaw@gmail.com

---
