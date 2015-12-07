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

TEST(boardTest, checkAddRandomValue)
{
    // Initialize random number generator.
    std::random_device rd;
    std::mt19937 mt(rd());

    bool testval; // Whether the board is full or not.
    std::vector<std::tuple<unsigned,unsigned> > emptyCells; // Holds empty cells indices.
    
    board myBoard(2);

    // Check if cells are added consecutively.
    emptyCells = myBoard.getEmptyCells();
    EXPECT_EQ(emptyCells.size(),4);
    testval = myBoard.addRandomValue(mt);
    emptyCells = myBoard.getEmptyCells();
    EXPECT_EQ(emptyCells.size(),3);
    EXPECT_EQ(testval,true);
    testval = myBoard.addRandomValue(mt);
    emptyCells = myBoard.getEmptyCells();
    EXPECT_EQ(emptyCells.size(),2);
    EXPECT_EQ(testval,true);
    testval = myBoard.addRandomValue(mt);
    emptyCells = myBoard.getEmptyCells();
    EXPECT_EQ(emptyCells.size(),1);
    EXPECT_EQ(testval,true);
    testval = myBoard.addRandomValue(mt);
    emptyCells = myBoard.getEmptyCells();
    EXPECT_EQ(emptyCells.size(),0);
    EXPECT_EQ(testval,true);

    // Check if the game stops after adding one number too many...
    testval = myBoard.addRandomValue(mt);
    EXPECT_EQ(emptyCells.size(),0);
    EXPECT_EQ(testval,false);
}

TEST(boardTest, checkMoveLeft) 
{
    // Make new board.
    unsigned score = 0;
    board myBoard(4);

    // Test left move.
    myBoard.zero();
    myBoard(1,3) = 4;
    myBoard(2,3) = 4;
    myBoard(3,3) = 4;
    bool gameOver = myBoard.move(LEFT,score);
    EXPECT_EQ(myBoard(0,3),8);
    EXPECT_EQ(myBoard(1,3),4);
    EXPECT_EQ(gameOver,false);
}

TEST(boardTest, checkMoveRight) 
{
    // Make new board.
    unsigned score = 0;
    board myBoard(4);
    
    // Test right move.
    myBoard.zero();
    myBoard(0,3) = 4;
    myBoard(1,3) = 4;
    myBoard(2,3) = 4;
    bool gameOver = myBoard.move(RIGHT,score);
    EXPECT_EQ(myBoard(3,3),8);
    EXPECT_EQ(myBoard(2,3),4);
    EXPECT_EQ(gameOver,false);
}

TEST(boardTest, checkMoveUp) 
{
    // Make new board.
    unsigned score = 0;
    board myBoard(4);
    
    // Test up move.
    myBoard.zero();
    myBoard(3,1) = 4;
    myBoard(3,2) = 4;
    myBoard(3,3) = 4;
    bool gameOver = myBoard.move(UP,score);
    EXPECT_EQ(myBoard(3,0),8);
    EXPECT_EQ(myBoard(3,1),4);
    EXPECT_EQ(gameOver,false);
}

TEST(boardTest, checkMoveDown) 
{
    // Make new board.
    unsigned score = 0;
    board myBoard(4);
    
    // Test down move.
    myBoard.zero();
    myBoard(3,0) = 4;
    myBoard(3,1) = 4;
    myBoard(3,2) = 4;
    bool gameOver = myBoard.move(DOWN,score);
    EXPECT_EQ(myBoard(3,3),8);
    EXPECT_EQ(myBoard(3,2),4);
    EXPECT_EQ(gameOver,false);
}

