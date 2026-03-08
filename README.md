# Pac-Man game made with c++ and raylib
I made this project in order to improve in c++ programming.
This is first and foremost a learning project made by me.
If you want to distribute this program, you need to comply with the license ( as seen in this repo).

## Technologies uses

+ C++ 23
+ Raylib
+ CMake
+ Git

## Features

This project features:

+ a default map (50 x 28 grid)
+ a score system ( to collect coins and display a win message)
+ player movement via both arrow and WASD keys
+ two enemy AIs that finds shortest path to the player (you) via [manhattan distance](https://en.wikipedia.org/wiki/Taxicab_geometry)
+ a *great* way to have fun


## Screenshots
![Gameplay Screenshot](/assets/pic1.png)
![Defeat Screen](/assets/pic2.png)

## Create your own map:
If you want to make your own map you need to make a txt file with exactly 1400 characters (It's a 50x28 grid)


X -> Player Starting Position

\# -> Wall

0 -> Coin

? -> Ghost starting position(s) There are 2 ghosts

Note that you do not need outer walls since the program treats the windows borders as walls.




## How to Run

### Prerequisites
- CMake 4.1 or higher
- C++23 compatible compiler  (This is required for std::expected)
- Git

### Build and Run (Release)
```bash
git clone https://github.com/scinca/pacman-cpp.git
cd pacman-cpp
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
./pacman_cpp
```

## Project Structure
    
```
src/
│
├── main.cpp # Application entry point
├── config.h # Shared configuration values (window size, tile size, etc.)
│
├── time/ # Simple deltaTime implementation for frame-independent movement
│
├── map/ # Map system
│ └── Map class handles:
│ - map loading from file or string
│ - tile queries ( coordinates, status , exploration )
│ - collision detection 
│
└── players/ # Base class shared by player and AI 
│
├── HumanPlayer/ # Handles player input and movement
│
└── EnemyAI/ # Enemy AI and pathfinding logic
```


**Note:** If raylib isn't installed it automatically downloaded and compiled. This takes a looong time.

## Disclosure of AI usage

This project was made by me. However I used Claude 4.5 Sonnet to help me with:

- designing the map ( writing 1400 '#' or '0' is insane)
- Making the cmake specifically the 'add_custom_command()' ( now removed)
- Some brainstorming about how to implement certain functionality ( but the code was written by me)
- questions about cpp ( like which function does this)
- debugging certain things where I got stuck.
- some of the math used to calculate certain things like the position of tiles
- the automatic raylib download 