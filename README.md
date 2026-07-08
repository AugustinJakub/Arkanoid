# Arkanoid — Custom 2D Game

**Arkanoid** is a classic 2D arcade game I wrote in C++ using the SFML library to handle the window, graphics, and audio. The main goal of this project was to practice Object-Oriented Programming, polymorphism and implement my own collision detection system from scratch.

## Features & Architecture

The project is split into modular components to keep the code clean and structured:

* **Game Loop:** Manages real-time state updates, frame rendering, and smooth gameplay.
* **Physics & Collisions:** I wrote a custom Axis-Aligned Bounding Box (AABB) algorithm to handle precise reflections between the ball, the paddle, and the brick grid.
* **Game Logic & UI:** Includes a functional main menu, a player lives system, score tracking, and persistent data storage.


<img width="950" height="540" alt="Screenshot 2026-07-02 121851" src="https://github.com/user-attachments/assets/d5f6aaa9-06b2-4d9a-b036-3b30c201c648" />


## Tech Stack

* **Language:** C++ (classes, encapsulation, resource management).
* **Library:** SFML (Graphics, Window, Audio modules).

## Key Systems

* **Movement Mechanics:** Ball and paddle movement scales with delta time, ensuring the game runs at the same speed regardless of the computer's frame rate.
* **Grid Generation:** Procedural brick layout with different point values assigned to different brick types.
* **Leaderboard Persistence:** Player high scores are directly saved to and read from a local text file (`leaderboard.txt`).

## How to Run

1. Open the `Arkanoid.sln` solution file in Visual Studio.
2. Make sure the build configuration is set to x64.
3. Hit run - the SFML binaries are included in the project folder, so it should compile and run out of the box.
