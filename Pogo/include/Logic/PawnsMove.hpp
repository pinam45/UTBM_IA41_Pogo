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
 * @file PawnMove.hpp
 * @brief      Definition of the PawnMove struct.
 * @author     Maxime Pinard
 * @date       12/04/17
 * @version    0.0
 */

#ifndef UTBM_IA41_POGO_PAWNMOVE_HPP
#define UTBM_IA41_POGO_PAWNMOVE_HPP


/*-------------------------------------------------------------------------*//**
 * @struct PawnMove
 *
 * @brief      Represent a pawns move on a board.
 */
struct PawnsMove {
	unsigned int fromX; /**< X coordinate of the stack where the pawns come from **/
	unsigned int fromY; /**< Y coordinate of the stack where the pawns come from **/
	unsigned int toX; /**< X coordinate of the stack where the pawns go to **/
	unsigned int toY; /**< Y coordinate of the stack where the pawns go to **/
	unsigned int pawnNumber; /**< Number of pawns moved **/
};


#endif //UTBM_IA41_POGO_PAWNMOVE_HPP
