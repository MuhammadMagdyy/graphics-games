# 3D Soccer Game - OpenGL/GLUT

An interactive 3D soccer game built with C++ and OpenGL/GLUT graphics library. Control a player to kick a soccer ball toward the goal by getting close to the ball, creating a realistic dribbling experience.

## Features

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

## Controls

### Player Movement
- **`f`** - Move forward (toward ball/goal)
- **`b`** - Move backward (away from goal)
- **`r`** - Move left
- **`l`** - Move right

### Camera Controls
- **`w`/`s`** - Camera up/down
- **`a`/`d`** - Camera left/right
- **`q`/`e`** - Camera forward/backward
- **Arrow Keys** - Rotate camera
- **`1`/`2`/`3`** - Preset views (corner, goal, side)

### Other
- **ESC** - Quit game

## Gameplay

1. Use `f` to move your blue player toward the black soccer ball
2. Get very close to the ball (collision distance: 0.1 units)
3. The ball will automatically kick forward 0.05 units toward the goal
4. Repeat the process - approach, kick, approach, kick...
5. Continue until the ball reaches the goal at Z=0.0
6. Enjoy the celebration screen!

## Building & Running

### Requirements
- macOS with OpenGL support
- GLUT framework
- clang++ compiler

### Compile
```bash
clang++ -std=gnu++14 -DGL_SILENCE_DEPRECATION -g Assignment2.cpp -o Assignment2 -framework GLUT -framework OpenGL
```

### Run
```bash
./Assignment2
```

## Technical Details

- **Language**: C++ with OpenGL/GLUT
- **Graphics**: 3D perspective projection, lighting, materials
- **Collision Detection**: Distance-based Euclidean calculation
- **Rendering**: Single buffer mode with glFlush()
- **Architecture**: Custom Vector3f and Camera classes
- **Game Loop**: GLUT event-driven with display callbacks
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
