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

#include "board.h"

board::board(const unsigned size)
{
    assert(this->size > 0);
    this->size = size;
}

board::~board()
{

}

void board::draw()
{

}

line board::getCol(const unsigned int colNum) const
{
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

line& board::getRow(const unsigned int rowNum) const
{
    assert(rowNum < this->size);
    std::vector<unsigned> newRowValues(this->size);
    unsigned count = 0;
    for(unsigned & elem : newRowValues) {
        elem = this->values.at(rowNum).at(count);
        count++;
    }
    //         line newRow = new line(this->size,row,newRowValues);
    //         return *newRow;
    line newRow(this->size,row,newRowValues);
    return newRow;
}

void board::setCol(const line& col)
{

}

void board::setRow(const line& row)
{

}


line::line(const unsigned int& size, const bool& rowOrCol, const std::vector< unsigned int >& values)
{
    this->size = size;
    this->rowOrCol = rowOrCol;
    this->values = values;
}

unsigned int line::getValue(unsigned int num)
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

}

bool line::isRow()
{

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
