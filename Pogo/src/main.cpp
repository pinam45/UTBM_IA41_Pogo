#include <iostream>
#include <ConsoleControl.h>
#include <ConsoleControlMenu.h>
#include <ConsoleControlUtility.h>
#include <Logic/PawnStack.hpp>
#include <Logic/Board.hpp>
#include <Logic/AIPlayer.hpp>

void PawnStackUseExample();

void BoardUseExample();

void AIPlayerUseExample ();

int main() {
	cc_clean();
	const char* choices[] = {
		"Human vs Human",
		"Human vs A.I.",
		"A.I. vs A.I.",
		"Options",
		"Exit"
	};
	cc_Menu menu;
	menu.choices = choices;
	menu.choicesNumber = 5;
	menu.currentChoice = 1;
	menu.choiceOnEscape = 4;
	menu.title = "Magic Pogo";
	const cc_MenuColors colors = {
		CYAN,
		BLACK,
		WHITE,
		BLACK,
		CYAN,
		BLACK
	};
	bool loop = true;
	while(loop) {
		cc_displayColorMenu(&menu, &colors);
		cc_setColors(BLACK, WHITE);
		switch(menu.currentChoice) {
			case 0:
				//TODO
				break;
			case 1:
				//TODO
				break;
			case 2:
				//TODO
				break;
			case 3:
				//TODO
				break;
			case 4:
				loop = false;
				break;
			default:
				break;
		}
	}
	return 0;
}

void PawnStackUseExample() {
	PawnStack16 player1Default{PLAYER1_DEFAULT_STACK};
	PawnStack16 player2Default{PLAYER2_DEFAULT_STACK};
	std::cout << "player1Default = " << player1Default << std::endl;
	std::cout << "player2Default = " << player2Default << std::endl;
	PawnStack16 a{0b00110101};
	std::cout << "a = " << a << std::endl;
	PawnStack16 b = a.pick(1);
	std::cout << "b = " << b << std::endl;
	std::cout << "a = " << a << std::endl;
	std::cout << "a.size() = " << a.size() << std::endl;
	std::cout << "b.size() = " << b.size() << std::endl;
	for(unsigned int i = 0; i < a.size(); ++i) {
		std::cout << "a[" << i << "] = " << a[i] << std::endl;
	}
	a.add(b);
	a.add(b);
	std::cout << "a = " << a << std::endl;
}

void BoardUseExample() {
	Board<PawnStack16> board;
	std::cout << "---" << std::endl;
	std::cout << "board[1][1]= " << board[1][1] << std::endl;
	std::cout << "board[1][2]= " << board[1][2] << std::endl;
	board[0][0] = PawnStack16{PLAYER1_DEFAULT_STACK};
	board[1][0] = PawnStack16{PLAYER1_DEFAULT_STACK};
	board[2][0] = PawnStack16{PLAYER1_DEFAULT_STACK};
	board[0][2] = PawnStack16{PLAYER2_DEFAULT_STACK};
	board[1][2] = PawnStack16{PLAYER2_DEFAULT_STACK};
	board[2][2] = PawnStack16{PLAYER2_DEFAULT_STACK};
	//board is default pogo board with player 1 at the top and player 2 at the bottom
	std::cout << "---" << std::endl;
	std::cout << "board[1][1]= " << board[1][1] << std::endl;
	std::cout << "board[1][2]= " << board[1][2] << std::endl;
	PawnsMove move{1,2,1,1,1};
	board.apply(move);
	std::cout << "---" << std::endl;
	std::cout << "board[1][1]= " << board[1][1] << std::endl;
	std::cout << "board[1][2]= " << board[1][2] << std::endl;
	std::cout << "board[1][2][1]= " << board[1][2][1] << std::endl;
}

void AIPlayerUseExample () {
	unsigned int depth = 5;
	AIPlayer AI (PLAYER1_PAWN,depth);
	Board<PawnStack16> board;
	board[0][0] = PawnStack16{PLAYER1_DEFAULT_STACK};
	board[1][0] = PawnStack16{PLAYER1_DEFAULT_STACK};
	board[2][0] = PawnStack16{PLAYER1_DEFAULT_STACK};
	board[0][2] = PawnStack16{PLAYER2_DEFAULT_STACK};
	board[1][2] = PawnStack16{PLAYER2_DEFAULT_STACK};
	board[2][2] = PawnStack16{PLAYER2_DEFAULT_STACK};
	PawnsMove choice = AI.chooseMove(board);
	std::cout  << "Chosen Move : " << choice.fromX << "," << choice.fromY <<" -> " << choice.toX << "," << choice.toY << " number : " << choice.pawnNumber << std::endl;
}
