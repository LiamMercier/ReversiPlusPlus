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

	void print_array() const
	{
		for (int i = 0; i <= 8; i++)
		{
			for (int j = 0; j <= 8; j++)
			{
				std::cout << +board[i * BOARD_DIMENSION + j] << " ";
			}
			std::cout << "\n";

		}
	}







private:

	// board contains the current state of the reversi game
	std::uint8_t board[BOARD_AREA]{};

	// occupied tiles is a list of tiles currently in play
	std::uint8_t active_tiles[BOARD_AREA]{};
	std::uint8_t tiles_count = 0;

	std::uint8_t current_turn = 0;


};

















#endif