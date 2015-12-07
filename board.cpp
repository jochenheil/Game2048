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

/*!\file board.cpp
 * \brief File contains the implementation of classes and functions for drawing 
 * and using the 2048 board.
 * 
 */

#include "board.h"
#include "helper.h"

board::board(const unsigned size)
{
    this->size = size;

    // Initialize board with all cells = 0.
    this->values.resize(this->size);
    this->zero();
}

board::~board()
{
}

void board::zero()
{
    for(unsigned i = 0; i < this->size; ++i) {
        this->values.at(i).resize(this->size);
        for(unsigned j = 0; j < this->size; ++j) {
            this->values.at(i).at(j) = 0;
        }
    }
}

std::vector< std::tuple<unsigned,unsigned> > board::getEmptyCells()
{
    std::vector<std::tuple<unsigned,unsigned> > emptyCells;
    for(unsigned i = 0; i < this->size; ++i) {
        for(unsigned j = 0; j < this->size; ++j) {
            if(this->values.at(i).at(j) == 0) emptyCells.push_back(std::tuple<unsigned,unsigned>(i,j));
        }
    }
    return emptyCells;
}

bool board::addRandomValue(std::mt19937& mt)
{
   
    // Get a list of all empty cell x,y-indices.
    std::vector<std::tuple<unsigned,unsigned> > emptyCells = getEmptyCells();

    if(emptyCells.size() == 0) {
        // If all cells are full, return false.
        return false;
    }
    else {
        // If at least one cell is empty...
        
        // ...generate a random number {2,4}...
        unsigned newValue = generateCellValue(mt);

        // ...get a random empty cell...
        std::uniform_int_distribution<unsigned> randomCellDist(0,emptyCells.size()-1);
        unsigned randomCellNum = randomCellDist(mt);
        std::tuple<unsigned,unsigned> cellToModifyId = emptyCells.at(randomCellNum);
        
        // ...and assign the new value.
        unsigned rowId = std::get<0>(cellToModifyId);
        unsigned colId = std::get<1>(cellToModifyId);
        this->values.at(rowId).at(colId) = newValue;

        return true;
    }
}

bool board::move(const char direction,unsigned& score)
{
    bool changeACell;
    switch(direction){
        case UP:
            // Iterate over all rows.
            for(unsigned i = 0; i < this->size; ++i) {
                // Repeat to self-consistency:
                // First move then add.
                do {
                    changeACell = false;
                    // If cell on the left (j-1) is zero, move current cell one left.
                    for(unsigned j = 1; j < this->size; ++j) {
                        if((*this)(i,j-1) == 0 && (*this)(i,j) != 0) {
                            (*this)(i,j-1) = (*this)(i,j);
                            (*this)(i,j) = 0;
                            changeACell = true;
                        }
                    }
                    // If cell on the right (j+1) is the same as the one on the left, multiply left by two and set right (j) to zero.
                    for(unsigned j = 0; j < this->size-1; ++j) {
                        if((*this)(i,j) == (*this)(i,j+1) && (*this)(i,j) != 0) {
                            score += (*this)(i,j);
                            (*this)(i,j) *= 2;
                            if((*this)(i,j) == 2048) return true;
                            (*this)(i,j+1) = 0;
                            changeACell = true;
                            break;
                        }
                    }
                } while(changeACell);
            }
            break;
        case DOWN:
            // Iterate over all rows.
            for(unsigned i = 0; i < this->size; ++i) {
                // Repeat to self-consistency:
                // First move then add.
                do {
                    changeACell = false;
                    // If cell on the left (j-1) is zero, move current cell one left.
                    for(int j = this->size-2; j >= 0; --j) {
                        if((*this)(i,j+1) == 0 && (*this)(i,j) != 0) {
                            (*this)(i,j+1) = (*this)(i,j);
                            (*this)(i,j) = 0;
                            changeACell = true;
                        }
                    }
                    // If cell on the right (j+1) is the same as the one on the left, multiply left by two and set right (j) to zero.
                    for(unsigned j = this->size-1; j >= 1 ; --j) {
                        if((*this)(i,j) == (*this)(i,j-1) && (*this)(i,j) != 0) {
                            score += (*this)(i,j);
                            (*this)(i,j) *= 2;
                            if((*this)(i,j) == 2048) return true;
                            (*this)(i,j-1) = 0;
                            changeACell = true;
                            break;
                        }
                    }
                } while(changeACell);
            }
            break;
        case LEFT:
            // Iterate over all columns.
            for(unsigned i = 0; i < this->size; ++i) {
                // Repeat to self-consistency:
                // First move then add.
                do {
                    changeACell = false;
                    // If cell on the left (j-1) is zero, move current cell one left.
                    for(unsigned j = 1; j < this->size; ++j) {
                        if((*this)(j-1,i) == 0 && (*this)(j,i) != 0) {
                            (*this)(j-1,i) = (*this)(j,i);
                            (*this)(j,i) = 0;
                            changeACell = true;
                        }
                    }
                    // If cell on the right (j+1) is the same as the one on the left, multiply left by two and set right (j) to zero.
                    for(unsigned j = 0; j < this->size-1; ++j) {
                        if((*this)(j,i) == (*this)(j+1,i) && (*this)(j,i) != 0) {
                            score += (*this)(j,i);
                            (*this)(j,i) *= 2;
                            if((*this)(j,i) == 2048) return true;
                            (*this)(j+1,i) = 0;
                            changeACell = true;
                            break;
                        }
                    }
                } while(changeACell);
            }
            break;
        case RIGHT:
            // Iterate over all columns.
            for(unsigned i = 0; i < this->size; ++i) {
                // Repeat to self-consistency:
                // First move then add.
                do {
                    changeACell = false;
                    // If cell on the right (j+1) is zero, move current cell one right.
                    for(int j = this->size-2; j >= 0; --j) {
                        if((*this)(j+1,i) == 0 && (*this)(j,i) != 0) {
                            (*this)(j+1,i) = (*this)(j,i);
                            (*this)(j,i) = 0;
                            changeACell = true;
                        }
                    }
                    // If cell on the left (j-1) is the same as the one on the right, multiply right by two and set left (j) to zero.
                    for(unsigned j = this->size-1; j >= 1 ; --j) {
                        if((*this)(j,i) == (*this)(j-1,i) && (*this)(j,i) != 0) {
                            score += (*this)(j,i);
                            (*this)(j,i) *= 2;
                            if((*this)(j,i) == 2048) return true;
                            (*this)(j-1,i) = 0;
                            changeACell = true;
                            break;
                        }
                    }
                } while(changeACell);
            }
            break;
        }
        return false;
}

void board::draw()
{
    // Check if the number of rows/columns/cells is valid.
    assert(this->values.size() == this->size);
    for(unsigned i = 0; i < this->size; ++i) assert(this->values.at(i).size() == this->size);

    // Draw board.
    for(unsigned k = 0; k < this->size; ++k) {
        for(unsigned i = 0; i < this->size; ++i) {
            std::cout << "======";
        }
        std::cout << std::endl;
        for(unsigned j = 0; j < 3; ++j) {
            for(unsigned i = 0; i < this->size; ++i) {
                std::cout << "|";

                // If the value of cell i,j is zero do not print the number.
                if((*this)(i,k) != 0 && j == 1) std::cout << centerNumberstring(4,(*this)(i,k)); else std::cout <<  "    ";
                std::cout <<  "|";
            }
            std::cout << std::endl;
        }
    }
    for(unsigned i = 0; i < this->size; ++i) {
        std::cout << "======";
    }
    std::cout << std::endl;
}
