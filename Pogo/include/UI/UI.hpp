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
 * @file UI.hpp
 * @brief      Definition of the UI class.
 * @author     Maxime Pinard
 * @date       13/04/17
 * @version    0.0
 */

#ifndef UTBM_IA41_POGO_UI_HPP
#define UTBM_IA41_POGO_UI_HPP


#include <Logic/Board.hpp>

/*-------------------------------------------------------------------------*//**
 * @brief      User Interface, interface with the user for playing the Pogo
 *             game.
 *
 * @tparam     BoardType  Type of the board
 */
template<typename BoardType>
class UI;

template<
	typename PawnStackType,
	unsigned int width,
	unsigned int height
>
class UI<Board<PawnStackType, width, height>> {

	using BoardType = Board<PawnStackType, width, height>;

public:

	/*------------------------------------------------------------------------*//**
	 * @brief      Display the board.
	 *
	 * @param[in]  board  The board
	 */
	virtual void displayBoard(const BoardType& board) = 0;

	/*------------------------------------------------------------------------*//**
	 * @brief      Allow the user to choose a move.
	 *
	 * @param[in]  board   The board
	 * @param[in]  player  The player
	 *
	 * @return     A valid Pogo move for the board.
	 */
	virtual PawnsMove chooseMove(const BoardType& board, Pawn player) = 0;

	/*------------------------------------------------------------------------*//**
	 * @brief      Display the victory screen.
	 *
	 * @param[in]  player  The player who won the game
	 */
	virtual void displayVictory(Pawn player) = 0;

	/*------------------------------------------------------------------------*//**
	 * @brief      Default destructor.
	 */
	virtual ~UI() = default;

};


#endif //UTBM_IA41_POGO_UI_HPP
