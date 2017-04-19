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
 * @file       AIPlayer.hpp
 * @brief      Definition of the AIPlayer class.
 * @date       12/04/17
 * @version    0.0
 */

#ifndef UTBM_IA41_POGO_AIPLAYER_HPP
#define UTBM_IA41_POGO_AIPLAYER_HPP

#include <vector>
#include <Logic/Player.hpp>
#include <iostream>

class AIPlayer : public Player {

private :

	/**
	 * @struct Node
	 * @brief Definition of a N-ary tree, used to build the possible moves
	 * @date 12/04/17
	 * @version 0.0
	 */
	struct Node {
		float val;
		std::vector<Node> children;
	};

	/*------------------------------------------------------------------------*//**
	 * @brief      Evaluates the board for the AI
	 *
	 * @param[in]  board   The board of the game
	 *
	 * @return     The value of the board for the AI
	 */
	float eval(const Board<PawnStack16>& board) const;

	/*------------------------------------------------------------------------*//**
	 * @brief      Build the tree of all possible moves
	 *
	 * @param[in]  depth   The depth of the tree
	 * @param[in]  root    The root of the tree
	 * @param[in]  board   The board of the game
	 *
	 * @details    implemented with Depth-first order
	 */
	void buildTree (const unsigned int depth, const Pawn toPlay,Node& root, Board<PawnStack16> & board) ;

	/*------------------------------------------------------------------------*//**
	 * @brief      Build a children node
	 *
	 * @param[in]  move    The move to apply
	 * @param[in]  depth   The depth of the tree
	 * @param[in]  toPlay  The pawn of the game
	 * @param[in]  board   The board of the game
	 * @param[in]  root    The root of the tree
	 *
	 * @details    implemented with Depth-first order
	 */
	void buildChildren(const PawnsMove& move, const unsigned int depth, const Pawn toPlay, Node& root, Board<PawnStack16>& board) ;

	/*------------------------------------------------------------------------*//**
	 * @brief      Gives the list of the possibles moves for one turn
	 *
	 * @param[in]  board   The board of the game
	 *
	 * @return     The vector of moves possible by the AI for one turn
	 */
	 std::vector<PawnsMove> firstMoves (const Board<PawnStack16>& board) const;

	/*------------------------------------------------------------------------*//**
	 * @brief      alphaBeta algorithm filling the nodes value
	 *
	 * @param[in]  root   The root of the tree
	 * @param[in]  depth  The depth of the tree
	 */
	 static void alphaBeta(Node& root, const unsigned int depth) ;

	/*------------------------------------------------------------------------*//**
	 * @brief      gives the value for MAX nodes
	 *
	 * @param[in]  root   The node to evaluate
	 * @param[in]  depth  The depth of the tree
	 * @param[in]  alpha  The alpha value of the Alpha Beta algorithm
	 * @param[in]  beta   The beta value of the Alpha Beta algorithm
	 *
	 * @return     the value of the given MAX node
	 */
	static float maxValue(Node& root, const unsigned int depth, float alpha, float beta) ;

	/*------------------------------------------------------------------------*//**
	 * @brief      gives the value for MIN nodes
	 *
	 * @param[in]  root   The node to evaluate
	 * @param[in]  depth  The depth of the tree
	 * @param[in]  alpha  The alpha value of the Alpha Beta algorithm
	 * @param[in]  beta   The beta value of the Alpha Beta algorithm
	 *
	 * @return     the value of the given MIN node
	 */
	static float minValue(Node& root, const unsigned int depth, float alpha, float beta) ;


	static int ManhattanDistance(const int x1, const int y1, const int x2, const int y2) {
		return abs(x1 - x2) + abs (y1 -  y2);
	}

	unsigned int m_depth;

public:
	PawnsMove chooseMove(Board<PawnStack16>& board) ;

	/*------------------------------------------------------------------------*//**
	 * @brief      Construct an AIPlayer
	 *
	 * @param[in]  pawn     the pawn of the AIPlayer
	 * @param[in]  depth    the depth of the tree generated
	 */
	AIPlayer(const Pawn pawn, const unsigned int depth) : Player(pawn), m_depth(depth) {}
};


#endif //UTBM_IA41_POGO_AIPLAYER_HPP
