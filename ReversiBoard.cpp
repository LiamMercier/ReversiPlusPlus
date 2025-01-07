#ifndef REVERSI_BOARD_CPP
#define REVERSI_BOARD_CPP

#include "ReversiBoard.h"

// Defined constants
#define BOARD_DIMENSION 8
#define BOARD_AREA 64


void ReversiBoard::print_board() const
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

void ReversiBoard::print_moves() const
{
	std::cout << "MOVES: ";
	for (int i = 0; i < num_moves; i++)
	{
		std::cout << +available_moves[i] << " ";
	}
	std::cout << "\n";
}

void ReversiBoard::print_active() const
{
	std::cout << "ACTIVE: ";
	for (int i = 0; i < tiles_count; i++)
	{
		std::cout << +active_tiles[i] << " ";
	}
}

std::uint8_t ReversiBoard::make_move(std::uint8_t selection)
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
	board[selection] = player;
	active_tiles[tiles_count] = selection;
	tiles_count++;

	// update other tiles
		
	// We should skip all this if we are not past turn 4
	if (current_turn < 4)
	{
		current_turn++;
		player = (player % 2) + 1;
		return 1;
	}
		
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

			// if this location has an opponent tile, take another step
			if (board[current_tile] == (player % 2) + 1)
			{
				continue;
			}

			// if this location has an ally tile, flip all tiles between this tile and selection.
			if (board[current_tile] == player)
			{
				while (current_tile != selection)
				{
					std::cout << "BACK STEP OF SIZE: " << +step << " TILE IS AT: " << +current_tile << "\n";
					current_tile -= step;
					board[current_tile] = player;
				}
				break;
			}

		}
	}

	current_turn++;
	player = (player % 2) + 1;
	return 0;
}

// The same as make_move but without checks for input.
//
// This can be used for faster computation assuming all
// inputs are from the available_moves array.
// Otherwise, errors may occur.
std::uint8_t ReversiBoard::make_move_unchecked(std::uint8_t selection)
{
	return 0;
}

// Find valid moves for the current board state.
//
// This function updates the class internal "available_moves"
// to hold the current moves.
//
// The values in available_moves may contain duplicates after this operation.
void ReversiBoard::compute_available_moves()
{
	num_moves = 0;

	// Check if past setup phase
	if (current_turn < 4)
	{
		// add all the tiles that are not occupied
		for (int i = 0; i < 4; i++)
		{
			uint8_t position = initial_moves[i];
			if (board[position] == 0)
			{
				available_moves[num_moves] = position;
				num_moves++;
			}

		}

		return;
	}

	// If turn >= 4 we should search tiles for potential moves
	//
	// Iterate over active_tiles and check if the tile is owned by the player
	// If so, search for a line of opponent tiles that ends in an empty space

	for (int i = 0; i < tiles_count; i++)
	{
		uint8_t position = active_tiles[i];

		// If not a player tile, skip to next one
		if (board[position] != player)
		{
			continue;
		}

		// Search each direction for opponent tile

		for (int i = 0; i < 8; i++)
		{
			// Retrieve the step value
			std::int8_t step = directions[i];
			std::uint8_t current_tile = position;

			// Set true if we found a valid line to save
			bool valid_flag = false;

			while (true)
			{
				// Take a step in the current direction
				current_tile += step;

				// If this location is out of bounds, stop searching
				if (current_tile >= BOARD_AREA)
				{
					break;
				}

				// If this location has an empty tile then this
				// Tile is a move if we have taken a step
				if (board[current_tile] == 0)
				{
					if (valid_flag)
					{
						// Add to list of moves
						available_moves[num_moves] = current_tile;
						num_moves++;
					}
					break;
				}

				// If this location has an opponent tile, take another step
				if (board[current_tile] == (3 - player))
				{
					// Unless we are on an edge
					if (current_tile % 8 == 0)
					{
						break;
					}

					if (current_tile % 8 == 7)
					{
						break;
					}

					valid_flag = true;
					continue;
				}

				// else, break
				break;

			}
		}
	}
}


	// board contains the current state of the reversi game
	std::uint8_t board[BOARD_AREA]{};
	std::uint8_t current_turn = 0;
	std::uint8_t player = 1;

	// active_tiles contains tiles currently in play
	std::uint8_t active_tiles[BOARD_AREA]{};
	std::uint8_t tiles_count = 0;

	// available_moves holds the valid moves for the current player
	// num_moves allows us to avoid clearing the whole array each time we search.
	std::uint8_t available_moves[BOARD_AREA];
	std::uint8_t num_moves = 0;

	// Static lookup table for first 4 moves
	//
	// The top left tile is (BOARD_DIMENSION/2) - 1 tiles down, (BOARD_DIMENSION/2)-1 tiles right
	// The top right tile is one to the right of that
	// The bottom left tile is BOARD_DIMENSION/2 tiles down, (BOARD_DIMENSION/2) - 1 tiles right
	// The bottom right tile is one to the right of that
	//
	// Simplified, if BOARD_DIMENSION is B
	//
	// Top Left = (B^2 - B)/2 - 1
	// Top Right = (B^2 - B)/2
	// Bottom Left = (B^2 + B)/2 - 1
	// Bottom Right = (B^2 + B)/2
	constexpr std::uint8_t ReversiBoard::initial_moves[4]{ (BOARD_DIMENSION * BOARD_DIMENSION - BOARD_DIMENSION) / 2 - 1, (BOARD_DIMENSION * BOARD_DIMENSION - BOARD_DIMENSION) / 2,
													(BOARD_DIMENSION * BOARD_DIMENSION + BOARD_DIMENSION) / 2 - 1, (BOARD_DIMENSION * BOARD_DIMENSION + BOARD_DIMENSION) / 2 };


	// Static lookup table for directions
	//
	// The first element is the direction for north-west, the rest are filled in clockwise.
	constexpr std::int8_t ReversiBoard::directions[8]{ -BOARD_DIMENSION - 1, -BOARD_DIMENSION, -BOARD_DIMENSION + 1,
												-1,                                                        1,
												 BOARD_DIMENSION - 1,  BOARD_DIMENSION,  BOARD_DIMENSION + 1 };

#endif
