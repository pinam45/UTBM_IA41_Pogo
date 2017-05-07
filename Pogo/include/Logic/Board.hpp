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
 * @brief      Definition of the Board class.
 * @author     Maxime Pinard
 * @date       11/04/17
 * @version    0.0
 */

#ifndef UTBM_IA41_POGO_BOARD_HPP
#define UTBM_IA41_POGO_BOARD_HPP


#include <type_traits>

#include <Logic/PawnStack.hpp>
#include <Logic/PawnsMove.hpp>

/*-------------------------------------------------------------------------*//**
 * @brief      Pogo board containing pawns stacks.
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
class Board {

	static_assert(is_pawn_stack<PawnStackType>::value, "Invalid pawn stack type");

private:

	class BoardLine {

		static_assert(is_pawn_stack<PawnStackType>::value, "Invalid pawn stack type");

		friend class Board<PawnStackType, width, height>;

	public:

		PawnStackType& operator[](unsigned int index);

		const PawnStackType& operator[](unsigned int index) const;

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
	 *
	 * @return     The board after the move
	 */
	Board<PawnStackType, width, height>& apply(const PawnsMove& move);

	/*------------------------------------------------------------------------*//**
	 * @brief      Compute the number of stack controlled by a player.
	 *
	 * @param[in]  player  The player
	 *
	 * @return     The number of stack controlled by the player
	 */
	unsigned int controlledStacks(Pawn player);

	/*------------------------------------------------------------------------*//**
	 * @brief      Default destructor.
	 */
	virtual ~Board() = default;

	BoardLine& operator[](unsigned int index);

	const BoardLine& operator[](unsigned int index) const;

private:

	BoardLine m_board[width];

};

template<typename PawnStackType, unsigned int width, unsigned int height>
Board<PawnStackType, width, height>::Board() {

}

template<typename PawnStackType, unsigned int width, unsigned int height>
Board<PawnStackType, width, height>& Board<PawnStackType, width, height>::apply(const PawnsMove& move) {
	m_board[move.toX][move.toY].add(m_board[move.fromX][move.fromY].pick(move.pawnNumber));
	return *this;
}

template<typename PawnStackType, unsigned int width, unsigned int height>
typename Board<PawnStackType, width, height>::BoardLine&
Board<PawnStackType, width, height>::operator[](unsigned int index) {
	return m_board[index];
}

template<typename PawnStackType, unsigned int width, unsigned int height>
typename Board<PawnStackType, width, height>::BoardLine const&
Board<PawnStackType, width, height>::operator[](unsigned int index) const {
	return m_board[index];
}

template<typename PawnStackType, unsigned int width, unsigned int height>
unsigned int Board<PawnStackType, width, height>::controlledStacks(Pawn player) {
	unsigned int counter = 0;
	for(unsigned int i = 0; i < width; ++i) {
		for(unsigned int j = 0; j < height; ++j) {
			if(m_board[i][j].size()) {
				counter += (m_board[i][j][m_board[i][j].size() - 1] == player);
			}
		}
	}
	return counter;
}

template<typename PawnStackType, unsigned int width, unsigned int height>
Board<PawnStackType, width, height>::BoardLine::BoardLine() {

}

template<typename PawnStackType, unsigned int width, unsigned int height>
PawnStackType& Board<PawnStackType, width, height>::BoardLine::operator[](unsigned int index) {
	return m_line[index];
}

template<typename PawnStackType, unsigned int width, unsigned int height>
const PawnStackType& Board<PawnStackType, width, height>::BoardLine::operator[](unsigned int index) const {
	return m_line[index];
}


#endif //UTBM_IA41_POGO_BOARD_HPP
