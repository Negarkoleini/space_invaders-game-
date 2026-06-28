# 🚀 Arcade Space Shooter (Advanced C Console Engine)

A modular, high-performance 2D arcade shooter game built from scratch in pure C. This project showcases structured programming architecture, matrix-based environment rendering, dynamic enemy AI behaviors, and a persistent state machine for user session management.

---

## 🚀 Key Technical Features (Resume Highlights)

* **Dynamic AI Pathfinding & Decision Trees:** Enemies do not just move blindly. They feature a randomized decision matrix where there is a **70% probability** of tracking the player's exact X/Y coordinates and a **20% probability** of executing unpredictable evasion maneuvers, preventing static gameplay patterns.
* **Algorithmic Level Scaling:** Features mathematical scaling curves (`3 * pow(level, 0.5)`) to procedurally compute the enemy spawn threshold and stat amplifiers (HP and damage caps) as the player progresses through levels.
* **Entity-to-Entity Collision Detection:** Implements a localized bounding-box collision engine that computes real-time intersections between active projectile vectors (`player.tir[b]`) and active enemy position matrices.
* **Persistent User Authentication System:** Includes a file-based user management framework (`users.txt`) that hashes or maps state verification, handling registration, duplicate username checking, and secure password validation.
* **State Machine Menu Architecture:** Managed via an explicit page routing engine (`PAGE_LOGIN`, `PAGE_SELECTMAP`, `PAGE_MAPMENU`, `PAGE_GAME`) that cleanly separates state transitions and rendering loops.

---

## 🛠️ Architecture & Data Structures

The system architecture cleanly splits logic via structured objects:
* **`Position` Struct:** Standardized abstract coordinate representation `{int x; int y;}` across players, projectiles, and obstacles.
* **`Enemy` Struct:** Encapsulates localized entity variables like health pool (`hp`), attack ratings (`damage`), dynamic positioning data, and an active visibility flag to bound vector lookups.
* **Double-Buffered Terminal Optimization:** Utilizes VT100 Escape Sequences (`\x1b[33m`, etc.) alongside `SetConsoleMode` virtual terminal processing to bypass traditional screen-clearing lag for seamless graphic redraws.

---

## 📁 Modular File Structure

* `main.c`: Entry point initializing the console core configuration and loading the overarching menu router.
* `game.c` / `game.h`: Coordinates the core execution loop, dynamic viewport refreshes, and asynchronous input mapping.
* `enemy.c` / `enemy.h`: Orchestrates object pooling algorithms for enemy instantiation, behavior patterns, and projectile intersections.
* `map.c` / `map.h`: Manages UTF-16 console mode transitions (`_O_U16TEXT`) and procedurally translates matrix arrays into geometric symbols (`●`, `■`, `█`).
* `menu1.c` / `menu1.h`: Implements the user directory logic, console login views, and custom map selection trees.

---

## 🕹️ Controls & Mechanics

* **Movement:** `W` (Up), `S` (Down), `A` (Left), `D` (Right)
* **Fire Projectile:** `SPACEBAR`

> **Gameplay Goal:** Move across the battle grid, fire lasers (`|`) to eliminate waves of spawning rogue entities (`■`), monitor your active health points (HP bar scaling dynamically), and advance through escalating stages.

---

## 🔨 How to Build and Run (Windows Environment)

The game relies on Windows console API hooks (`<windows.h>`, `<io.h>`) for handling non-blocking input states and customized stdout visual layers.

### Compilation via GCC
```bash
gcc main.c game.c enemy.c map.c menu1.c -o SpaceShooter.exe -lm
