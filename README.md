# Graphics Games Collection

This repository contains two interactive 3D games built with C++ and OpenGL/GLUT graphics library:

## 🎮 Games Overview

### 1. Space Invaders Game (Assignment_1.cpp)
A classic Space Invaders-style game where you control a spaceship to shoot down an enemy invader while avoiding enemy bullets.

### 2. 3D Soccer Game (Assignment2.cpp)
An interactive 3D soccer game where you control a player to kick a ball toward the goal by getting close to it, creating a realistic dribbling experience.


---

## 👾 Space Invaders Game - Assignment_1.cpp

### Features

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

### Space Invaders Controls

- **WASD** or **Arrow Keys** - Move player spaceship
- **Spacebar** - Shoot laser balls
- **ESC** - Quit game

### Space Invaders Building & Running

#### Requirements
- macOS with OpenGL support
- GLUT framework
- g++ compiler

#### Compile
```bash
g++ -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/GLUT.framework/Headers/ \
Assignment_1.cpp -framework OpenGL -framework GLUT -o Assignment_1
```

#### Run
```bash
./Assignment_1
```

---


## 🏆 3D Soccer Game - Assignment2.cpp

### Features

- **3D Graphics**: Full 3D rendering with lighting, textures, and depth
- **Player Controls**:
  - `f` - Move forward toward ball/goal
  - `b` - Move backward away from goal
  - `r`/`l` - Move left/right
- **Camera Controls**:
  - `w`/`s` - Camera up/down
  - `a`/`d` - Camera left/right
  - `q`/`e` - Camera forward/backward
  - Arrow keys - Camera rotation
  - `1`/`2`/`3` - Preset camera views
- **Realistic Ball Physics**:
  - Ball only moves when player gets very close (within 0.1 units)
  - Incremental kicking: ball moves 0.05 units per kick, then stops
  - Player must repeatedly approach to advance the ball
- **Game Elements**:
  - Soccer field with green ground
  - Goal net with posts and crossbar
  - Corner flags and banners
  - Trophy cup display
- **Goal Scoring**:
  - Ball must reach Z=0.0 to score
  - Celebration screen with "GOALLLLLLLLLL!" message
  - Goal counter display
  - Game exits after 2 seconds
- **Boundaries**: Player movement constrained within field limits

### Soccer Game Controls

#### Player Movement
- **`f`** - Move forward (toward ball/goal)
- **`b`** - Move backward (away from goal)
- **`r`** - Move left
- **`l`** - Move right

#### Camera Controls
- **`w`/`s`** - Camera up/down
- **`a`/`d`** - Camera left/right
- **`q`/`e`** - Camera forward/backward
- **Arrow Keys** - Rotate camera
- **`1`/`2`/`3`** - Preset views (corner, goal, side)

#### Other
- **ESC** - Quit game

### Soccer Gameplay

1. Use `f` to move your blue player toward the black soccer ball
2. Get very close to the ball (collision distance: 0.1 units)
3. The ball will automatically kick forward 0.05 units toward the goal
4. Repeat the process - approach, kick, approach, kick...
5. Continue until the ball reaches the goal at Z=0.0
6. Enjoy the celebration screen!

### Soccer Building & Running

#### Requirements
- macOS with OpenGL support
- GLUT framework
- clang++ compiler

#### Compile
```bash
clang++ -std=gnu++14 -DGL_SILENCE_DEPRECATION -g Assignment2.cpp -o Assignment2 -framework GLUT -framework OpenGL
```

#### Run
```bash
./Assignment2
```

---

## 🛠 Technical Details

### Common Requirements
- **Language**: C++ with OpenGL/GLUT
- **Platform**: macOS
- **Graphics**: OpenGL immediate mode rendering
- **Windowing**: GLUT for cross-platform window management

### Architecture
- **Soccer Game**: Custom Vector3f and Camera classes, distance-based collision detection
- **Space Invaders**: 2D game with health systems, power-ups, and AI enemy movement
- **Rendering**: Both use GLUT event-driven architecture with display callbacks

### File Structure
```
├── Assignment_1.cpp    # Space Invaders game
├── Assignment2.cpp     # 3D Soccer game
├── README.md          # This documentation
└── (compiled executables not included in repo)
```
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
