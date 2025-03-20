# Terramorphus

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

A tool developped in C to manipulate perspective and Topographic generation using Perlin Noise 

## Features

-   **2D Isometric Perspective:** Implements a 2D Isometric perspective to render a pseudo-3D environment.
-   **Perlin Noise:** Utilizes Perlin noise for procedural topographic generation.
-   **Perspective Manipulation:** Allows for dynamic adjustment of the viewing perspective.
-   **Topographic Generation:** Generates varied and complex terrain using Perlin noise.
-   **Map Navigation:** Enables movement and exploration within the generated map.
-   **Map Saving/Loading:** Provides functionality to save and load generated maps.
-   **Zoom:** Allows the user to zoom in and out of the map.
-   **Sprites:** Supports the rendering of sprites within the environment.
-   **UI:** Provides a user interface to change the topography and perspective.

## Getting Started

Get started with the project by following these steps.

### Prerequisites

*   **C Compiler:** A C compiler (like GCC or Clang) is required to build the project.
*   **Make:** The `make` utility is used to automate the build process.
*   **CSFML:** The C wrapper of the SFML Library

### Installation

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/zachmae/terramorphus
    cd Raycasting_doomlike
    ```
2.  **Compile the project:**
    ```bash
    make
    ```
3. **Run the project:**
    ```bash
    ./terramorphus
    ```

## Usage

*   **Movement:**
    *   `Space`: Generate a new map using Perlin Noise base algorithm
    *   `Up Arrow`: Move map Up.
    *   `Down Arrow`: Move map Down
    *   `Left Arrow`: move map left.
    *   `Right Arrow`: move map right.
    *   `S`: save a map in a save.legend file
    *   `L`: load a map from a save.legend file
    *   `Mouse Wheel`: zoom in and out the camera
    *   `UI on the left`: change the topography of the map and perspective
* **Sprites:**
    * Sprites are loaded from the tileset.png file in the assets folder


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
