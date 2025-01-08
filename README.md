# ReversiPlusPlus

A simple implementation of the game Reversi in C++ with the goal of being fast and portable to other interfaces.

This project is licensed under the Apache 2.0 license. See LICENSE for more information.

## Compiling

Simply go to the build directory and call CMake.

`cd builds`

`cmake .. && cmake --build .`

It is assumed that the standard library is available for compilation.

## Options

To run with default parameters simply type

`./Reversi`

To run with parameters use the format

`./Reversi [flag] <flag_value>`

For a full list of options see

`./Reversi -h`

The most relevant option is the setup option `-s` which changes how the game starts. The choices are classical (default) and standard.

- Classical setup: each player starts by picking a move in the center four squares until they are filled.
- Standard setup: the middle 4 tiles are filled in an alternating pattern.

## Playing

- Each valid move is displayed to the console at the start of a new turn. The tiles are numbered 0 through 63 going left to right, top to bottom.
- Players pick an empty tile (by entering a valid tile number) that forms a line (horizontal, vertical, diagonal) with the opponent tiles and one of their own tiles. This line may not have any empty tiles in between.
- The game terminates when one player is unable to move. In Reversi, there are no passes.
- The final score for each player is the number of tiles owned by the player at the end of the game.

## Including this project in other projects

The main.cpp file is simple code to get user input from the console and set different flags. These flags and input methods are not included in the class to allow for different design decisions (for example, working over a network). Other functions in the class are provided to make it possible to include the core game outside of the main.cpp interface, such as with a GUI application or website frontend. It is advised to only use the ReversiBoard.cpp and ReversiBoard.h code in this case, as the main.cpp interface is bare bones and not useful for these applications outside of testing functionality.

If you are working with a known dataset of games, calls to make_move_unchecked will work faster with the same result as long as the moves are known to be valid beforehand.

Finally, compute_available_moves will find all valid moves, but duplicate detection is not implemented (unnecessary performance cost). Therefore, the array of available moves may often contain duplicates when printed to the screen. If needed, do duplicate detection on the array before using the values.
