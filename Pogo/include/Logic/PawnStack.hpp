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
#include <limits>

#include <cstdint>
#include <climits>

#include <log.h>
#include <Logic/Pawn.hpp>

#define EMPTY_STACK 0b1
#define PLAYER1_DEFAULT_STACK 0b100
#define PLAYER2_DEFAULT_STACK 0b111

template<typename container, typename = typename std::enable_if_t<std::is_integral<container>::value>>
class PawnStack;

template<class T>
struct is_pawn_stack : std::false_type {
};

template<class T>
struct is_pawn_stack<PawnStack<T>> : std::true_type {
};

using PawnStack8 = PawnStack<uint8_t>;
using PawnStack16 = PawnStack<uint16_t>;
using PawnStack32 = PawnStack<uint32_t>;
using PawnStack64 = PawnStack<uint64_t>;

/*-------------------------------------------------------------------------*//**
 * @brief      A stack of pawn, contain up to sizeof(container) pawns.
 *
 * @details    Use a @c container to store the pawn, the last 1 bit is the size
 *             delimiter and the previous bits are the pawns.
 *
 * @tparam     container  Type to use as container
 * @tparam     check      Check that @c container is integral
 */
template<typename container, typename check>
class PawnStack {

	template<typename T, typename Y>
	friend std::ostream& operator<<(std::ostream& os, const PawnStack<T, Y>& pawnStack);

public:

	/*------------------------------------------------------------------------*//**
	 * @brief      Construct a new empty pawn stack.
	 */
	PawnStack();

	/*------------------------------------------------------------------------*//**
	 * @brief      Construct a new pawn stack.
	 *
	 * @param[in]  stack  The stack initial value, must have a size delimitation
	 *                    bit
	 */
	explicit PawnStack(const container stack);

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
	PawnStack<container, check> pick(const unsigned int number);

	/*------------------------------------------------------------------------*//**
	 * @brief      Adds paws at the top of the stack.
	 *
	 * @param[in]  pawnStack  The stack containing the pawns to add
	 */
	void add(const PawnStack<container, check> pawnStack);

	/*------------------------------------------------------------------------*//**
	 * @brief      Get the pawn at the given position
	 *
	 * @param[in]  pos   The position of the pawn
	 *
	 * @return     The pawn at the given position
	 */
	inline Pawn get(unsigned int pos) const;

	Pawn operator[](unsigned int pos) const;

private:

	container m_stack;

};

template<typename T, typename check>
std::ostream& operator<<(std::ostream& os, const PawnStack<T, check>& pawnStack) {
	os << "[";
	for(unsigned int i = PawnStack<T, check>::max_size() + 1; --i;) {
		os << ((pawnStack.m_stack >> i) & 1);
	}
	os << (pawnStack.m_stack & 1) << "]";
	return os;
}

template<typename T, typename check>
PawnStack<T, check>::PawnStack() : m_stack(EMPTY_STACK) {

}

template<typename T, typename check>
PawnStack<T, check>::PawnStack(const T stack) : m_stack(stack) {
	if(!stack) {
		SLOG_ERR("Empty stack: no end byte");
	}
}

template<typename T, typename check>
unsigned int PawnStack<T, check>::size() const {
	for(unsigned int i = max_size() + 1; --i;) {
		if(m_stack >> i == 1) {
			return i;
		}
	}
	return 0;
}

template<typename T, typename check>
constexpr unsigned int PawnStack<T, check>::max_size() {
	return sizeof(m_stack) * CHAR_BIT - 1;
}

template<typename T, typename check>
PawnStack<T, check> PawnStack<T, check>::pick(const unsigned int number) {
	unsigned int currentSize = size();
	T stack = static_cast<T>(m_stack >> (size() - number));
	m_stack = static_cast<T>(m_stack & (std::numeric_limits<T>::max() >> (max_size() + 1 - currentSize + number)));
	m_stack = static_cast<T>(m_stack | (1 << (currentSize - number)));
	return PawnStack<T>(stack);
}

template<typename T, typename check>
void PawnStack<T, check>::add(const PawnStack pawnStack) {
	unsigned int currentSize = size();
	unsigned int addedSize = pawnStack.size();
	if(currentSize + addedSize > PawnStack<T, check>::max_size()) {
		SLOG_ERR("new size bigger than max size");
	}
	m_stack = static_cast<T>(m_stack & (std::numeric_limits<T>::max() >> (PawnStack<T, check>::max_size() + 1 - currentSize)));
	m_stack = static_cast<T>(m_stack | (pawnStack.m_stack << currentSize));
}

template<typename T, typename check>
Pawn PawnStack<T, check>::get(unsigned int pos) const {
	if(pos >= size()) {
		SLOG_ERR("position out of the stack");
	}
	return static_cast<Pawn>((m_stack >> pos) & 1);
}

template<typename T, typename check>
Pawn PawnStack<T, check>::operator[](unsigned int pos) const {
	if(pos >= size()) {
		SLOG_ERR("position out of the stack");
	}
	return static_cast<Pawn>((m_stack >> pos) & 1);
}


#endif //UTBM_IA41_POGO_PAWNSTACK_HPP
