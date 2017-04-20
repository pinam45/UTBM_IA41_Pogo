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
 * @file ConsoleUI.hpp
 * @brief      Definition of the ConsoleUI class.
 * @author     Maxime Pinard
 * @date       13/04/17
 * @version    0.0
 */

#ifndef UTBM_IA41_POGO_CONSOLEUI_HPP
#define UTBM_IA41_POGO_CONSOLEUI_HPP


#include <iostream>

#include <ConsoleControl.h>
#include <ConsoleControlInput.h>
#include <ConsoleControlUtility.h>

#include <UI/UI.hpp>

/*-------------------------------------------------------------------------*//**
 * @brief      Console User Interface, console interface with the user for
 *             playing the Pogo game.
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
class ConsoleUI : public UI<PawnStackType, width, height> {

public:

	/*------------------------------------------------------------------------*//**
	 * @brief      Constructor, compute board elements positions.
	 */
	ConsoleUI();


	/*------------------------------------------------------------------------*//**
	 * @brief      Display the board.
	 *
	 * @param[in]  board  The board
	 */
	void displayBoard(const Board<PawnStackType, width, height>& board) override;

	/*------------------------------------------------------------------------*//**
	 * @brief      Allow the user to choose a move.
	 *
	 * @param[in]  board   The board
	 * @param[in]  player  The player
	 *
	 * @return     A valid Pogo move for the board.
	 */
	PawnsMove chooseMove(const Board<PawnStackType, width, height>& board, Pawn player) override;

	/*------------------------------------------------------------------------*//**
	 * @brief      Display the victory screen.
	 *
	 * @param[in]  player  The player who won the game
	 */
	void displayVictory(Pawn player) override;

private:

	enum PawnStackState {
		VALID,
		NONVALID,
		UNDEFINED
	};

	struct PawnStackInfo {
		PawnStackState state = UNDEFINED;
		cc_Vector2 frameTopLeft = {0, 0};
		cc_Vector2 frameDownRight = {0, 0};
		cc_Vector2 stackDownLeft = {0, 0};
		bool selected = false;
		unsigned int pawnSelected = 0;
	};

	cc_Vector2 selectFrame(cc_Vector2 initialSelection);

	unsigned int selectPawnsNumber(cc_Vector2 stackPosition, PawnStackType pawnStack);

	void setValidStacks(const Board<PawnStackType, width, height>& board, bool player);

	void setValidMoveStacks(cc_Vector2 fromStackPosition, unsigned int takenPawns);

	void addValidMoveStacks(cc_Vector2 fromStackPosition, unsigned int takenPawns);

	void setUndefinedStacks();

	void drawPawnStack(ConsoleUI::PawnStackInfo info, PawnStackType pawnStack);

	void drawSelectedPawnStack(ConsoleUI::PawnStackInfo info, PawnStackType pawnStack, unsigned int takenPawns);

	void drawSelectedFrame(ConsoleUI::PawnStackInfo stackInfo);

	void drawFrame(ConsoleUI::PawnStackInfo stackInfo);

	void computePositions();

	const unsigned int m_maxTakenPawns = 3;

	const cc_Color m_backgroundColor = WHITE;

	const cc_Color m_boardBackgroundColor = BLUE;
	const cc_Color m_boardForegroundColor = BLUE;
	const char m_boardChar = ' ';

	const cc_Color m_squaresBackgroundColor = BLACK;

	const cc_Color m_selectionFrameForegroundColor = WHITE;

	const cc_Color m_selectedFrameBackgroundColor = YELLOW;
	const cc_Color m_validFrameBackgroundColor = GREEN;
	const cc_Color m_nonvalidFrameBackgroundColor = BLUE;

	const cc_Color m_selectedPawnsBackgroundColor = YELLOW;
	const cc_Color m_selectedPawnsForegroundColor = BLACK;

	const cc_Color m_p1PawnsBackgroundColor = MAGENTA;
	const cc_Color m_p1PawnsForegroundColor = WHITE;
	const char m_p1PawnsChar = '_';

	const cc_Color m_p2PawnsBackgroundColor = CYAN;
	const cc_Color m_p2PawnsForegroundColor = WHITE;
	const char m_p2PawnsChar = '_';

	const unsigned int m_pawnStackMaxSize = PawnStackType::max_size();
	const unsigned int m_boardWidth = width * m_pawnStackMaxSize * 2 + 2 * (width + 1);
	const unsigned int m_boardHeight = height * m_pawnStackMaxSize + 2 * (height + 1);
	const unsigned int m_squareWidth = m_pawnStackMaxSize * 2;
	const unsigned int m_squareHeight = m_pawnStackMaxSize;

	cc_Vector2 m_boardTopLeft; // computed in computePositions()

	PawnStackInfo m_pawnStackInfo[width][height]; // computed in computePositions()

};

template<typename PawnStackType, unsigned int width, unsigned int height, typename check>
ConsoleUI<PawnStackType, width, height, check>::ConsoleUI() : m_boardTopLeft() {
	computePositions();
}

template<typename PawnStackType, unsigned int width, unsigned int height, typename check>
void ConsoleUI<PawnStackType, width, height, check>::displayBoard(const Board<PawnStackType, width, height>& board) {
	cc_clean();
	while(static_cast<unsigned int>(cc_getWidth()) < m_boardWidth
	      || static_cast<unsigned int>(cc_getHeight()) < m_boardHeight) {
		cc_Vector2 nullPos = {0, 0};
		cc_setCursorPosition(nullPos);
		std::cout << "Console not big enough to display the board" << std::flush; //TODO: better message
		cc_getInput();
		computePositions();
	}

	cc_Vector2 boardDownRight = {
		static_cast<cc_type>(m_boardTopLeft.x + m_boardWidth - 1),
		static_cast<cc_type>(m_boardTopLeft.y + m_boardHeight - 1)
	};
	cc_setBackgroundColor(m_backgroundColor);
	cc_clean();
	cc_setColors(m_boardBackgroundColor, m_boardForegroundColor);
	cc_drawRectangle(m_boardTopLeft, boardDownRight, m_boardChar);

	for(unsigned int i = width; i--;) {
		for(unsigned int j = height; j--;) {
			drawFrame(m_pawnStackInfo[i][j]);
		}
	}

	for(unsigned int i = width; i--;) {
		for(unsigned int j = height; j--;) {
			drawPawnStack(m_pawnStackInfo[i][j], board[i][j]);
		}
	}
}

template<typename PawnStackType, unsigned int width, unsigned int height, typename check>
PawnsMove ConsoleUI<PawnStackType, width, height, check>::chooseMove(const Board<PawnStackType, width, height>& board,
                                                                     bool player) {
	for(unsigned int i = width; i--;) {
		for(unsigned int j = height; j--;) {
			m_pawnStackInfo[i][j].selected = false;
		}
	}
	setValidStacks(board, player);
	displayBoard(board);

	cc_Vector2 selectedFrame = {0, 0};
	selectedFrame = selectFrame(selectedFrame);
	PawnsMove move;
	move.fromX = static_cast<unsigned int>(selectedFrame.x);
	move.fromY = static_cast<unsigned int>(selectedFrame.y);

	setUndefinedStacks();
	move.pawnNumber = selectPawnsNumber(selectedFrame, board[selectedFrame.x][selectedFrame.y]);

	setValidMoveStacks(selectedFrame, move.pawnNumber);
	m_pawnStackInfo[selectedFrame.x][selectedFrame.y].state = UNDEFINED;
	for(unsigned int i = width; i--;) {
		for(unsigned int j = height; j--;) {
			drawFrame(m_pawnStackInfo[i][j]);
		}
	}

	selectedFrame = selectFrame(selectedFrame);
	move.toX = static_cast<unsigned int>(selectedFrame.x);
	move.toY = static_cast<unsigned int>(selectedFrame.y);

	setUndefinedStacks();
	for(unsigned int i = width; i--;) {
		for(unsigned int j = height; j--;) {
			m_pawnStackInfo[i][j].selected = false;
		}
	}
	return move;
}

template<typename PawnStackType, unsigned int width, unsigned int height, typename check>
void ConsoleUI<PawnStackType, width, height, check>::displayVictory(Pawn player) {
	cc_setColors(BLACK,WHITE);
	cc_clean();
	cc_Vector2 nullPos = {0, 0};
	cc_setCursorPosition(nullPos);
	std::cout << "Player " << player << " win the game." << std::flush; //TODO: better message
	cc_getInput();
}

template<typename PawnStackType, unsigned int width, unsigned int height, typename check>
cc_Vector2 ConsoleUI<PawnStackType, width, height, check>::selectFrame(cc_Vector2 initialSelection) {
	cc_Vector2 selection = initialSelection;
	cc_Vector2 oldSelection = selection;

	drawSelectedFrame(m_pawnStackInfo[selection.x][selection.y]);

	bool ended = false;
	cc_Input input;
	while(!ended) {
		input = cc_getInput();
		switch(input.key) {
			case HOME_KEY:
				selection.x = 0;
				break;
			case END_KEY:
				selection.x = width - 1;
				break;
			case PAGE_UP_KEY:
				selection.y = 0;
				break;
			case PAGE_DOWN_KEY:
				selection.y = height - 1;
				break;
			case UP_ARROW_KEY:
				if(selection.y) {
					--selection.y;
				}
				break;
			case DOWN_ARROW_KEY:
				if(static_cast<unsigned int>(selection.y) < height - 1) {
					++selection.y;
				}
				break;
			case LEFT_ARROW_KEY:
				if(selection.x) {
					--selection.x;
				}
				break;
			case RIGHT_ARROW_KEY:
				if(static_cast<unsigned int>(selection.x) < width - 1) {
					++selection.x;
				}
				break;
			case ENTER_KEY:
				if(m_pawnStackInfo[selection.x][selection.y].state == PawnStackState::VALID) {
					m_pawnStackInfo[selection.x][selection.y].selected = true;
					ended = true;
				}
			case BACKSPACE_KEY:
			case TAB_KEY:
			case ESC_KEY:
			case SPACE_KEY:
			case INS_KEY:
			case DEL_KEY:
			case F1_KEY:
			case F2_KEY:
			case F3_KEY:
			case F4_KEY:
			case F5_KEY:
			case F6_KEY:
			case F7_KEY:
			case F8_KEY:
			case F9_KEY:
			case F10_KEY:
			case F11_KEY:
			case F12_KEY:
			case OTHER_KEY:
			default:
				break;
		}
		cc_setColors(m_boardBackgroundColor, m_boardForegroundColor);
		drawFrame(m_pawnStackInfo[oldSelection.x][oldSelection.y]);
		drawSelectedFrame(m_pawnStackInfo[selection.x][selection.y]);
		oldSelection = selection;
	}
	return selection;
}

template<typename PawnStackType, unsigned int width, unsigned int height, typename check>
unsigned int ConsoleUI<PawnStackType, width, height, check>::selectPawnsNumber(cc_Vector2 stackPosition,
                                                                               PawnStackType pawnStack) {

	ConsoleUI::PawnStackInfo info = m_pawnStackInfo[stackPosition.x][stackPosition.y];

	unsigned int pawnStackSize = pawnStack.size();
	unsigned int takenPawns = 1;

	drawSelectedPawnStack(info, pawnStack, takenPawns);
	setValidMoveStacks(stackPosition, takenPawns);
	for(unsigned int i = width; i--;) {
		for(unsigned int j = height; j--;) {
			drawFrame(m_pawnStackInfo[i][j]);
		}
	}
	cc_Input input = {OTHER_KEY, 0};
	while(input.key != ENTER_KEY) {
		input = cc_getInput();
		switch(input.key) {
			case UP_ARROW_KEY:
				if(takenPawns > 1) {
					--takenPawns;
				}
				break;
			case DOWN_ARROW_KEY:
				if(takenPawns < m_maxTakenPawns && takenPawns < pawnStackSize) {
					++takenPawns;
				}
				break;
			case OTHER_KEY:
				if(input.ch == '+') {
					if(takenPawns < m_maxTakenPawns) {
						++takenPawns;
					}
				}
				else if(input.ch == '-') {
					if(takenPawns > 1) {
						--takenPawns;
					}
				}
				else if(input.ch > '0' && input.ch < static_cast<unsigned char>('0' + m_maxTakenPawns)) {
					takenPawns = static_cast<unsigned int>(input.ch - '0');
				}
				break;
			case HOME_KEY:
			case END_KEY:
			case PAGE_UP_KEY:
			case PAGE_DOWN_KEY:
			case LEFT_ARROW_KEY:
			case RIGHT_ARROW_KEY:
			case BACKSPACE_KEY:
			case TAB_KEY:
			case ENTER_KEY:
			case ESC_KEY:
			case SPACE_KEY:
			case INS_KEY:
			case DEL_KEY:
			case F1_KEY:
			case F2_KEY:
			case F3_KEY:
			case F4_KEY:
			case F5_KEY:
			case F6_KEY:
			case F7_KEY:
			case F8_KEY:
			case F9_KEY:
			case F10_KEY:
			case F11_KEY:
			case F12_KEY:
			default:
				break;
		}
		drawSelectedPawnStack(info, pawnStack, takenPawns);
		setValidMoveStacks(stackPosition, takenPawns);
		for(unsigned int i = width; i--;) {
			for(unsigned int j = height; j--;) {
				drawFrame(m_pawnStackInfo[i][j]);
			}
		}
	}
	return takenPawns;
}

template<typename PawnStackType, unsigned int width, unsigned int height, typename check>
void ConsoleUI<PawnStackType, width, height, check>::setValidStacks(const Board<PawnStackType, width, height>& board,
                                                                    bool player) {
	for(unsigned int i = width; i--;) {
		for(unsigned int j = height; j--;) {
			if(board[i][j].size() > 0 && board[i][j][board[i][j].size() - 1] == player) {
				m_pawnStackInfo[i][j].state = PawnStackState::VALID;
			}
			else {
				m_pawnStackInfo[i][j].state = PawnStackState::NONVALID;
			}
		}
	}
}

template<typename PawnStackType, unsigned int width, unsigned int height, typename check>
void ConsoleUI<PawnStackType, width, height, check>::setValidMoveStacks(cc_Vector2 fromStackPosition,
                                                                        unsigned int takenPawns) {
	for(unsigned int i = width; i--;) {
		for(unsigned int j = height; j--;) {
			m_pawnStackInfo[i][j].state = NONVALID;
		}
	}
	addValidMoveStacks(fromStackPosition, takenPawns);
}

template<typename PawnStackType, unsigned int width, unsigned int height, typename check>
void ConsoleUI<PawnStackType, width, height, check>::addValidMoveStacks(cc_Vector2 fromStackPosition,
                                                                        unsigned int takenPawns) {
	cc_Vector2 pos;
	if(takenPawns == 1) {
		pos.y = fromStackPosition.y;
		if(fromStackPosition.x > 0) {
			pos.x = fromStackPosition.x - 1;
			m_pawnStackInfo[pos.x][pos.y].state = VALID;
		}
		if(fromStackPosition.x < static_cast<int>(width - 1)) {
			pos.x = fromStackPosition.x + 1;
			m_pawnStackInfo[pos.x][pos.y].state = VALID;
		}
		pos.x = fromStackPosition.x;
		if(fromStackPosition.y > 0) {
			pos.y = fromStackPosition.y - 1;
			m_pawnStackInfo[pos.x][pos.y].state = VALID;
		}
		if(fromStackPosition.y < static_cast<int>(height - 1)) {
			pos.y = fromStackPosition.y + 1;
			m_pawnStackInfo[pos.x][pos.y].state = VALID;
		}
	}
	else if(takenPawns > 1) {
		--takenPawns;
		pos.y = fromStackPosition.y;
		if(fromStackPosition.x > 0) {
			pos.x = fromStackPosition.x - 1;
			addValidMoveStacks(pos, takenPawns);
		}
		if(fromStackPosition.x < static_cast<int>(width - 1)) {
			pos.x = fromStackPosition.x + 1;
			addValidMoveStacks(pos, takenPawns);
		}
		pos.x = fromStackPosition.x;
		if(fromStackPosition.y > 0) {
			pos.y = fromStackPosition.y - 1;
			addValidMoveStacks(pos, takenPawns);
		}
		if(fromStackPosition.y < static_cast<int>(height - 1)) {
			pos.y = fromStackPosition.y + 1;
			addValidMoveStacks(pos, takenPawns);
		}
	}
}

template<typename PawnStackType, unsigned int width, unsigned int height, typename check>
void ConsoleUI<PawnStackType, width, height, check>::setUndefinedStacks() {
	for(unsigned int i = width; i--;) {
		for(unsigned int j = height; j--;) {
			m_pawnStackInfo[i][j].state = PawnStackState::UNDEFINED;
		}
	}
}

template<typename PawnStackType, unsigned int width, unsigned int height, typename check>
void
ConsoleUI<PawnStackType, width, height, check>::drawPawnStack(ConsoleUI::PawnStackInfo info, PawnStackType pawnStack) {
	cc_Vector2 downLeft = info.stackDownLeft;
	cc_Vector2 downRight = {
		static_cast<cc_type>(downLeft.x + PawnStackType::max_size() * 2 - 1),
		downLeft.y
	};
	unsigned int i = 0;
	for(; i < pawnStack.size(); ++i) {
		if(pawnStack[i] == PLAYER1_PAWN) {
			cc_setColors(m_p1PawnsBackgroundColor, m_p1PawnsForegroundColor);
			cc_drawLine(downLeft, downRight, m_p1PawnsChar);
		}
		else {
			cc_setColors(m_p2PawnsBackgroundColor, m_p2PawnsForegroundColor);
			cc_drawLine(downLeft, downRight, m_p2PawnsChar);
		}
		--downLeft.y;
		--downRight.y;
	}
	cc_setColors(m_squaresBackgroundColor, m_squaresBackgroundColor);
	for(; i < m_pawnStackMaxSize; ++i) {
		cc_drawLine(downLeft, downRight, ' ');
		--downLeft.y;
		--downRight.y;
	}
}

template<typename PawnStackType, unsigned int width, unsigned int height, typename check>
void ConsoleUI<PawnStackType, width, height, check>::drawSelectedPawnStack(ConsoleUI::PawnStackInfo info,
                                                                           PawnStackType pawnStack,
                                                                           unsigned int takenPawns) {
	drawPawnStack(info, pawnStack);

	cc_Vector2 stackTopLeft{
		info.stackDownLeft.x,
		static_cast<cc_type>(info.stackDownLeft.y - pawnStack.size() + 1)
	};

	cc_Vector2 stackTopRight{
		static_cast<cc_type>(stackTopLeft.x + m_pawnStackMaxSize * 2 - 2),
		stackTopLeft.y
	};

	cc_setColors(m_selectedPawnsBackgroundColor, m_selectedPawnsForegroundColor);
	cc_Vector2 posLeft;
	posLeft.x = stackTopLeft.x;
	cc_Vector2 posRight;
	posRight.x = stackTopRight.x;
	for(unsigned int i = takenPawns; --i;) {

		posLeft.y = stackTopLeft.y + i;
		cc_setCursorPosition(posLeft);
		std::cout << "--" << std::flush;

		posRight.y = stackTopRight.y + i;
		cc_setCursorPosition(posRight);
		std::cout << "--" << std::flush;
	}
	cc_setCursorPosition(stackTopLeft);
	std::cout << "--" << std::flush;

	cc_setCursorPosition(stackTopRight);
	std::cout << "--" << std::flush;

	posLeft.y = stackTopLeft.y + takenPawns - 1;
	cc_setCursorPosition(posLeft);
	std::cout << "->" << std::flush;

	posRight.y = stackTopRight.y + takenPawns - 1;
	cc_setCursorPosition(posRight);
	std::cout << "<-" << std::flush;
}

template<typename PawnStackType, unsigned int width, unsigned int height, typename check>
void ConsoleUI<PawnStackType, width, height, check>::drawSelectedFrame(ConsoleUI::PawnStackInfo stackInfo) {

	if(stackInfo.selected) {
		cc_setBackgroundColor(m_selectedFrameBackgroundColor);
	}
	else {
		switch(stackInfo.state) {
			case VALID:
				cc_setBackgroundColor(m_validFrameBackgroundColor);
				break;
			case NONVALID:
				cc_setBackgroundColor(m_nonvalidFrameBackgroundColor);
				break;
			case UNDEFINED:
				/* FALLTHROUGH */
			default:
				cc_setBackgroundColor(m_boardBackgroundColor);
				break;
		}
	}
	cc_setForegroundColor(m_selectionFrameForegroundColor);
	cc_drawTableRectangle(stackInfo.frameTopLeft, stackInfo.frameDownRight);
}

template<typename PawnStackType, unsigned int width, unsigned int height, typename check>
void ConsoleUI<PawnStackType, width, height, check>::drawFrame(ConsoleUI::PawnStackInfo stackInfo) {

	if(stackInfo.selected) {
		cc_setBackgroundColor(m_selectedFrameBackgroundColor);
	}
	else {
		switch(stackInfo.state) {
			case VALID:
				cc_setBackgroundColor(m_validFrameBackgroundColor);
				break;
			case NONVALID:
				cc_setBackgroundColor(m_nonvalidFrameBackgroundColor);
				break;
			case UNDEFINED:
				/* FALLTHROUGH */
			default:
				cc_setBackgroundColor(m_boardBackgroundColor);
				break;
		}
	}
	cc_setForegroundColor(m_boardForegroundColor);
	cc_drawRectangle(stackInfo.frameTopLeft, stackInfo.frameDownRight, m_boardChar);
}

template<typename PawnStackType, unsigned int width, unsigned int height, typename check>
void ConsoleUI<PawnStackType, width, height, check>::computePositions() {

	m_boardTopLeft.x = (cc_getWidth() - m_boardWidth) / 2;
	m_boardTopLeft.y = (cc_getHeight() - m_boardHeight) / 2;

	cc_Vector2 frameTopLeft = {0, 0};
	cc_Vector2 frameDownRight = {0, 0};
	cc_Vector2 stackDownLeft = {0, 0};
	for(unsigned int i = width; i--;) {
		for(unsigned int j = height; j--;) {
			frameTopLeft.x = m_boardTopLeft.x + 1 + (m_squareWidth + 2) * i;
			frameTopLeft.y = m_boardTopLeft.y + 1 + (m_squareHeight + 2) * j;
			m_pawnStackInfo[i][j].frameTopLeft = frameTopLeft;
			frameDownRight.x = frameTopLeft.x + m_pawnStackMaxSize * 2 + 1;
			frameDownRight.y = frameTopLeft.y + m_pawnStackMaxSize + 1;
			m_pawnStackInfo[i][j].frameDownRight = frameDownRight;
			stackDownLeft.x = frameTopLeft.x + 1;
			stackDownLeft.y = frameDownRight.y - 1;
			m_pawnStackInfo[i][j].stackDownLeft = stackDownLeft;
		}
	}
}


#endif //UTBM_IA41_POGO_CONSOLEUI_HPP
