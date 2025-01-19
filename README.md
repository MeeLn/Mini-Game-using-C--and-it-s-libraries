# Mini-Game-using-C++and-it-s-libraries
# DashLeapster

## Description
**DashLeapster** is a 2D endless runner game developed in C++ using the SDL2 library. In this game, you control a box that must avoid red boxes while running infinitely in a factory. The goal is to survive as long as possible without getting boxed in by the red boxes. Players can input their names, compete for the highest score, and restart or quit the game after failing.

The game features dynamic mechanics like jumping and gravity manipulation, making it both challenging and fun to play.

---

## Gameplay Features
1. **Player Mechanics**:
   - **Jump**: Press the **Space** button to make the box jump.
   - **Gravity Flip**: Press the **Up Arrow** to flip gravity upside down for a short duration.
   - **Gravity Reset**:
     - Automatically resets after a certain time.
     - Press the **Down Arrow** to instantly reset gravity to normal.

2. **Health**:
   - The box starts with **2x health**, giving it a second chance before it gets boxed in.

3. **Score**:
   - The score increases as the player survives longer.
   - The leaderboard displays the highest score along with the player's name.

4. **Random Obstacles**:
   - Randomized no. of Red boxes appears at random intervals, ensuring no two runs are the same.

5. **Restart or Quit**:
   - After failing, players can choose to restart the game or quit.

6. **Player Name**:
   - Players can input their names to save their scores on the leaderboard.

---

## Controls
| Action                | Key                |
|-----------------------|--------------------|
| Jump                  | `Space`            |
| Flip Gravity          | `Up Arrow`         |
| Reset Gravity         | `Down Arrow`       |
| Restart Game          | `Play Again Button`|
| Quit Game             | `X button on top`  |

---

## How to Play
1. Launch the game and input your name.
2. Control the box to avoid red boxes using jumps and gravity manipulation.
3. Survive as long as possible to achieve a high score.
4. If the box gets boxed in, choose to restart or quit the game.

---

## Development Details
- **Game Name**: DashLeapster
- **Developer**: Milan Raut
- **Language**: C++
- **Library**: SDL2 and others
- **Mechanics**:
  - Infinite scrolling map.
  - Randomized no. of red box occurrences.
  - Time-based score increment.

---

## Installation and Running
1. Clone the repository:
2. Open the project using Visual Studio
3. Run the Code
[Note: SDL2\include path must be included addtitional include direcotries in project properties C/C++ section and SDL2\lib\x64 path must be included in additional libraries directories in linker section. SDL2 libraries is in my SDL2 repo, you can find it there.]
