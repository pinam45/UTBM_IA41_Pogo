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
 * @file Player.hpp
 * @brief      Definition of the Player class.
 * @date       12/04/17
 * @version    0.0
 */

#ifndef UTBM_IA41_POGO_PLAYER_HPP
#define UTBM_IA41_POGO_PLAYER_HPP


#include <Logic/Pawn.hpp>
#include <Logic/Board.hpp>
#include <Logic/PawnsMove.hpp>

/*-------------------------------------------------------------------------*//**
 * @brief      Pogo player, player classes should extend this class to be used
 *             with the @c GameManager
 *
 * @tparam     BoardType  Type of the board
 */
template<typename BoardType>
class Player;

template<
	typename PawnStackType,
	unsigned int width,
	unsigned int height
>
class Player<Board<PawnStackType, width, height>> {

public:

	/*------------------------------------------------------------------------*//**
	 * @brief      Construct a new player.
	 *
	 * @param[in]  pawn  The pawn of the player, either PLAYER1_PAWN or
	 *                   PLAYER2_PAWN
	 */
	explicit Player(Pawn pawn);

	/*------------------------------------------------------------------------*//**
	 * @brief      Choose a move to play.
	 *
	 * @param[in]  board  The board of the game
	 *
	 * @return     The move chosen by the player
	 */
	virtual PawnsMove chooseMove(const Board<PawnStackType, width, height>& board) = 0;

	/*------------------------------------------------------------------------*//**
	 * @brief      Default destructor.
	 */
	virtual ~Player() = default;

protected:

	Pawn m_pawn;

};

template<typename PawnStackType, unsigned int width, unsigned int height>
Player<Board<PawnStackType, width, height>>::Player(Pawn pawn) : m_pawn(pawn) {

}


#endif //UTBM_IA41_POGO_PLAYER_HPP
