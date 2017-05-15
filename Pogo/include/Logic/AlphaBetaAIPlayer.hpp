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
 * @file AlphaBetaAIPlayer.hpp
 * @brief      Definition of the AlphaBetaAIPlayer class.
 * @author     Maxime Pinard
 * @date       07/05/17
 * @version    0.0
 */

#ifndef UTBM_IA41_POGO_ALPHABETAAIPLAYER_HPP
#define UTBM_IA41_POGO_ALPHABETAAIPLAYER_HPP


#include <limits>
#include <functional>

#include <Logic/Player.hpp>

/*-------------------------------------------------------------------------*//**
 * @brief      Pogo AI player that use the min-max algorithm with an alpha–beta
 *             pruning.
 *
 * @tparam     BoardType  Type of the board
 */
template<typename BoardType>
class AlphaBetaAIPlayer;

template<
	typename PawnStackType,
	unsigned int width,
	unsigned int height
>
class AlphaBetaAIPlayer<Board<PawnStackType, width, height>> : public Player<Board<PawnStackType, width, height>> {

	using BoardType = Board<PawnStackType, width, height>;

public:

	/*------------------------------------------------------------------------*//**
	 * @brief      Construct a new alpha-beta AI player.
	 *
	 * @param[in]  pawn   The pawn of the player, either PLAYER1_PAWN or
	 *                    PLAYER2_PAWN
	 * @param[in]  depth  The depth of the min-max
	 * @param[in]  eval   The evaluation function
	 */
	AlphaBetaAIPlayer(Pawn pawn, unsigned int depth, std::function<float(const BoardType, Pawn)> eval);

	/*------------------------------------------------------------------------*//**
	 * @brief      Choose a move to play.
	 *
	 * @param[in]  board  The board of the game
	 *
	 * @return     The move chosen by the player
	 */
	PawnsMove chooseMove(const BoardType& board) override;

	/*------------------------------------------------------------------------*//**
	 * @brief      Default destructor.
	 */
	~AlphaBetaAIPlayer() = default;

private:

	int manhattanDistance(int x1, int y1, int x2, int y2);

	float alphaBeta(const BoardType& board, unsigned int depth, float alpha, float beta, bool maximizing);

	unsigned int m_depth;

	std::function<float(const BoardType, Pawn)> m_eval;

};

template<typename PawnStackType, unsigned int width, unsigned int height>
AlphaBetaAIPlayer<Board<PawnStackType, width, height>>::AlphaBetaAIPlayer(Pawn pawn, unsigned int depth,
                                                                          std::function<float(const BoardType,
                                                                                              Pawn)> eval)
	: Player<BoardType>(pawn), m_depth(depth), m_eval(eval) {

}

template<typename PawnStackType, unsigned int width, unsigned int height>
PawnsMove AlphaBetaAIPlayer<Board<PawnStackType, width, height>>::chooseMove(const BoardType& board) {

	unsigned int depth = m_depth;
	float alpha = std::numeric_limits<float>::lowest();
	float beta = std::numeric_limits<float>::max();

	float val = std::numeric_limits<float>::lowest();
	PawnsMove move{};

	for(unsigned int x = 0; x < width; ++x) {
		for(unsigned int y = 0; y < height; ++y) {
			unsigned int stackSize = board[x][y].size();
			if(stackSize && board[x][y].get(stackSize - 1) == this->usedPawn) {
				for(unsigned int i = 0; i < width; ++i) {
					for(unsigned int j = 0; j < height; ++j) {
						int dist = manhattanDistance(x, y, i, j);
						float tmpVal = std::numeric_limits<float>::lowest();
						if(stackSize >= 3 && (dist == 3 || dist == 1)) {
							PawnsMove tmpMove{x, y, i, j, 3};
							tmpVal = std::max(tmpVal,
							                  alphaBeta(BoardType(board).apply(tmpMove), depth - 1, alpha, beta,
							                            false));
							alpha = std::max(alpha, val);
							if(tmpVal > val) {
								val = tmpVal;
								move = std::move(tmpMove);
							}
						}
						if(stackSize >= 2 && dist == 2) {
							PawnsMove tmpMove{x, y, i, j, 2};
							tmpVal = std::max(tmpVal,
							                  alphaBeta(BoardType(board).apply(tmpMove), depth - 1, alpha, beta,
							                            false));
							alpha = std::max(alpha, val);
							if(tmpVal > val) {
								val = tmpVal;
								move = std::move(tmpMove);
							}
						}
						if(dist == 1) {
							PawnsMove tmpMove{x, y, i, j, 1};
							tmpVal = std::max(tmpVal,
							                  alphaBeta(BoardType(board).apply(tmpMove), depth - 1, alpha, beta,
							                            false));
							alpha = std::max(alpha, val);
							if(tmpVal > val) {
								val = tmpVal;
								move = std::move(tmpMove);
							}
						}
					}
				}
			}
		}
	}
	return move;
}

template<typename PawnStackType, unsigned int width, unsigned int height>
int AlphaBetaAIPlayer<Board<PawnStackType, width, height>>::manhattanDistance(int x1, int y1, int x2, int y2) {
	return std::abs(x1 - x2) + std::abs(y1 - y2);

}

template<typename PawnStackType, unsigned int width, unsigned int height>
float AlphaBetaAIPlayer<Board<PawnStackType, width, height>>::alphaBeta(const BoardType& board, unsigned int depth,
                                                                        float alpha, float beta, bool maximizing) {
	if(depth == 0) { // Leaf
		return m_eval(board, this->usedPawn);
	}

	if(board.controlledStacks(!this->usedPawn) == 0){ // Victory
		return m_eval(board, this->usedPawn);
	}

	float val;
	if(maximizing) {
		val = std::numeric_limits<float>::lowest();
		for(unsigned int x = 0; x < width; ++x) {
			for(unsigned int y = 0; y < height; ++y) {
				unsigned int stackSize = board[x][y].size();
				if(stackSize && board[x][y].get(stackSize - 1) == this->usedPawn) {
					for(unsigned int i = 0; i < width; ++i) {
						for(unsigned int j = 0; j < height; ++j) {
							int dist = manhattanDistance(x, y, i, j);
							if(stackSize >= 3 && (dist == 3 || dist == 1)) {
								val = std::max(val,
								               alphaBeta(BoardType(board).apply(PawnsMove{x, y, i, j, 3}), depth - 1,
								                         alpha, beta, false));
								alpha = std::max(alpha, val);
							}
							if(stackSize >= 2 && dist == 2) {
								val = std::max(val,
								               alphaBeta(BoardType(board).apply(PawnsMove{x, y, i, j, 2}), depth - 1,
								                         alpha, beta, false));
								alpha = std::max(alpha, val);
							}
							if(dist == 1) {
								val = std::max(val,
								               alphaBeta(BoardType(board).apply(PawnsMove{x, y, i, j, 1}), depth - 1,
								                         alpha, beta, false));
								alpha = std::max(alpha, val);
							}
							if(beta < alpha) {
								return val; // beta cut-off
							}
						}
					}
				}
			}
		}
	}
	else { // !maximizing
		val = std::numeric_limits<float>::max();
		for(unsigned int x = 0; x < width; ++x) {
			for(unsigned int y = 0; y < height; ++y) {
				unsigned int stackSize = board[x][y].size();
				if(stackSize && board[x][y].get(stackSize - 1) == this->usedPawn) {
					for(unsigned int i = 0; i < width; ++i) {
						for(unsigned int j = 0; j < height; ++j) {
							int dist = manhattanDistance(x, y, i, j);
							if(stackSize >= 3 && (dist == 3 || dist == 1)) {
								val = std::min(val,
								               alphaBeta(BoardType(board).apply(PawnsMove{x, y, i, j, 3}), depth - 1,
								                         alpha, beta, true));
								beta = std::min(beta, val);
							}
							if(stackSize >= 2 && dist == 2) {
								val = std::min(val,
								               alphaBeta(BoardType(board).apply(PawnsMove{x, y, i, j, 2}), depth - 1,
								                         alpha, beta, true));
								beta = std::min(beta, val);
							}
							if(dist == 1) {
								val = std::min(val,
								               alphaBeta(BoardType(board).apply(PawnsMove{x, y, i, j, 1}), depth - 1,
								                         alpha, beta, true));
								beta = std::min(beta, val);
							}
							if(beta < alpha) {
								return val; // alpha cut-off
							}
						}
					}
				}
			}
		}
	}
	return val;
}


#endif //UTBM_IA41_POGO_ALPHABETAAIPLAYER_HPP
