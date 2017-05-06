/*****************************************************************************************
 *                                                                                       *
 * MIT License                                                                           *
 *                                                                                       *
 * Copyright (c) 2017 Julien Barbier & Kadir Ercin & Maxime Pinard                       *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy          *
 * of this software and associated documentation files (the "Software"), to deal         *
 * in the Software without restriction, including without limitation the rights          *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell             *
 * copies of the Software, and to permit persons to whom the Software is                 *
 * furnished to do so, subject to the following conditions:                              *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all        *
 * copies or substantial portions of the Software.                                       *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR            *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,              *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE           *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,         *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE         *
 * SOFTWARE.                                                                             *
 *                                                                                       *
 *****************************************************************************************/

/**
 * @file GameManager.hpp
 * @brief      Definition of the GameManager class.
 * @author     Maxime Pinard
 * @date       19/04/17
 * @version    0.0
 */

#ifndef UTBM_IA41_POGO_GAMEMANAGER_HPP
#define UTBM_IA41_POGO_GAMEMANAGER_HPP


#include <Logic/Player.hpp>
#include <UI/UI.hpp>
#include <UI/ConsoleUI.hpp>

/*-------------------------------------------------------------------------*//**
 * @brief      Pogo game manager, ask the players for a move one after the other
 *             until a player win and display the board using an User Interface.
 *
 * @tparam     PawnStackType  Pawns stacks type
 * @tparam     width          Width of the board (default = 3)
 * @tparam     height         Height of the board (default = 3)
 */
template<
	typename PawnStackType,
	unsigned int width = 3,
	unsigned int height = 3
>
class GameManager {

	static_assert(is_pawn_stack<PawnStackType>::value, "Invalid pawn stack type");

public:

	/*------------------------------------------------------------------------*//**
	 * @brief      Launch a game, player1 play against player2, player2 play
	 *             first.
	 *
	 * @param      player1  The player 1
	 * @param      player2  The player 2
	 * @param      UI       The User Interface to use
	 */
	void playGame(Player& player1, Player& player2, UI<PawnStackType, width, height>& UI);

private:

	Board<PawnStackType, width, height> initialBoard();

};

template<typename PawnStackType, unsigned int width, unsigned int height>
void GameManager<PawnStackType, width, height>::playGame(Player& player1, Player& player2,
                                                         UI<PawnStackType, width, height>& UI) {

	Board<PawnStackType, width, height> board = initialBoard();
	Player* players[2] = {&player1, &player2};

	unsigned int turn = 0;
	Pawn winner;
	UI.displayBoard(board);
	while(true) {
		board.apply(players[++turn % 2]->chooseMove(board));
		UI.displayBoard(board);
		if(!board.controlledStacks(PLAYER1_PAWN)) {
			winner = PLAYER2_PAWN;
			break;
		}
		if(!board.controlledStacks(PLAYER2_PAWN)) {
			winner = PLAYER1_PAWN;
			break;
		}
	}
	UI.displayVictory(winner);
}

template<typename PawnStackType, unsigned int width, unsigned int height>
Board<PawnStackType, width, height> GameManager<PawnStackType, width, height>::initialBoard() {
	Board<PawnStackType, width, height> board;
	for(unsigned int i = 0; i < width; ++i) {
		board[i][0] = PawnStackType(PLAYER2_DEFAULT_STACK);
	}
	for(unsigned int i = 0; i < width; ++i) {
		board[i][height - 1] = PawnStackType(PLAYER1_DEFAULT_STACK);
	}
	return board;
}


#endif //UTBM_IA41_POGO_GAMEMANAGER_HPP
