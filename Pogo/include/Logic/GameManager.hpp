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
 * @tparam     BoardType  Type of the board
 */
template<typename BoardType>
class GameManager;

template<
	typename PawnStackType,
	unsigned int width,
	unsigned int height
>
class GameManager<Board<PawnStackType, width, height>> {

	using BoardType = Board<PawnStackType, width, height>;

public:

	/*------------------------------------------------------------------------*//**
	 * @brief      Launch a game, player1 play against player2, player2 play
	 *             first.
	 *
	 * @param      player1  The player 1
	 * @param      player2  The player 2
	 * @param      UI       The User Interface to use
	 */
	void playGame(Player<BoardType>& player1, Player<BoardType>& player2, std::string player1Name,
	              std::string player2Name, UI<BoardType>& UI);

	/*------------------------------------------------------------------------*//**
	 * @brief      Default destructor.
	 */
	virtual ~GameManager() = default;

private:

	BoardType initialBoard();

};

template<typename PawnStackType, unsigned int width, unsigned int height>
void GameManager<Board<PawnStackType, width, height>>::playGame(Player<BoardType>& player1, Player<BoardType>& player2,
                                                                std::string player1Name, std::string player2Name,
                                                                UI<BoardType>& UI) {

	BoardType board = initialBoard();
	Player<BoardType>* players[2] = {&player1, &player2};
	PawnsMove move;

	unsigned int turn = 0;
	UI.displayBoard(board);
	while(true) {
		move = players[++turn % 2]->chooseMove(board);
		if(move.pawnNumber == 0){
			break;
		}
		board.apply(move);
		UI.displayBoard(board);
		if(!board.controlledStacks(PLAYER1_PAWN)) {
			UI.displayVictory(player2Name, board);
			break;
		}
		if(!board.controlledStacks(PLAYER2_PAWN)) {
			UI.displayVictory(player1Name, board);
			break;
		}
	}
}

template<typename PawnStackType, unsigned int width, unsigned int height>
Board<PawnStackType, width, height> GameManager<Board<PawnStackType, width, height>>::initialBoard() {
	BoardType board;
	for(unsigned int i = 0; i < width; ++i) {
		board[i][0] = PawnStackType(PLAYER2_DEFAULT_STACK);
	}
	for(unsigned int i = 0; i < width; ++i) {
		board[i][height - 1] = PawnStackType(PLAYER1_DEFAULT_STACK);
	}
	return board;
}


#endif //UTBM_IA41_POGO_GAMEMANAGER_HPP
