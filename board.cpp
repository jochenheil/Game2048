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

board::board(std::mt19937& mt, const unsigned size)
{
    this->mt = mt;
    this->size = size;

    // Initialize board with all cells = 0.
    this->values.resize(this->size);
    for(unsigned i = 0; i < this->size; ++i) {
        this->values.at(i).resize(this->size);
        for(unsigned j = 0; j < this->size; ++j) {
            this->values.at(i).at(j) = 0;
        }
    }
    
    // Start with a single occupied cell.
    this->addRandomValue();
}

board::~board()
{
}

void board::addRandomValue()
{
    // Number of empty cells.
    unsigned emptyCount = 0;

    // Count empty cells.
    for(unsigned i = 0; i < this->size; ++i) {
        for(unsigned j = 0; j < this->size; ++j) {
            if(this->values.at(i).at(j) == 0) emptyCount++;
        }
    }

    // Get a random empty cell and a new random value of 2 or 4.
    std::uniform_int_distribution<unsigned> randomCellDist(0,emptyCount);
    unsigned randomCellCount = randomCellDist(mt);
    
    // Fill random cell with 2 or 4.
    unsigned newEmptyCount = 0;
    for(unsigned i = 0; i < this->size; ++i) {
        for(unsigned j = 0; j < this->size; ++j) {
            if(this->values.at(i).at(j) == 0) {
                if(newEmptyCount == randomCellCount) this->values.at(i).at(j) = generateCellValue(this->mt);
                newEmptyCount++;
            }
        }
    }
}

void board::move(const char direction)
{
    switch(direction){
        case UP:
            
            break;
        case DOWN:

            break;
        case LEFT:

            break;
        case RIGHT:

            break;
        default:
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

                // If the value of cell i,j is zero do not print the number
                if(this->values.at(i).at(k) != 0 && j == 1) std::cout << centerNumberstring(4,this->values.at(i).at(k)); else std::cout <<  "    ";
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

line board::getCol(const unsigned colNum) const
{
    // Check if the number of columns/cells is valid.
    assert(colNum < this->size);
    
    std::vector<unsigned> newColValues(this->size);
    unsigned count = 0;
    for(unsigned & elem : newColValues) {
        elem = this->values.at(colNum).at(count);
        count++;
    }
    line newCol(this->size,row,newColValues);
    return newCol;
}

line board::getRow(const unsigned rowNum) const
{
    // Check if the number of rows/cells is valid.
    assert(rowNum < this->size);
    
    std::vector<unsigned> newRowValues(this->size);
    unsigned count = 0;
    for(unsigned & elem : newRowValues) {
        elem = this->values.at(count).at(rowNum);
        count++;
    }
    line newRow(this->size,row,newRowValues);
    return newRow;
}

void board::setCol(const line& colToSet, const unsigned int colNum)
{
    // Check if the line to write to the board is really a column with the correct number of cells.
    assert(colNum < this->size);
    assert(colToSet.rowOrCol == col);

    for(unsigned i = 0; i < this->size; ++i) this->values.at(i).at(colNum) = colToSet.values.at(i);
}

void board::setRow(const line& rowToSet, const unsigned int rowNum)
{
    // Check if the line to write to the board is really a row with the correct number of cells.
    assert(rowNum < this->size);
    assert(rowToSet.rowOrCol == row);

    for(unsigned i = 0; i < this->size; ++i) this->values.at(rowNum).at(i) = rowToSet.values.at(i);
}

line::line(const unsigned& size, const bool& rowOrCol, const std::vector<unsigned>& values)
{
    this->size = size;
    this->rowOrCol = rowOrCol;
    this->values.resize(this->size);
    this->values = values;
}

unsigned line::getValue(const unsigned num)
{
    if(num < this->size) {
        return this->values.at(num);
    }
    else {
        std::cerr << "Internal error: Trying to get a line element from ouside boundarys, abort!" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

bool line::isCol()
{
    if(this->rowOrCol == col) return true; else return false;
}

bool line::isRow()
{
    if(this->rowOrCol == row) return true; else return false;
}

line line::operator+(const line& right)
{
    assert(this->rowOrCol == right.rowOrCol);
    assert(this->values.size() == right.values.size());
    assert(this->size == right.size);
    std::vector<unsigned> resultValues(this->size);
    unsigned count = 0;
    for(unsigned & elem : resultValues) {
        elem = this->values.at(count) + right.values.at(count);
        count++;
    }
    line result(this->size,this->rowOrCol,resultValues);
    for(unsigned i = 0; i < this->size; ++i) result.values.at(i) = this->values.at(i) + right.values.at(i);
    return result;
}

line& line::operator=(const line& right)
{
    assert(this->rowOrCol == right.rowOrCol);
    assert(this->values.size() == right.values.size());
    assert(this->size == right.size);
    this->size = right.size;
    this->values = right.values;
    return *this;
}

line::~line()
{

}
