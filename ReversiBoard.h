#ifndef REVERSI_BOARD_H
#define REVERSI_BOARD_H

// Included headers
#include <iostream>
#include <cstdint>
#include <limits>

// Defined constants
#define BOARD_DIMENSION 8
#define BOARD_AREA 64

struct Score
{
	uint8_t player1 = 0;
	uint8_t player2 = 0;
};

class ReversiBoard
{
public:

	void print_board() const;

	void print_moves() const;

	void print_active() const;

	std::uint8_t make_move(std::uint8_t selection);

	std::uint8_t make_move_unchecked(std::uint8_t selection);

	void compute_available_moves();

	std::uint8_t number_of_moves() const;

	Score score_game() const;

	Score standard_setup_terminal();

	Score classical_setup_terminal();

private:
	std::uint8_t board[BOARD_AREA]{};
	std::uint8_t current_turn = 0;
	std::uint8_t player = 1;
	std::uint8_t active_tiles[BOARD_AREA]{};
	std::uint8_t tiles_count = 0;
	std::uint8_t available_moves[BOARD_AREA]{};
	std::uint8_t num_moves = 0;

    static const std::uint8_t initial_moves[4];
    static const std::int8_t directions[8];
};

#endif
