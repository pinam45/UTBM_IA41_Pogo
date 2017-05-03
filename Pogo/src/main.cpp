#include <iostream>
#include <ConsoleControl.h>
#include <ConsoleControlUI.h>
#include <ConsoleControlUtility.h>
#include <Logic/PawnStack.hpp>
#include <Logic/Board.hpp>
#include <Logic/AIPlayer.hpp>
#include <UI/ConsoleUI.hpp>
#include <Logic/GameManager.hpp>
#include <Logic/HumanPlayer.hpp>

#define BOARD_WIDTH 3
#define BOARD_HEIGHT 3
using PawnStackType = PawnStack16;

static const cc_MenuColors menuColors = {
	BLACK,
	CYAN,
	BLACK,
	WHITE,
	BLACK,
	CYAN,
	BLACK
};

static const cc_MessageColors messageColors = {
	BLACK,
	CYAN,
	BLACK,
	WHITE,
	BLACK,
	WHITE,
	BLACK,
	CYAN,
	BLACK
};

unsigned int depthChoice(unsigned int number);

bool turnChoice();

bool checkExit();

int main() {
	const char* choices[] = {
		"Human vs Human",
		"Human vs A.I.",
		"A.I. vs A.I.",
		"Options",
		"Exit"
	};
	cc_Menu mainMenu;
	mainMenu.choices = choices;
	mainMenu.choicesNumber = 5;
	mainMenu.currentChoice = 0;
	mainMenu.choiceOnEscape = 4;
	mainMenu.title = "Magic Pogo";
	bool loop = true;
	while(loop) {
		ConsoleUI<PawnStackType, BOARD_WIDTH, BOARD_HEIGHT> ui;
		GameManager<PawnStackType, BOARD_WIDTH, BOARD_HEIGHT> manager;

		cc_displayColorMenu(&mainMenu, &menuColors);
		cc_setColors(BLACK, WHITE);
		switch(mainMenu.currentChoice) {
			case 0: {
				HumanPlayer player1{PLAYER1_PAWN, ui};
				HumanPlayer player2{PLAYER2_PAWN, ui};
				manager.playGame(player1, player2, ui);
			}
				break;
			case 1: {
				HumanPlayer player1{PLAYER1_PAWN, ui};
				AIPlayer player2(PLAYER2_PAWN, depthChoice(1));
				if(turnChoice()) {
					manager.playGame(player1, player2, ui);
				}
				else {
					manager.playGame(player2, player1, ui);
				}
			}
				break;
			case 2: {
				AIPlayer player1{PLAYER1_PAWN, depthChoice(1)};
				AIPlayer player2(PLAYER2_PAWN, depthChoice(2));
				manager.playGame(player1, player2, ui);
			}
				break;
			case 3:
				//TODO
				break;
			case 4:
				loop = !checkExit();
				break;
			default:
				break;
		}
	}
	return 0;
}

unsigned int depthChoice(unsigned int number) {
	const char* difficultyChoices[] = {
		"1",
		"2",
		"3",
		"4",
		"5"
	};

	std::string title("AI ");
	title += static_cast<char>('0' + number);
	title += " Difficulty";
	cc_Menu difficulty;
	difficulty.choices = difficultyChoices;
	difficulty.choicesNumber = 5;
	difficulty.currentChoice = 0;
	difficulty.choiceOnEscape = -1;
	difficulty.title = title.c_str();
	cc_displayColorMenu(&difficulty, &menuColors);
	return difficulty.currentChoice + 1;
}

bool turnChoice() {
	cc_Message message{
		"Turns order",
		"Who plays first ?",
		"Human",
		NULL,
		"AI",
		RIGHT_CHOICE,
		false
	};

	cc_displayColorMessage(&message, &messageColors);
	return message.currentChoice == RIGHT_CHOICE;
}

bool checkExit() {
	cc_Message message{
		NULL,
		"Are you sure you want to exit ?",
		"no",
		NULL,
		"yes",
		RIGHT_CHOICE,
		true
	};

	cc_displayColorMessage(&message, &messageColors);
	return message.currentChoice == RIGHT_CHOICE;
}
