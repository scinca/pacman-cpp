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

? -> Ghost starting position(s) There are 3 ghosts on the default map. There can be a maximum of 4 ghosts.

Note that you do not need outer walls since the program treats the windows borders as walls.


### Map Rules so an LLM can generate the map better
#### Map File Format

The map must be stored in a .txt file representing a 50×28 grid.

Format rules:
- The file must have 1400 characters in it ( excluding newlines etc)
- Do not include any extra spaces.
- Line breaks do not count as grid characters.
- \n and \r characters will be erased by the program.

Allowed characters:

X  -> Player starting position (exactly one required)
#  -> Wall
0  -> Coin
?  -> Ghost starting position


Ghost rules:
- Minimum: 0
- Maximum: 4

Notes:
- Outer walls are not required because the window borders are treated as walls by the program.
-  After generating the map, verify that the total number of characters (excluding line breaks) is exactly 1400.

## How to Run

### Prerequisites
- CMake 4.1 or higher
- C++23 compatible compiler  (This is required for std::expected)
- git

### Build and Run (Release)
```bash
git clone https://github.com/scinca/pacman-cpp.git
cd pacman-cpp
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
./pacman_cpp
```

**Note:** If raylib isn't installed it automatically downloaded and compiled. This takes a looong time.

## Disclosure of AI usage

This project was made by me. However, I used Claude 4.5 Sonnet in learning mode to help me with:

- designing the initial map ( writing 1400 '#' or '0' is insane)
- Making some parts of the cmake
- Some brainstorming about how to implement certain functionality ( but the code was written by me)
- questions about cpp ( like which function does this)
- debugging certain things where I got stuck.
- some of the math used to calculate certain things like the position of tiles
