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

#include <cassert>
#include <cstdlib>
#include <vector>
#include <iostream>

#ifndef BOARD_H
#define BOARD_H

class board;
class line;

/*! \brief The board on which 2048 is played.
 *
 *  This is the board on which 2048 is played and on which all game actions
 *  take place.
 */
class board
{
private:
    unsigned size; /*!< The number of rows and columns. */
    std::vector< std::vector<unsigned> > values; /*!< Values of all cells on the Board. First index: rows, second index: columns. */
public:
    void draw(); /*!< Draw the board to STDOUT. */
    board(const unsigned size); /*!< Constructor for board. */
    ~board(); /*!< Destructor for board. */
    line getRow(const unsigned rowNum) const; /*!< Get a single row from the board. */
    line getCol(const unsigned colNum) const; /*!< Get a single column from the board. */
    void setRow(const line & row); /*!< Set a single column on the board. */
    void setCol(const line & col); /*!< Set a single column on the board. */
};

enum { row = true, col = false }; /*!< Enum used to determine whether a line is a row or a column. */

/*! \brief A line of cells on the 2048 board.
 *
 *  This is the board on which 2048 is played and on which all game actions
 *  take place.
 */
class line
{
private:
    unsigned size; /*!< The number of cells in the line. */
    bool rowOrCol; /*!< Whether the line is a row or a column. Row is true, column is false. */
    std::vector<unsigned> values; /*!< The values in the line */
public:
    line(const unsigned & size,const bool & rowOrCol,const std::vector<unsigned> & values); /*!< Constructor for line. */
    line& operator = (const line& right); /*!< Constructor for line. */
    line operator+(const line& right); /*!< Destructor for line. */
    bool isRow(); /*!< Check whether line is a row. */
    bool isCol(); /*!< Check whether line is a column. */
    unsigned getValue(unsigned num); /*!< Get value of cell number num starting from below/left. */
    ~line(); /*!< Destructor for line. */
};

#endif // BOARD_H
