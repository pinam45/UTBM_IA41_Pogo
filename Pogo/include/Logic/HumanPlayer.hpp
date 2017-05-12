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
 * @file HumanPlayer.hpp
 * @brief      Definition of the HumanPlayer class.
 * @author     Maxime Pinard
 * @date       20/04/17
 * @version    0.0
 */

#ifndef UTBM_IA41_POGO_HUMANPLAYER_HPP
#define UTBM_IA41_POGO_HUMANPLAYER_HPP


#include <Logic/Player.hpp>
#include <UI/UI.hpp>

/*-------------------------------------------------------------------------*//**
 * @brief      Pogo human player, use the UI to choose moves.
 *
 * @tparam     BoardType  Type of the board
 */
template<typename BoardType>
class HumanPlayer;

template<
	typename PawnStackType,
	unsigned int width,
	unsigned int height
>
class HumanPlayer<Board<PawnStackType, width, height>> : public Player<Board<PawnStackType, width, height>> {

	using BoardType = Board<PawnStackType, width, height>;

public:

	/*------------------------------------------------------------------------*//**
	 * @brief      Constructor.
	 *
	 * @param[in]  pawn  The pawn of the player
	 * @param      ui    The user interface for choosing moves
	 */
	HumanPlayer(Pawn pawn, UI<BoardType>& ui);

	/*------------------------------------------------------------------------*//**
	 * @brief      Choose a move to play using the UI.
	 *
	 * @param[in]  board  The board of the game
	 *
	 * @return     The move chosen by the player
	 */
	PawnsMove chooseMove(const BoardType& board) override;

	/*------------------------------------------------------------------------*//**
	 * @brief      Default destructor.
	 */
	virtual ~HumanPlayer() = default;

private:

	UI<BoardType>& m_ui;

};

template<typename PawnStackType, unsigned int width, unsigned int height>
HumanPlayer<Board<PawnStackType, width, height>>::HumanPlayer(Pawn pawn, UI<BoardType>& ui)
	: Player<BoardType>(pawn), m_ui(ui) {

}

template<typename PawnStackType, unsigned int width, unsigned int height>
PawnsMove HumanPlayer<Board<PawnStackType, width, height>>::chooseMove(const BoardType& board) {
	return m_ui.chooseMove(board, Player<BoardType>::usedPawn);
}


#endif //UTBM_IA41_POGO_HUMANPLAYER_HPP
