#include "ReversiBoard.h"


int main()
{
	ReversiBoard game_board;

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(27);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(28);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(36);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(35);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	return 0;
}