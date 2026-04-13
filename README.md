# Space Invaders Game - OpenGL/GLUT

A classic Space Invaders-style game built with C++ and OpenGL/GLUT graphics library. The player controls a spaceship at the bottom of the screen and must shoot down an enemy invader cube while avoiding incoming enemy bullets.

## Features

- **Player Controls**: Move with WASD or Arrow Keys
- **Continuous Shooting**: Press Spacebar to fire green laser balls
- **Enemy AI**: Enemy cube moves left and right autonomously and fires red bullets at intervals
- **Collision Detection**: 
  - Hit detection between player bullets and enemy
  - Contact collision to prevent touching the enemy
  - Damage system for enemy bullets
- **Health System**: 
  - Player has 3 health points (displayed as green cubes)
  - Enemy has 20 health points (damage shown via health bar color)
  - Enemy health bar changes color: green (high) → yellow (medium) → red (low)
- **Power-Up Mechanics**:
  - Pink cube power-up appears randomly on the map
  - Lasts 5 seconds before disappearing
  - Respawns in a different location after 2.5-second delay
  - When collected, grants temporary invincibility
- **Game States**:
  - "Game Over" - displayed when player health reaches 0
  - "You Won" - displayed when enemy health reaches 0
  - Both appear on a black background with red text
- **Boundaries**: Player is confined within screen borders

## Controls

- **WASD** or **Arrow Keys** - Move player spaceship
- **Spacebar** - Shoot laser balls
- **ESC** - Quit game

## Building & Running

### Requirements
- macOS with OpenGL support
- GLUT framework
- g++ compiler

### Compile
```bash
g++ -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/GLUT.framework/Headers/ \
Assignment_1.cpp -framework OpenGL -framework GLUT -o Assignment_1
```

### Run
```bash
./Assignment_1
```

## Game Mechanics

### Scoring/Victory
- Reduce enemy health to 0 to win
- Avoid taking all 3 damage points or you lose
- Touch the pink power-up to gain temporary invincibility

### Enemy Behavior
- Moves side to side automatically
- Fires one red bullet every ~1.67 seconds from current position
- Each bullet travels down the screen independently
- Bullets reset position when they go off-screen

### Player Mechanics
- Spawn position: Center bottom of screen
- Can fire unlimited consecutive bullets
- Movement is smooth with continuous key tracking
- Confined to play area (±1.8 in X and Y coordinates)

## Code Structure

- **Global Variables**: Game state, positions, health counters, timers
- **Input Handling**: `keyDown()`, `keyUp()`, `specialKeyDown()`, `specialKeyUp()`
- **Game Logic**: `display()` - main game loop handling all updates and rendering
- **Rendering Functions**: `fire()`, `player()`, `Invader()`, `laser()`, `powerUp()`, etc.
- **Arrays**: 
  - `laserXArray[10]` / `laserYArray[10]` - player bullets
  - `fireXArray[4]` / `fireYArray[4]` - enemy bullets
  - Health bars and tracking arrays

## Key Features Implemented

- Array-based bullet system for unlimited consecutive shots
- Multiple simultaneous enemy bullets
- Collision detection system
- Power-up spawn and disappear timing
- Autonomous enemy movement
- Health bar visualization with color coding
- Game state management
- Text rendering for game over/win screens
