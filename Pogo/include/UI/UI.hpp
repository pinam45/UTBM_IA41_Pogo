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
 * @tparam     PawnStackType  Type of stack to use, determine the size of the
 *                            displayed stack
 * @tparam     width          Width of the board (number of stacks in one line)
 * @tparam     height         Height of the board (number of stacks in one line)
 * @tparam     check          Check that @c PawnStackType is a pawn stack type
 */
template<
	typename PawnStackType,
	unsigned int width = 3,
	unsigned int height = 3,
	typename check = typename std::enable_if_t<is_pawn_stack<PawnStackType>::value>
>
class UI {

public:

	/*------------------------------------------------------------------------*//**
	 * @brief      Draws the board.
	 *
	 * @param[in]  board  The board
	 */
	virtual void drawBoard(const Board<PawnStackType, width, height>& board) = 0;

	/*------------------------------------------------------------------------*//**
	 * @brief      Allow the user to choose a move.
	 *
	 * @param[in]  board   The board
	 * @param[in]  player  The player
	 *
	 * @return     A valid Pogo move for the board.
	 */
	virtual PawnsMove chooseMove(const Board<PawnStackType, width, height>& board, bool player) = 0;

	/*------------------------------------------------------------------------*//**
	 * @brief      Default destructor.
	 */
	virtual ~UI() = default;

};


#endif //UTBM_IA41_POGO_UI_HPP
