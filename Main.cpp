#include "ReversiBoard.h"


int main()
{
	ReversiBoard game_board;

	Score game_result = game_board.classical_setup_terminal();

	std::cout << +game_result.player1 << ":" << +game_result.player2 << "\n";

	return 0;

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

	game_board.make_move(29);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(19);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(10);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(11);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(34);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(9);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(3);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(12);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(1);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(26);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(8);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(42);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(25);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(43);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(49);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(50);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(58);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(22);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(15);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(30);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(31);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(51);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(13);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(37);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(59);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(21);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(45);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(14);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	game_board.make_move(7);

	game_board.print_board();
	game_board.compute_available_moves();
	game_board.print_moves();

	Score result = game_board.score_game();

	std::cout << +result.player1 << ":" << +result.player2 << "\n";

	return 0;
}
