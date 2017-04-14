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
 * @file Board.hpp
 * @brief      Definition of the Board type.
 * @author     Maxime Pinard
 * @date       11/04/17
 * @version    0.0
 */

#ifndef UTBM_IA41_POGO_BOARD_HPP
#define UTBM_IA41_POGO_BOARD_HPP


#include <type_traits>

#include <Logic/PawnStack.hpp>
#include <Logic/PawnsMove.hpp>

template<class T>
struct is_pawn_stack : std::false_type {
};

template<class T>
struct is_pawn_stack<PawnStack<T>> : std::true_type {
};

/*-------------------------------------------------------------------------*//**
 * @brief      Pogo board containing pawns stacks.
 *
 * @tparam     PawnStackType  Pawns stacks type
 * @tparam     width          Width of the board (default = 3)
 * @tparam     height         Height of the board (default = 3)
 * @tparam     check          Check that @c PawnStackType is a PawnStack
 */
template<
	typename PawnStackType,
	unsigned int width = 3,
	unsigned int height = 3,
	typename check = typename std::enable_if_t<is_pawn_stack<PawnStackType>::value>
>
class Board {

private:

	class BoardLine {

		friend class Board<PawnStackType, width, height, check>;

	public:

		PawnStackType& operator[](unsigned int index);

	private:

		BoardLine();

		PawnStackType m_line[height];

	};

public:

	/*------------------------------------------------------------------------*//**
	 * @brief      Construct a new empty board.
	 */
	Board();

	/*------------------------------------------------------------------------*//**
	 * @brief      Apply the pawns move.
	 *
	 * @param[in]  move  The move
	 */
	void apply(const PawnsMove& move);

	BoardLine& operator[](unsigned int index);

private:

	BoardLine m_board[width];

};

template<typename PawnStackType, unsigned int width, unsigned int height, typename check>
Board<PawnStackType, width, height, check>::Board() {

}

template<typename PawnStackType, unsigned int width, unsigned int height, typename check>
typename Board<PawnStackType, width, height, check>::BoardLine&
Board<PawnStackType, width, height, check>::operator[](unsigned int index) {
	return m_board[index];
}

template<typename PawnStackType, unsigned int width, unsigned int height, typename check>
void Board<PawnStackType, width, height, check>::apply(const PawnsMove& move) {
	m_board[move.toX][move.toY].add(m_board[move.fromX][move.fromY].pick(move.pawnNumber));
}

template<typename PawnStackType, unsigned int width, unsigned int height, typename check>
Board<PawnStackType, width, height, check>::BoardLine::BoardLine() {

}

template<typename PawnStackType, unsigned int width, unsigned int height, typename check>
PawnStackType& Board<PawnStackType, width, height, check>::BoardLine::operator[](unsigned int index) {
	return m_line[index];
}


#endif //UTBM_IA41_POGO_BOARD_HPP