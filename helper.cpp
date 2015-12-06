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

/*!\file helper.cpp
 * \brief File contains the implementation of helper functions for the 2048 game.
 */

#include "helper.h"

unsigned generateCellValue(std::mt19937& mt)
{
    std::uniform_int_distribution<unsigned> startValueDist(1,10);
    unsigned newCellValue = startValueDist(mt);
    if(newCellValue > 9) newCellValue = 4; else newCellValue = 2;
    
    assert(newCellValue == 4 || newCellValue == 2);
    return newCellValue;
}

std::string centerNumberstring(const unsigned width, const unsigned inputNumber)
{
    std::string result = std::to_string(inputNumber);
    
    // Assert that the number is not larger than the cell inside which it should fit.
    assert(result.size() <= width);
    
    // Pad the number left and right until the final size of the string is reached.
    bool padAlternate = true;
    while(result.size() < width) {
        if(padAlternate == true) {
            result.append(" ");
        }
        else {
            std::reverse(result.begin(),result.end());
            result.append(" ");
            std::reverse(result.begin(),result.end());
        }
        padAlternate = ! padAlternate;
    }
    
    // Assert that the final string length corresponds to the original width.
    assert(result.size() == width);
    return result;
}
