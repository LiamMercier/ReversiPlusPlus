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

	void print_board() const;

	void print_moves() const;

	void print_active() const;

	std::uint8_t make_move(std::uint8_t selection);

	std::uint8_t make_move_unchecked(std::uint8_t selection);

	void compute_available_moves();

private:
	std::uint8_t board[BOARD_AREA]{};
	std::uint8_t current_turn;
	std::uint8_t player;
	std::uint8_t active_tiles[BOARD_AREA];
	std::uint8_t tiles_count;
	std::uint8_t available_moves[BOARD_AREA];
	std::uint8_t num_moves;

    static std::uint8_t initial_moves[4];
    static std::int8_t directions[8];
};

#endif
