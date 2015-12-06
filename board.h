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

/*!\file board.h 
 * \brief File contains the definition of classes and functions for drawing and 
 * using the 2048 board.
 * 
 */

#ifndef BOARD_H
#define BOARD_H

#include <cassert>
#include <vector>
#include <iostream>
#include "helper.h"

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
    /*! \brief Draw the board.
     * 
     *  Draw the board to STDOUT.
     * 
     */
    void draw();
    
    /*! \brief Make a new board.
     * 
     *  Constructor for a board of a certain size.
     * 
     *  \param size The number of rows and columns on the board.
     *  \param startValue The start value placed on an arbitrary cell on the board at the start of the game.
     *  \param startValueRow The row number of the start value. 
     *  \param startValueCol The column number of the start value.
     * 
     */
    board(const unsigned size, const unsigned startValue, const unsigned startValueRow, const unsigned startValueCol);
    
    ~board(); /*!< Destructor that deletes the board object. */
    
    /*! \brief Get a row.
     * 
     *  Get a row from a position on the board.
     * 
     *  \param rowNum The position of the row that should be returned.
     *  \return A line object representing the row.
     */
    line getRow(const unsigned rowNum) const;
    
    /*! \brief Get a column.
     * 
     *  Get a column from a position on the board.
     * 
     *  \param colNum The position of the column that should be returned.
     *  \return A line object representing the column.
     */
    line getCol(const unsigned colNum) const; /*!< Get a single column from the board. */
    
    /*! \brief Set a row.
     * 
     *  Set a row on a position on the board.
     * 
     *  \param rowToSet The line object with the cells that should be written to the board.
     *  \param rowNum The position of the row that should be returned.
     */
    void setRow(const line & rowToSet,const unsigned rowNum);
    
    /*! \brief Set a column.
     * 
     *  Set a column on a position on the board.
     * 
     *  \param colToSet The line object with the cells that should be written to the board.
     *  \param colNum The position of the column that should be returned.
     */
    void setCol(const line & colToSet,const unsigned colNum);
};

/*! \brief Enum used to determine whether a line is a row or a column.
 *
 */
enum { row = true, col = false };

/*! \brief A line of cells on the 2048 board.
 *
 *  This is the board on which 2048 is played and on which all game actions
 *  take place.
 */
class line
{
    friend class board;
private:
    unsigned size; /*!< The number of cells in the line. */
    bool rowOrCol; /*!< Whether the line is a row or a column. Row is true, column is false. */
    std::vector<unsigned> values; /*!< The values in the line */
public:
 
    /*! \brief Constructor for line.
     * 
     *  Create a line (i.e. a row or a column) with a certain number of elements with predefined values.
     *
     *  \param size Target width of the string.
     *  \param rowOrCol Whether the line is a row or a column. Row is true, column is false.
     *  \param values The values of the cells in the line.
     */
    line(const unsigned & size,const bool & rowOrCol,const std::vector<unsigned> & values);

    /*! \brief Set one line equal to another.
     * 
     *  \param right The line on the right side of the "+" sign.
     *  \return The address of the new line.
     */
    line& operator = (const line& right);

    line operator+(const line& right); /*!< Add two lines. Beware: Does not commute! */

    /*! \brief Check whether a line is a row.
     * 
     *  \return True if it is a row, false otherwise.
     */
    bool isRow();

    /*! \brief Check whether a line is a column.
     * 
     *  \return True if it is a column, false otherwise.
     */
    bool isCol();

    /*! \brief Get a value on the line.
     * 
     *  Get the value of the cell at position num in the line.
     *
     *  \param num The position of the cell whose value should be returned.
     *  \return The values of the cell.
     */
    unsigned getValue(const unsigned num); /*!< Get value of cell number num starting from below/left. */

    void print(); /*!< Print line to STDOUT (for debugging). */

    ~line(); /*!< Destructor for line. */
};

#endif // BOARD_H
