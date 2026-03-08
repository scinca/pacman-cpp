# Pac-Man game made with c++ and raylib
I made this project in order to improve in c++ programming.
It is very basic at the moment. I might add some assets like sounds or proper characters later.
This is first and foremost a learning project made by me. This project is not meant to be distributed. If you want to do that anyways you need to comply with the license ( as seen in this repo).


## Features

This project Features

+ a default map
+ a score system ( to collect coins and display a win message)
+ player movement
+ a simple enemy ai that finds shortest path to the player (you) via [manhattan distance](https://en.wikipedia.org/wiki/Taxicab_geometry)


## Create your own map:
If you want to make your own map you need to make a txt file with exactly 1400 characters (It's a 50x28 grid)



X -> Player Starting Position

\# -> Wall

0 -> Coin

? -> Ghost starting position(s) There are 2 ghosts

Note that you do not need outer walls since the program treats the windows borders as walls.


## Disclosure of AI usage

This project was made by me. However I used Claude 3.5 Sonnet to help me with:

- Making the cmake specifically the 'add_custom_command()' ( now removed)
- Some brainstorming about how to implement certain functionality ( but the code was written by me)
- questions about cpp ( like which function does this)
-  debugging certain things where I got stuck.