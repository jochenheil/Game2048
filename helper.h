/*
 * Copyright (c) 2015, Jochen Heil
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY Jochen Heil ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Jochen Heil BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*!\file helper.h 
 * \brief File contains the definitions of helper functions for the 2048 game.
 */


#ifndef HELPER_H
#define HELPER_H

#include <random>
#include <algorithm>
#include <cassert>

/*! \brief Idiomatic directions/keys.
 * 
 */
enum { UP = 'w', DOWN = 's', LEFT = 'a', RIGHT = 'D', QUIT = 'q' };

/*! \brief Generate a new cell value for 2048.
 * 
 *  This is used to generate a new cell value for 2048 using a
 *  Mersenne-Twister pseudo-random number generator. The number
 *  should be either 2 (90 % probability) or 4 (10 % probability).
 *
 *  \param mt The Mersenne-Twister RNG.
 *  \return The random number (2 or 4).
 */
unsigned generateCellValue(std::mt19937& mt);

/*! \brief Center a number inside a string.
 * 
 *  This is used to center the number inside a cell on the board on which 2048 is played.
 *
 *  \param width Target width of the string.
 *  \param inputNumber The number to convert to a centered string.
 *  \return A centered string containing inputNumber.
 */
std::string centerNumberstring(const unsigned width,const unsigned inputNumber);

#endif // HELPER_H