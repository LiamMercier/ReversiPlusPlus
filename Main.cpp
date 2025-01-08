#include "ReversiBoard.h"

enum class Flag : uint8_t
{
	None, Setup, Printing, TerminalColor
};

enum class Setups : uint8_t
{
	Classical, Standard
};

enum class Prints : uint8_t
{
	Plain, Color
};

void explain_options()
{
	std::cout <<"Usage\n";
	std::cout <<"  ./Reversi                             = Defaults\n";
	std::cout <<"  ./Reversi [flag] <flag_value>         = Run with flags\n";
	std::cout <<"\n";
	std::cout << "Options\n";
	std::cout << "  -h <value>                            = Display help\n";
	std::cout << "  -s <value>                            = Setup style (standard, classical)\n";
	std::cout << "  -p <value>                            = Printing style (plain, color)\n";
	std::cout << "  -c1 <value>                           = ANSII color (0-255) for player 1's valid moves\n";
	std::cout << "  -c2 <value>                           = ANSII color (0-255) for player 2's valid moves\n";
	std::cout << "Examples\n";
	std::cout << "  ./Reversi -s classical -p color       = Play with the classical opening and color printing\n";
}

// GLOBAL VARIABLES
//
// These variables are for color, and should not change across
// the lifetime of the program after set.
std::string TERMINAL_COLOR_P1 = "27";
std::string TERMINAL_COLOR_P2 = "196";

int main(int argc, char* argv[])
{
	Setups setup_type = Setups::Classical;
	Prints printing_type = Prints::Color;

	// Valid options start with "-" so we parse by looking for
	// an input starting with "-" to get the flag and then look for
	// the option in the next argv entry.
	bool flag_found = false;
	Flag previous_flag = Flag::None;

	for (int i = 1; i<argc; i++)
	{
		// Previous argument is a flag, deal with options
		// relating to the flag.
		if (flag_found)
		{
			std::string current_arg = argv[i];
			// Deal with different flags.
			switch (previous_flag)
			{
				case Flag::Setup:
					if (current_arg == "classical")
					{
						setup_type = Setups::Classical;
						break;
					}
					else if (current_arg == "standard")
					{
						setup_type = Setups::Standard;
						break;
					}
					std::cerr << "Invalid parameter for setup flag. Use -h to view options." << std::endl;
					return 2;
				case Flag::Printing:
					if (current_arg == "plain")
					{
						printing_type = Prints::Plain;
						break;
					}
					else if (current_arg == "color")
					{
						printing_type = Prints::Color;
						break;
					}
					std::cerr << "Invalid parameter for printing flag. Use -h to view options." << std::endl;
					return 2;
				case Flag::TerminalColor:
					// Cannot have more than 3 characters, otherwise too big to be valid.
					uint16_t color_input;
					if (current_arg.length() > 3)
					{
						std::cout<<"Invalid value for terminal color. Use -h to view options.";
						return 2;
					}

					// Test that the value is valid.
					//
					// First, see if it's an integer.
					for(uint8_t i = 0; i < current_arg.length() ; i++)
					{
						if (!isdigit(current_arg[i]))
						{
							std::cout<<"Invalid value for terminal color. Use -h to view options.";
							return 2;
						}
					}
					// Then see if it fits in the range.
					color_input = std::stoi(current_arg);

					if (color_input > UINT8_MAX)
					{
						std::cout<<"Invalid value for terminal color. Use -h to view options.";
						return 2;
					}

					// If all checks pass, change the terminal color.
					//
					// note: argv[i-1][2] is always going to exist, because it was
					// the previous flag variable with length 3.
					if (argv[i-1][2] == '1')
					{
						TERMINAL_COLOR_P1 = current_arg;
					}
					else
					{
						TERMINAL_COLOR_P2 = current_arg;
					}
					break;
				default:
					std::cerr << "Invalid flag. Use -h to view options." << std::endl;
					return 2;
			}
			// Reset the flag and string.
			previous_flag = Flag::None;
			flag_found = false;
		}

		// Deal with not having previously seen a flag.
		// (we are taking in a flag or exiting with a usage error)
		else
		{
			std::string current_arg = argv[i];

			// Check for improper usage.
			if(current_arg[0] != '-' || current_arg.length() < 2)
			{
				std::cerr << "Error in usage (No flag detected). Use -h to view options." << std::endl;
				// Invalid arguments.
				return 2;
			}

			// At this point, we have a flag argument.
			// Determine the type of flag and continue.
			switch(current_arg[1])
			{
				// Get help with running the program.
				case 'h':
					explain_options();
					return 0;
				// Setup options.
				case 's':
					previous_flag = Flag::Setup;
					flag_found = true;
					break;
				case 'p':
					previous_flag = Flag::Printing;
					flag_found = true;
					break;
				case 'c':
					// If not correct format then reject (-c1 or -c2).
					if (current_arg.length() != 3)
					{
						std::cerr << "Error in usage (Unknown flag detected). Use -h to view options." << std::endl;
						return 2;
					}
					previous_flag = Flag::TerminalColor;
					flag_found = true;
					break;
				default:
					std::cerr << "Error in usage (Unknown flag detected). Use -h to view options." << std::endl;
					return 2;
			}

			// Get the next argument.
			continue;
		}
	}

	ReversiBoard game_board;
	Score game_result;

	// default to color printing
	void (ReversiBoard::*print_func)() const = &ReversiBoard::color_print_board;

	// set printing to plain if flag is set
	if (printing_type == Prints::Plain)
	{
		print_func = &ReversiBoard::print_board;
	}

	// Default to classical reversi, otherwise do a standard opening.
	if (setup_type == Setups::Standard)
	{
		game_result = game_board.standard_setup_terminal(print_func);
	}
	else
	{
		game_result = game_board.classical_setup_terminal(print_func);
	}

	// Show results
	std::cout << "Score (Player1:Player2)\n";
	std::cout << +game_result.player1 << " : " << +game_result.player2 << "\n";

	return 0;
}
