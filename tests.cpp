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
#include <gtest/gtest.h>

TEST(IndependentMethod, ResetsToZero1)
{
    std::vector<unsigned> values1 = {2,3,4};
    std::vector<unsigned> values2 = {4,1,0};
    line line1(3,row,values1);
    line line2(3,row,values2);
    line line3 = line1 + line2;
    EXPECT_EQ(line3.getValue(0), 6);
    EXPECT_EQ(line3.getValue(1), 4);
    EXPECT_EQ(line3.getValue(2), 4);
}

TEST(IndependentMethod, ResetsToZero2)
{
    board myBoard(3);
    line testCol(3,col,std::vector<unsigned>({1,2,3}));
    myBoard.setCol(testCol,2);
    line testRow(3,row,std::vector<unsigned>({16,15,14}));
    myBoard.setRow(testRow,0);
    line line1 = myBoard.getRow(0);
    line line2 = myBoard.getRow(1);
    line line3 = myBoard.getRow(2);
    line line4 = myBoard.getCol(0);
    line line5 = myBoard.getCol(1);
    line line6 = myBoard.getCol(2);
    EXPECT_EQ(line1.getValue(0),16);
    EXPECT_EQ(line1.getValue(1),0);
    EXPECT_EQ(line1.getValue(2),0);
    EXPECT_EQ(line2.getValue(0),15);
    EXPECT_EQ(line2.getValue(1),0);
    EXPECT_EQ(line2.getValue(2),0);
    EXPECT_EQ(line3.getValue(0),14);
    EXPECT_EQ(line3.getValue(1),2);
    EXPECT_EQ(line3.getValue(2),3);

    EXPECT_EQ(line4.getValue(0),16);
    EXPECT_EQ(line4.getValue(1),15);
    EXPECT_EQ(line4.getValue(2),14);
    EXPECT_EQ(line5.getValue(0),0);
    EXPECT_EQ(line5.getValue(1),0);
    EXPECT_EQ(line5.getValue(2),2);
    EXPECT_EQ(line6.getValue(0),0);
    EXPECT_EQ(line6.getValue(1),0);
    EXPECT_EQ(line6.getValue(2),3);
}