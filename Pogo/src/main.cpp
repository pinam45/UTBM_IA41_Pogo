#include <iostream>
#include <ConsoleControl.h>
#include <ConsoleControlUI.h>
#include <Logic/PawnStack.hpp>
#include <Logic/Board.hpp>
#include <Logic/GameManager.hpp>
#include <Logic/HumanPlayer.hpp>
#include <Logic/AlphaBetaAIPlayer.hpp>
#include <Logic/MinMaxAIPlayer.hpp>
#include <UI/ConsoleUI.hpp>
#include <ConsoleControlMenu.h>
#include <ConsoleControlMessage.h>

#define BOARD_WIDTH 3
#define BOARD_HEIGHT 3
using PawnStackType = PawnStack16;
using BoardType = Board<PawnStackType, BOARD_WIDTH, BOARD_HEIGHT>;

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

float stackDiffEval(const BoardType board, Pawn pawn);

float stackFracEval(const BoardType board, Pawn pawn);

float pawnsFracEval(const BoardType board, Pawn pawn);

void playHumanHuman();

void playHumanAI();

void playAIAI();

bool checkExit();

int main() {
	const char* choices[] = {
		"Human vs Human",
		"Human vs A.I.",
		"A.I. vs A.I.",
		"Exit"
	};
	cc_Menu mainMenu;
	mainMenu.choices = choices;
	mainMenu.choicesNumber = 4;
	mainMenu.currentChoice = 0;
	mainMenu.choiceOnEscape = 3;
	mainMenu.title = "Magic Pogo";
	bool loop = true;
	while(loop) {
		ConsoleUI<BoardType> ui;
		GameManager<BoardType> manager;

		cc_displayColorMenu(&mainMenu, &menuColors);
		cc_setColors(BLACK, WHITE);
		switch(mainMenu.currentChoice) {
			case 0: {
				playHumanHuman();
			}
				break;
			case 1:
				playHumanAI();
				break;
			case 2:
				playAIAI();
				break;
			case 3:
				loop = !checkExit();
				break;
			default:
				break;
		}
	}
	cc_setCursorVisibility(true);
	cc_displayInputs(true);
	return 0;
}

float stackDiffEval(const BoardType board, Pawn pawn) {
	float eval = 0;
	for(int x = 0; x < BOARD_WIDTH; ++x) {
		for(int y = 0; y < BOARD_HEIGHT; ++y) {
			if(board[x][y].size()) {
				if(board[x][y].get(board[x][y].size() - 1) == pawn) {
					++eval;
				}
				else {
					--eval;
				}
			}
		}
	}
	return eval;
}

float stackFracEval(const BoardType board, Pawn pawn) {
	unsigned int stacks = 0;
	unsigned int controlledStacks = 0;
	for(int x = 0; x < BOARD_WIDTH; ++x) {
		for(int y = 0; y < BOARD_HEIGHT; ++y) {
			if(board[x][y].size()) {
				++stacks;
				if(board[x][y].get(board[x][y].size() - 1) == pawn) {
					++controlledStacks;
				}
			}
		}
	}
	return static_cast<float>(controlledStacks) / static_cast<float>(stacks);
}

float pawnsFracEval(const BoardType board, Pawn pawn) {
	unsigned int pawns = 0;
	unsigned int controlledPawns = 0;
	for(int x = 0; x < BOARD_WIDTH; ++x) {
		for(int y = 0; y < BOARD_HEIGHT; ++y) {
			unsigned int size = board[x][y].size();
			if(size) {
				pawns += size;
				if(board[x][y].get(size - 1) == pawn) {
					controlledPawns += size;
				}
			}
		}
	}
	return static_cast<float>(controlledPawns) / static_cast<float>(pawns);
}

void playHumanHuman() {
	cc_Message message{
		"Turns order",
		"Human 1 play first",
		NULL,
		NULL,
		NULL,
		NO_CHOICE,
		true
	};
	cc_displayColorMessage(&message, &messageColors);
	ConsoleUI<BoardType> ui;
	GameManager<BoardType> manager;
	HumanPlayer<BoardType> player1{PLAYER1_PAWN, ui};
	HumanPlayer<BoardType> player2{PLAYER2_PAWN, ui};
	manager.playGame(player1, player2, "Human 1", "Human 2", ui);
}

void playHumanAI() {

	/* Choose AI depth */
	cc_IntegerOption integerOption = {1, 1, 7, 1};
	cc_Option option;
	option.name = "AI depth";
	option.optionType = INTEGER_OPTION;
	option.integerOption = &integerOption;
	cc_Option* options[] = {&option};
	cc_OptionsMenu optionsMenu = {
		"AI difficulty",
		options,
		1,
		0,
		"OK",
		false
	};
	cc_displayColorOptionMenu(&optionsMenu, &menuColors);

	/* Choose turn order */
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

	ConsoleUI<BoardType> ui;
	GameManager<BoardType> manager;
	HumanPlayer<BoardType> player1{PLAYER1_PAWN, ui};
	AlphaBetaAIPlayer<BoardType> player2(PLAYER2_PAWN, static_cast<unsigned int>(integerOption.value), &stackFracEval);

	if(message.currentChoice == RIGHT_CHOICE) {
		manager.playGame(player1, player2, "Human", "AI", ui);
	}
	else {
		manager.playGame(player2, player1, "AI", "Human", ui);
	}
}

void playAIAI() {

	/* Choose AIs depths */
	cc_IntegerOption integerOption1 = {1, 1, 7, 1};
	cc_Option option1;
	option1.name = "AI 1 depth";
	option1.optionType = INTEGER_OPTION;
	option1.integerOption = &integerOption1;
	cc_IntegerOption integerOption2 = {1, 1, 7, 1};
	cc_Option option2;
	option2.name = "AI 2 depth";
	option2.optionType = INTEGER_OPTION;
	option2.integerOption = &integerOption2;
	cc_Option* options[] = {&option1, &option2};
	cc_OptionsMenu optionsMenu = {
		"AI difficulty",
		options,
		2,
		0,
		"OK",
		false
	};
	cc_displayColorOptionMenu(&optionsMenu, &menuColors);

	ConsoleUI<BoardType> ui;
	GameManager<BoardType> manager;
	AlphaBetaAIPlayer<BoardType> player1(PLAYER1_PAWN, static_cast<unsigned int>(integerOption1.value), &pawnsFracEval);
	AlphaBetaAIPlayer<BoardType> player2(PLAYER2_PAWN, static_cast<unsigned int>(integerOption2.value), &pawnsFracEval);

	std::string AI1Name("AI 1 (depth ");
	AI1Name += static_cast<char>('0' + integerOption1.value);
	AI1Name += ")";
	std::string AI2Name("AI 2 (depth ");
	AI2Name += static_cast<char>('0' + integerOption2.value);
	AI2Name += ")";
	manager.playGame(player1, player2, AI1Name, AI2Name, ui);
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
	return message.currentChoice == RIGHT_CHOICE || message.currentChoice == NO_CHOICE;
}
