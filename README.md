# Brick Breaker: OpenGL 2D Physics Engine

A custom 2D arcade physics engine built entirely in C++ utilizing the legacy OpenGL Utility Toolkit (GLUT). This project demonstrates foundational concepts in object-oriented system architecture, manual memory management, and spatial rendering pipelines.

**Core Technical Features**
*   **Custom Physics & Collision:** Implements precise bounding-box collision detection and dynamic vector reflection. Ball trajectory algorithms dynamically calculate bounce angles based on the exact impact coordinate along the paddle's width.
*   **Hierarchical OOP Architecture:** Utilizes deep class inheritance (Coordinates -> Brick/Ball/Paddle) and pointer-based dynamic memory allocation for entity management across multiple game states.
*   **Matrix Projections:** Directly manipulates OpenGL projection matrices (`glOrtho`, `glMatrixMode`) for raw coordinate mapping and frame rendering.
*   **State Management:** Features multi-level progression grids, dynamic power-up spawn logic (modifying entity attributes at runtime), and persistent I/O stream scoring.

**Tech Stack**
*   **Language:** C++ 
*   **Graphics API:** OpenGL / GLUT
*   **Build System:** Make

**Installation & Compilation**

This project utilizes `make` and requires standard OpenGL, GLUT, and FreeImage libraries. A shell script is provided for rapid dependency installation on Linux/WSL environments.

**1. Install Dependencies**
Execute the included shell script to install required graphics libraries:
```bash
chmod +x install-libraries.sh
./install-libraries.shcls