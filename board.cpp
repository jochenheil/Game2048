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
            (*this)(i,j) = 0;
        }
    }
}

std::vector< std::tuple<unsigned,unsigned> > board::getEmptyCells()
{
    std::vector<std::tuple<unsigned,unsigned> > emptyCells;
    for(unsigned i = 0; i < this->size; ++i) {
        for(unsigned j = 0; j < this->size; ++j) {
            if((*this)(i,j) == 0) emptyCells.push_back(std::tuple<unsigned,unsigned>(i,j));
        }
    }
    return emptyCells;
}

bool board::addRandomValue(std::mt19937& mt)
{
   
    // Get a list of all empty cell x,y-indices.
    std::vector<std::tuple<unsigned,unsigned> > emptyCells = this->getEmptyCells();

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

gameState_t board::move(const char direction,unsigned& score) {
    
    std::vector<unsigned> nonZeroElements;
    unsigned nZeroElements;
    unsigned nNonZeroElements;
    bool isValidMove = false;
    
    // Check whether there is still space left on the board.
    bool spaceLeft = false;
    for(unsigned i = 0; i < this->size; i++) {
        for(unsigned j = 0; j < this->size; j++) {
            if((*this)(i,j) == 0) spaceLeft = true;
        }
    }
    // If no space left on the board, you loose.
    if(!spaceLeft) { 
        return LOOSE;
    }
    
    for(unsigned i = 0; i < this->size; ++i) {

        // Get all cell values in line i according to the move direction.
        nonZeroElements.clear();
        if(direction == UP || direction == DOWN) {
            for(unsigned j = 0; j < this->size; ++j) { if((*this)(i,j) != 0) nonZeroElements.push_back((*this)(i,j)); }
        }
        else { // direction == LEFT/RIGHT
            for(unsigned j = 0; j < this->size; ++j) { if((*this)(j,i) != 0) nonZeroElements.push_back((*this)(j,i)); }
        }
        
        // If the line is not empty...
        if(nonZeroElements.size() > 0) {

            // ...combine values according to game rule and remove zero values, check if at least one was merged, and...
            if(combineCells(direction,nonZeroElements,score)) isValidMove = true;

            // ...check victory condition and...
            for(const unsigned elem : nonZeroElements) {
                if(elem == 2048) return WIN;
            }

            // ...assign new values to first few cells and set the rest of the line to zero.
            // Check if anything changes and set isValidMove to true if it does.
            switch(direction){
                case UP:
                    
                    // Write all non-zero elements at the upper part of the line.
                    for(unsigned j = 0; j < nonZeroElements.size(); ++j) {
                        if((*this)(i,j) != nonZeroElements.at(j)) isValidMove = true;
                        (*this)(i,j) = nonZeroElements.at(j);
                    }
                    
                    // Write all zero elements at the lower part of the line.
                    for(unsigned j = nonZeroElements.size(); j < this->size; ++j) {
                        if((*this)(i,j) != 0) isValidMove = true;
                        (*this)(i,j) = 0;
                    }
                    break;
                case DOWN:
                    
                    // Write all zero elements at the upper part of the line.
                    nZeroElements = this->size - nonZeroElements.size();
                    nNonZeroElements = this->size - nZeroElements;
                    for(unsigned j = 0; j < nZeroElements; ++j) {
                        if((*this)(i,j) != 0) isValidMove = true;
                        (*this)(i,j) = 0;
                    }

                    // Write all non-zero elements at the lower part of the line.
                    for(unsigned j = 0; j < nNonZeroElements; ++j) {
                        if((*this)(i,j+nZeroElements) != nonZeroElements.at(j)) isValidMove = true;
                        (*this)(i,j+nZeroElements) = nonZeroElements.at(j);
                    }
                    break;
                case LEFT:
                    
                    // Write all non-zero elements at the left part of the line.
                    for(unsigned j = 0; j < nonZeroElements.size(); ++j) {
                        if((*this)(j,i) != nonZeroElements.at(j)) isValidMove = true;
                        (*this)(j,i) = nonZeroElements.at(j);
                    }
                    
                    // Write all zero elements at the right part of the line.
                    for(unsigned j = nonZeroElements.size(); j < this->size; ++j) {
                        if((*this)(j,i) != 0) isValidMove = true;
                        (*this)(j,i) = 0;
                    }
                    break;
                case RIGHT:
                    
                    // Write all zero elements at the left part of the line.
                    nZeroElements = this->size - nonZeroElements.size();
                    nNonZeroElements = this->size - nZeroElements;
                    for(unsigned j = 0; j < nZeroElements; ++j) {
                        if((*this)(j,i) != 0) isValidMove = true;
                        (*this)(j,i) = 0;
                    }
                    
                    // Write all non-zero elements at the right part of the line.
                    for(unsigned j = 0; j < nNonZeroElements; ++j) {
                        if((*this)(j+nZeroElements,i) != nonZeroElements.at(j)) isValidMove = true;
                        (*this)(j+nZeroElements,i) = nonZeroElements.at(j);
                    }
                    break;
            }
        }
    }
    if(isValidMove) {
        return UNFINISHED;
    }
    else {
        return INVALID;
    }
}

void board::fillLine(const char direction,std::vector<unsigned> fillVector, const unsigned lineNumber)
{
    assert(fillVector.size() == this->size);
    switch(direction) {
        case UP:
            for(unsigned i = 0; i < this->size; ++i) (*this)(lineNumber,i) = fillVector.at(i);
            break;
        case DOWN:
            std::reverse(fillVector.begin(), fillVector.end());
            for(unsigned i = 0; i < this->size; ++i) (*this)(lineNumber,i) = fillVector.at(i);
            break;
        case LEFT:
            for(unsigned i = 0; i < this->size; ++i) (*this)(i,lineNumber) = fillVector.at(i);
            break;
        case RIGHT:
            std::reverse(fillVector.begin(), fillVector.end());
            for(unsigned i = 0; i < this->size; ++i) (*this)(i,lineNumber) = fillVector.at(i);
            break;
    }
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

void board::setBoardValues(const std::vector< std::vector< unsigned > > newValues)
{
    this->values = newValues;
}

std::vector< std::vector<unsigned> > board::getBoardValues() const
{
    return this->values;
}

unsigned& board::operator()(const unsigned row,const unsigned col)
{
    assert(row < this->size);
    assert(col < this->size);
    return this->values.at(row).at(col);
}
