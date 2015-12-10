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
#include <random>
#include "helper.h"

class board;

/*! \brief Enum used to determine whether a line is a row or a column.
 * 
 */
enum { row = true, col = false };

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

    /*! \brief Set all cells to 0.
     * 
     *  Set all cells to 0.
     * 
     */
    void zero();

    /*! \brief Add 2 or 4 to some random empty cell.
     * 
     *  Add 2 or 4 to some random empty cell.
     * 
     * \param mt The Mersenne-Twister random number generator.
     * \return Whether there was still space to add the new value, i.e. if the game is over (false).
     * 
     */
    bool addRandomValue(std::mt19937& mt);

    /*! \brief Make a game move.
     * 
     *  Make a game move: move cell lines and update the board and the score.
     * 
     * \param direction The direction in which to move the cells.
     * \param score The score that needs updating.
     * \return The state of the game.
     * 
     */
    gameState_t move(const char direction,unsigned& score);
    
    /*! \brief Make a new board.
     * 
     *  Constructor for a board of a certain size.
     * 
     * \param size The number of rows and columns on the board.
     * 
     */
    board(const unsigned int size);
    
    ~board(); /*!< Destructor that deletes the board object. */
    
    /*! \brief Get coordinates of empty cells.
     * 
     *  Find all empty cells and return their x,y-indices as std::tuple<unsigned,unsigned>.
     *  \return A list of x,y-indices of empty cells.
     * 
     */    
    std::vector<std::tuple<unsigned,unsigned> > getEmptyCells();

    /*! \brief Fill a line on the board in a given direction.
     * 
     *  Fill a line on the board in a given direction. For testing/debuuging.
     *  \param direction The direction in which to fill in the values.
     *  \param fillVector The values to write to the board.
     *  \param lineNumber The index of the row/column to write.
     * 
     */    
    void fillLine(const char direction, const std::vector<unsigned> fillVector, const unsigned lineNumber);

    /*! \brief Set board values.
     * 
     *  Used to set the board values. For testing/debuuging.
     * 
     *  \param newValues The new board values.
     */    
    void setBoardValues(const std::vector< std::vector<unsigned> > newValues);
    
    /*! \brief Get board values.
     * 
     *  Used to get the board values. For testing/debuuging.
     * 
     *  \return The current board values.
     */    
    std::vector<std::vector<unsigned> > getBoardValues();

    /*! \brief Overloaded function call operator for matrix element access.
     * 
     *  Overloaded function call operator for matrix element access allows simple idiomatic
     *  access to board matrix elements via (*this)(X,Y) in member function and [board instance](X,Y)
     *  otherwise.
     * 
     *  \param row The number of the row (X) to access.
     *  \param col The number of the column (Y) to access.
     *  \return The address of a board matrix element.
     * 
     */    
    unsigned& operator()(const unsigned row,const unsigned col);
    
};

#endif // BOARD_H
