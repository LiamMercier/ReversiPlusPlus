#ifndef REVERSI_BOARD_H
#define REVERSI_BOARD_H

// Included headers
#include <iostream>
#include <cstdint>

// Defined constants
#define BOARD_DIMENSION 8
#define BOARD_AREA 64





class ReversiBoard
{

public:

	void print_board() const
	{
		for (int i = 0; i < BOARD_DIMENSION; i++)
		{
			for (int j = 0; j < BOARD_DIMENSION; j++)
			{
				std::cout << +board[i * BOARD_DIMENSION + j] << " ";
			}
			std::cout << "\n";

		}
	}

	void print_moves() const
	{
		std::cout << "MOVES: ";
		for (int i = 0; i < num_moves; i++)
		{
			std::cout << +available_moves[i] << " ";
		}
		std::cout << "\n";

	}

	void print_active() const 
	{
		std::cout << "ACTIVE: ";
		for (int i = 0; i < tiles_count; i++) 
		{
			std::cout << +active_tiles[i] << " ";
		}
	}

	std::uint8_t make_move(std::uint8_t selection)
	{
		// Input validation

		// Check for array bounds
		if (selection >= BOARD_AREA)
		{
			// do nothing, this is an invalid move
			return 1;
		}
		// Check for empty tile
		if (board[selection] != 0)
		{
			// do nothing, this is an occupied tile
			return 1;
		}
		// Check for valid move
		bool valid_move = false;
		for (int j = 0; j < num_moves; j++) 
		{
			if (available_moves[j] == selection) 
			{
				valid_move = true;
				break;
			}
		}
		if (!valid_move) 
		{
			return 1;
		}

		// place tile and add it to the pool of tiles to search when finding moves
		board[selection] = (current_turn % 2) + 1;
		active_tiles[tiles_count] = selection;
		tiles_count++;

		// update other tiles
		// 
		// To flip tiles, we must search in all 8 directions.

		for (int i = 0; i < 8; i++)
		{
			// for this direction, retrieve the step value to reduce memory access
			std::int8_t step = directions[i];
			std::uint8_t current_tile = selection;

			while (true)
			{
				// take a step in the current direction
				current_tile += step;

				std::cout << "FOREWARD STEP OF SIZE: " << +step <<  " TILE IS AT : " << +current_tile << "\n";

				// if this location is out of bounds, stop searching
				if (current_tile >= BOARD_AREA) 
				{
					break;
				}

				// if this location has an empty tile, there is no flipping to be done
				if (board[current_tile] == 0)
				{
					break;
				}

				// if this location has an enemy tile, take another step
				if (board[current_tile] == (2 - current_turn % 2))
				{
					continue;
				}

				// if this location has an ally tile, flip all tiles between this tile and selection.
				if (board[current_tile] == (current_turn % 2) + 1)
				{
					while (current_tile != selection) 
					{
						std::cout << "BACK STEP OF SIZE: " << +step << " TILE IS AT: " << +current_tile << "\n";
						current_tile -= step;
						board[current_tile] = (current_turn % 2) + 1;
					}
					break;
				}

			}
		}

		current_turn++;

	}

	// The same as make_move but without checks for input.
	//
	// This can be used for faster computation assuming all
	// inputs are from the available_moves array. Otherwise, errors
	// may occur.
	std::uint8_t make_move_unchecked(int selection)
	{

	}

	void compute_available_moves() 
	{
		num_moves = 0;

		// Check if past setup phase
		if (current_turn < 4)
		{
			// add all the tiles that are not occupied
			for (int i = 0; i < 4; i++)
			{
				if (board[initial_moves[i]] == 0) 
				{
					available_moves[num_moves] = initial_moves[i];
					num_moves++;
				}

			}
		}

		// Otherwise, we should search tiles for potential moves

	}


private:

	// board contains the current state of the reversi game
	std::uint8_t board[BOARD_AREA]{};
	std::uint8_t current_turn = 0;

	// occupied tiles is a list of tiles currently in play
	std::uint8_t active_tiles[BOARD_AREA]{};
	std::uint8_t tiles_count = 0;

	// this array holds the valid moves for the current player
	// the array should be wiped (set to BOARD_AREA).
	std::uint8_t available_moves[BOARD_AREA];
	std::uint8_t num_moves = 0;

	// static lookup table for first 4 moves
	//
	// the top left tile is (BOARD_DIMENSION/2) - 1 tiles down, (BOARD_DIMENSION/2)-1 tiles right
	// the top right tile is one to the right of that
	// the bottom left tile is BOARD_DIMENSION/2 tiles down, (BOARD_DIMENSION/2) - 1 tiles right
	// the bottom right tile is one to the right of that
	//
	// simplified, if BOARD_DIMENSION is B
	//
	// TopLeft = (B^2 - B)/2 - 1
	// TopRight = (B^2 - B)/2
	// BottomLeft = (B^2 + B)/2 - 1
	// BottomRight = (B^2 + B)/2
	static constexpr std::uint8_t initial_moves[4]{ (BOARD_DIMENSION * BOARD_DIMENSION - BOARD_DIMENSION) / 2 - 1, (BOARD_DIMENSION * BOARD_DIMENSION - BOARD_DIMENSION) / 2,
													(BOARD_DIMENSION * BOARD_DIMENSION + BOARD_DIMENSION) / 2 - 1, (BOARD_DIMENSION * BOARD_DIMENSION + BOARD_DIMENSION) / 2 };


	// static lookup table for directions
	//
	// Moving up results in a change of -BOARD_DIMENSION to the current tile value, down results in +BOARD_DIMENSION, 
	// left results in -1, right results in +1, thus, we can compute each direction easily
	static constexpr std::int8_t directions[8]{ -BOARD_DIMENSION - 1, -BOARD_DIMENSION, -BOARD_DIMENSION + 1,
												-1,															1,
												BOARD_DIMENSION - 1, BOARD_DIMENSION, BOARD_DIMENSION + 1 };

};

















#endif