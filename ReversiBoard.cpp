#ifndef REVERSI_BOARD_CPP
#define REVERSI_BOARD_CPP

#include "ReversiBoard.h"

// Defined constants.
#define BOARD_DIMENSION 8
#define BOARD_AREA 64

extern std::string TERMINAL_COLOR_P1;
extern std::string TERMINAL_COLOR_P2;

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

void ReversiBoard::color_print_board() const
{
	for (int i = 0; i < BOARD_DIMENSION; i++)
	{
		for (int j = 0; j < BOARD_DIMENSION; j++)
		{
			uint8_t current = i * BOARD_DIMENSION + j;
			bool valid_move = is_valid_move(current);

			if (valid_move)
			{
				// Print the text with color.
				std::string control_characters;
				control_characters.reserve(15);

				control_characters.append("\033[48;5;");
				if (player == 1)
				{
					control_characters.append(TERMINAL_COLOR_P1);
				}
				else
				{
					control_characters.append(TERMINAL_COLOR_P2);
				}
				control_characters.append("m");

				std::cout << control_characters << +board[current] << "\033[0m ";
				continue;
			}

			// Print the text normally.
			std::cout << +board[current] << " ";

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
	// Input validation.
		
	// Check for array bounds.
	if (selection >= BOARD_AREA)
	{
		// Do nothing, this is an invalid move.
		return 1;
	}
	// Check for empty tile.
	if (board[selection] != 0)
	{
		// Do nothing, this is an occupied tile.
		return 1;
	}
	// Check for valid move.
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

	// Handle the move and return the result.

	return make_move_unchecked(selection);
}

// The same as make_move but without checks for input.
//
// This can be used for faster computation assuming all
// inputs are from the available_moves array.
// Otherwise, errors may occur.
std::uint8_t ReversiBoard::make_move_unchecked(std::uint8_t selection)
{
	// Place tile and add it to the pool of tiles to search when finding moves.
	board[selection] = player;
	active_tiles[tiles_count] = selection;
	tiles_count++;

	// Update other tiles.

	// We should skip all this if we are not past turn 4.
	if (current_turn < 4)
	{
		current_turn++;
		player = (player % 2) + 1;
		return 0;
	}

	// To flip tiles, we must search in all 8 directions.
	for (int i = 0; i < 8; i++)
	{
		// For this direction, retrieve the step value to reduce memory access.
		std::int8_t step = directions[i];
		std::uint8_t current_tile = selection;

		while (true)
		{
			// We need to ensure we don't move more than
			// one column at a time, because this would be going
			// out of bounds.
			uint8_t row_prev = current_tile % 8;

			// Take a step in the current direction.
			current_tile += step;

			uint8_t row = current_tile % 8;

			// If step would lead us outside the grid, break
			//
			// Here is an example if you are not convinced that this works.
			//
			// N is the current location, X is N + step (north west)
			//
			// 0 0 0 0 0 0 0 0
			// 0 0 0 0 0 0 0 0
			// X 0 0 0 0 0 0 0
			// 0 0 0 0 0 0 0 N
			// 0 0 0 0 0 0 0 0
			// 0 0 0 0 0 0 0 0
			// 0 0 0 0 0 0 0 0
			// 0 0 0 0 0 0 0 0
			//
			// Then:
			// N % 8 = 7
			// X % 8 = 0
			//
			// Thus we detect the collision. You can do this for any
			// step choice (except 8,-8 which are covered after this).

			if (row - row_prev > 1 || row_prev - row > 1 )
			{
				break;
			}

			// std::cout << "FOREWARD STEP OF SIZE: " << +step <<  " TILE IS AT : " << +current_tile << "\n";

			// If this location is out of bounds, stop searching.
			if (current_tile >= BOARD_AREA)
			{
				break;
			}

			// If this location has an empty tile, there is no flipping to be done.
			if (board[current_tile] == 0)
			{
				break;
			}

			// If this location has an opponent tile, take another step.
			if (board[current_tile] == (player % 2) + 1)
			{
				continue;
			}

			// If this location has an ally tile, flip all tiles between this tile and selection.
			if (board[current_tile] == player)
			{
				while (current_tile != selection)
				{
					//std::cout << "BACK STEP OF SIZE: " << +step << " TILE IS AT: " << +current_tile << "\n";
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

// Find valid moves for the current board state.
//
// This function updates the class internal "available_moves"
// to hold the current moves.
//
// The values in available_moves may contain duplicates after this operation.
void ReversiBoard::compute_available_moves()
{
	num_moves = 0;

	// Check if past setup phase.
	if (current_turn < 4)
	{
		// Add all the tiles that are not occupied.
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

	// If turn >= 4 we should search tiles for potential moves.
	//
	// Iterate over active_tiles and check if the tile is owned by the player
	// If so, search for a line of opponent tiles that ends in an empty space.

	for (int i = 0; i < tiles_count; i++)
	{
		uint8_t position = active_tiles[i];

		// If not a player tile, skip to next one.
		if (board[position] != player)
		{
			continue;
		}

		// Search each direction for opponent tile.

		for (int i = 0; i < 8; i++)
		{
			// Retrieve the step value.
			std::int8_t step = directions[i];
			std::uint8_t current_tile = position;

			// Set true if we found a valid line to save.
			bool valid_flag = false;

			while (true)
			{
				// We need to ensure we don't move more than
				// one column at a time, because this would be going
				// out of bounds.
				uint8_t row_prev = current_tile % 8;

				// Take a step in the current direction.
				current_tile += step;

				uint8_t row = current_tile % 8;

				// If step would lead us outside the grid, break
				if (row - row_prev > 1 || row_prev - row > 1 )
				{
					break;
				}

				// If this location is out of bounds, stop searching.
				if (current_tile >= BOARD_AREA)
				{
					break;
				}

				// If this location has an empty tile then this
				// tile is a move if we have taken a step.
				if (board[current_tile] == 0)
				{
					if (valid_flag)
					{
						// Add to list of moves.
						available_moves[num_moves] = current_tile;
						num_moves++;
					}
					break;
				}

				// If this location has an opponent tile, take another step.
				if (board[current_tile] == (3 - player))
				{
					// Unless we are on an edge.
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

				break;

			}
		}
	}
}

// Simple function to see if a move is in the valid moves list.
bool ReversiBoard::is_valid_move(std::uint8_t selection) const
{
	for (int j = 0; j < num_moves; j++)
	{
		if (available_moves[j] == selection)
		{
			return true;
		}
	}
	return false;
}


// Used to get the number of moves. Should not be called before
// moves are found using compute_available_moves.
std::uint8_t ReversiBoard::number_of_moves() const
{
	return num_moves;
}

// Score the game by counting how many tiles each
// player has placed when the game ends.
Score ReversiBoard::score_game() const
{
	Score final_score;
	for (int i = 0; i < BOARD_AREA; i++)
	{
		if (board[i] == 1)
		{
			final_score.player1 += 1;
			continue;
		}
		if (board[i] == 2)
		{
			final_score.player2 += 1;
			continue;
		}
	}
	return final_score;
}

// Start a reversi game on this board with a standard opening.
// The peices will be placed in an alternating fashion.
//
// This setup uses the standard output and input.
Score ReversiBoard::standard_setup_terminal(void (ReversiBoard::*printing_function)() const)
{
	// Setup the initial game board.
	make_move_unchecked(28);
	make_move_unchecked(27);
	make_move_unchecked(35);
	make_move_unchecked(36);

	Score game_result = classical_setup_terminal(printing_function);

	return game_result;
}

// Start a reversi game on this board with the classical opening.
// The first 4 moves are not predetermined.
//
// This setup uses the standard output and input.
Score ReversiBoard::classical_setup_terminal(void (ReversiBoard::*printing_function)() const)
{
	// Each turn we need to:
	// - Update available moves
	// - Check termination conditions
	// - Print the board to the screen
	// - List the moves available
	// - Get user input
	// - Make the move
	while (true)
	{
		compute_available_moves();

		// Terminate when no more moves can occur
		// for the current player.
		//
		// Reversi does not implement passes.
		if (num_moves == 0)
		{
			break;
		}

		(this->*printing_function)();
		print_moves();

		// Get input.
		while (true)
		{
			int move;

			std::cout << "Move for player " << +player << ": ";
			std::cin >> move;

			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Input is invalid" << std::endl;
			}

			// If input is good, proceed.

			std::uint8_t valid = make_move(move);

			// If move was good, exit and finish turn.
			if (valid == 0)
			{
				break;
			}
			else
			{
				std::cout << "Invalid move: " << move << std::endl;
			}
		}
	}

	(this->*printing_function)();
	Score game_result = score_game();

	return game_result;
}

// Wipe the entire board and reset all variables.
void ReversiBoard::reset_board()
{
	// Reset the entire board area.
	for(int i = 0; i<BOARD_AREA; i++)
	{
		board[i] = 0;
	}

	current_turn = 0;
	player = 1;

	// Both of the other arrays don't need to be wiped since
	// we are using counters to avoid needing to operate on them.
	tiles_count = 0;
	num_moves = 0;
}


// Static lookup table for first 4 moves.
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

// Static lookup table for directions.
//
// The first element is the direction for north-west, the rest are filled in clockwise.
constexpr std::int8_t ReversiBoard::directions[8]{ -BOARD_DIMENSION - 1, -BOARD_DIMENSION, -BOARD_DIMENSION + 1,
												-1,                                                        1,
												 BOARD_DIMENSION - 1,  BOARD_DIMENSION,  BOARD_DIMENSION + 1 };

#endif
