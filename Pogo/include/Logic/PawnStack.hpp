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

#ifndef UTBM_IA41_POGO_PAWNSTACK_HPP
#define UTBM_IA41_POGO_PAWNSTACK_HPP


#include <ostream>
#include <vector>
#include <cstdint>

#include <Log.h>
#include <Logic/Pawn.hpp>

#define PLAYER1_DEFAULT_STACK 0b00000100
#define PLAYER2_DEFAULT_STACK 0b00000111

/*-------------------------------------------------------------------------*//**
 * @brief      A stack of pawn, contain up to 7 pawns.
 *
 * @details    Use a uint8_t to store the pawn, the last 1 bit is the size
 *             delimiter and the previous bits are the pawns.
 */
class PawnStack {

	friend std::ostream& operator<<(std::ostream& os, const PawnStack& pawnStack);

public:

	/*------------------------------------------------------------------------*//**
	 * @brief      Construct a new pawn stack.
	 *
	 * @param[in]  stack  The stack initial value, must have a size delimitation
	 *                    bit
	 */
	explicit PawnStack(const uint8_t stack);

	/*------------------------------------------------------------------------*//**
	 * @brief      Compute the stack size.
	 *
	 * @return     The stack size
	 */
	unsigned int size() const;

	/*------------------------------------------------------------------------*//**
	 * @brief      The stack maximum size.
	 *
	 * @return     The stack maximum size
	 */
	static constexpr unsigned int max_size();

	/*------------------------------------------------------------------------*//**
	 * @brief      Pick a given number of pawn from the top of the stack.
	 *
	 * @param[in]  number  The number of pawns to pick
	 *
	 * @return     A stack containing the picked pawns
	 */
	PawnStack pick(const unsigned int number);

	/*------------------------------------------------------------------------*//**
	 * @brief      Adds paws at the top of the stack.
	 *
	 * @param[in]  pawnStack  The stack containing the pawns to add
	 */
	void add(const PawnStack pawnStack);

	/*------------------------------------------------------------------------*//**
	 * @brief      Get the pawn at the given position
	 *
	 * @param[in]  pos   The position of the pawn
	 *
	 * @return     The pawn at the given position
	 */
	inline Pawn get(const unsigned int pos) const;

private:

	uint8_t m_stack;

};

Pawn PawnStack::get(const unsigned int pos) const {
	if(pos >= size()) {
		SLOG_ERR("position out of the stack");
	}
	return static_cast<Pawn>((m_stack >> pos) & 1);
}


#endif //UTBM_IA41_POGO_PAWNSTACK_HPP
