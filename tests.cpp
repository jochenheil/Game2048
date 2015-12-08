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

    bool boardIsFull; // Whether the board is full or not.
    std::vector<std::tuple<unsigned,unsigned> > emptyCells; // Holds empty cells indices.
    
    board myBoard(2);

    // Check if cells are added consecutively.
    emptyCells = myBoard.getEmptyCells();
    EXPECT_EQ(emptyCells.size(),4);
    boardIsFull = myBoard.addRandomValue(mt);
    emptyCells = myBoard.getEmptyCells();
    EXPECT_EQ(emptyCells.size(),3);
    EXPECT_EQ(boardIsFull,true);
    boardIsFull = myBoard.addRandomValue(mt);
    emptyCells = myBoard.getEmptyCells();
    EXPECT_EQ(emptyCells.size(),2);
    EXPECT_EQ(boardIsFull,true);
    boardIsFull = myBoard.addRandomValue(mt);
    emptyCells = myBoard.getEmptyCells();
    EXPECT_EQ(emptyCells.size(),1);
    EXPECT_EQ(boardIsFull,true);
    boardIsFull = myBoard.addRandomValue(mt);
    emptyCells = myBoard.getEmptyCells();
    EXPECT_EQ(emptyCells.size(),0);
    EXPECT_EQ(boardIsFull,true);

    // Check if the game stops after adding one number too many...
    boardIsFull = myBoard.addRandomValue(mt);
    EXPECT_EQ(emptyCells.size(),0);
    EXPECT_EQ(boardIsFull,false);
}

// Check invalid moves on full lines.
TEST(boardTest, checkMoveInvalid) {
    board myBoard(4);
    unsigned score;
    gameState_t gameState;
    std::vector<unsigned> testLine1 {2,4,8,16};
    std::vector< std::vector<unsigned> > boardValBefore;

    // Up.
    myBoard.zero();
    myBoard.fillLine(UP,testLine1,0);
    boardValBefore = myBoard.getBoardValues();
    score = 0;
    gameState = myBoard.move(UP,score);
    EXPECT_EQ(score,0);
    EXPECT_EQ(gameState,INVALID);
    EXPECT_EQ(boardValBefore,myBoard.getBoardValues());

    // Down.
    myBoard.zero();
    myBoard.fillLine(DOWN,testLine1,0);
    boardValBefore = myBoard.getBoardValues();
    score = 0;
    gameState = myBoard.move(UP,score);
    EXPECT_EQ(score,0);
    EXPECT_EQ(gameState,INVALID);
    EXPECT_EQ(boardValBefore,myBoard.getBoardValues());

    // Right.
    myBoard.zero();
    myBoard.fillLine(RIGHT,testLine1,0);
    boardValBefore = myBoard.getBoardValues();
    score = 0;
    gameState = myBoard.move(RIGHT,score);
    EXPECT_EQ(score,0);
    EXPECT_EQ(gameState,INVALID);
    EXPECT_EQ(boardValBefore,myBoard.getBoardValues());

    // Left.
    myBoard.zero();
    myBoard.fillLine(LEFT,testLine1,0);
    boardValBefore = myBoard.getBoardValues();
    score = 0;
    gameState = myBoard.move(LEFT,score);
    EXPECT_EQ(score,0);
    EXPECT_EQ(gameState,INVALID);
    EXPECT_EQ(boardValBefore,myBoard.getBoardValues());
}

// Check valid moves without merges.
TEST(boardTest, checkMoveWithoutMerge) {
    board myBoard(4);
    unsigned score;
    gameState_t gameState;
    std::vector<unsigned> testLine1 {0,2,4,8};
    std::vector< std::vector<unsigned> > boardValBefore;
    std::vector< std::vector<unsigned> > boardValAfter;
    
    // Up.
    boardValBefore = {{0,2,4,8},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    boardValAfter = {{2,4,8,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    myBoard.setBoardValues(boardValBefore);
    score = 0;
    gameState = myBoard.move(UP,score);
    EXPECT_EQ(score,0);
    EXPECT_EQ(gameState,UNFINISHED);
    EXPECT_EQ(myBoard.getBoardValues(),boardValAfter);
    
    // Down.
    boardValBefore = {{8,4,2,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    boardValAfter = {{0,8,4,2},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    myBoard.setBoardValues(boardValBefore);
    score = 0;
    gameState = myBoard.move(DOWN,score);
    EXPECT_EQ(score,0);
    EXPECT_EQ(gameState,UNFINISHED);
    EXPECT_EQ(myBoard.getBoardValues(),boardValAfter);
    
    // Left.
    boardValBefore = {{0,0,0,0},{2,0,0,0},{4,0,0,0},{8,0,0,0}};
    boardValAfter = {{2,0,0,0},{4,0,0,0},{8,0,0,0},{0,0,0,0}};
    myBoard.setBoardValues(boardValBefore);
    score = 0;
    gameState = myBoard.move(LEFT,score);
    EXPECT_EQ(score,0);
    EXPECT_EQ(gameState,UNFINISHED);
    EXPECT_EQ(myBoard.getBoardValues(),boardValAfter);
    
    // Right.
    boardValBefore = {{8,0,0,0},{4,0,0,0},{2,0,0,0},{0,0,0,0}};
    boardValAfter = {{0,0,0,0},{8,0,0,0},{4,0,0,0},{2,0,0,0}};
    myBoard.setBoardValues(boardValBefore);
    score = 0;
    gameState = myBoard.move(RIGHT,score);
    EXPECT_EQ(score,0);
    EXPECT_EQ(gameState,UNFINISHED);
    EXPECT_EQ(myBoard.getBoardValues(),boardValAfter);
}

// Check valid moves with 1 merge.
TEST(boardTest, checkMoveWithMerge) {
    board myBoard(4);
    unsigned score;
    gameState_t gameState;
    std::vector<unsigned> testLine1 {0,2,4,8};
    std::vector< std::vector<unsigned> > boardValBefore;
    std::vector< std::vector<unsigned> > boardValAfter;
    
    // Up.
    boardValBefore = {{0,2,2,8},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    boardValAfter = {{4,8,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    myBoard.setBoardValues(boardValBefore);
    score = 0;
    gameState = myBoard.move(UP,score);
    EXPECT_EQ(score,4);
    EXPECT_EQ(gameState,UNFINISHED);
    EXPECT_EQ(myBoard.getBoardValues(),boardValAfter);

    // Down.
    boardValBefore = {{8,2,2,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    boardValAfter = {{0,0,8,4},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    myBoard.setBoardValues(boardValBefore);
    score = 0;
    gameState = myBoard.move(DOWN,score);
    EXPECT_EQ(score,4);
    EXPECT_EQ(gameState,UNFINISHED);
    EXPECT_EQ(myBoard.getBoardValues(),boardValAfter);
    
    // Left.
    boardValBefore = {{0,0,0,0},{2,0,0,0},{2,0,0,0},{8,0,0,0}};
    boardValAfter = {{4,0,0,0},{8,0,0,0},{0,0,0,0},{0,0,0,0}};
    myBoard.setBoardValues(boardValBefore);
    score = 0;
    gameState = myBoard.move(LEFT,score);
    EXPECT_EQ(score,4);
    EXPECT_EQ(gameState,UNFINISHED);
    EXPECT_EQ(myBoard.getBoardValues(),boardValAfter);
    
    // Right.
    boardValBefore = {{8,0,0,0},{2,0,0,0},{2,0,0,0},{0,0,0,0}};
    boardValAfter = {{0,0,0,0},{0,0,0,0},{8,0,0,0},{4,0,0,0}};
    myBoard.setBoardValues(boardValBefore);
    score = 0;
    gameState = myBoard.move(RIGHT,score);
    EXPECT_EQ(score,4);
    EXPECT_EQ(gameState,UNFINISHED);
    EXPECT_EQ(myBoard.getBoardValues(),boardValAfter);
}

// Check valid moves with 2 merges.
TEST(boardTest, checkMoveWith2Merges) {
    board myBoard(4);
    unsigned score;
    gameState_t gameState;
    std::vector< std::vector<unsigned> > boardValBefore;
    std::vector< std::vector<unsigned> > boardValAfter;
    
    // Up.
    boardValBefore = {{2,2,2,2},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    boardValAfter = {{4,4,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    myBoard.setBoardValues(boardValBefore);
    score = 0;
    gameState = myBoard.move(UP,score);
    EXPECT_EQ(score,8);
    EXPECT_EQ(gameState,UNFINISHED);
    EXPECT_EQ(myBoard.getBoardValues(),boardValAfter);
    
    // Down.
    boardValBefore = {{2,2,2,2},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    boardValAfter = {{0,0,4,4},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    myBoard.setBoardValues(boardValBefore);
    score = 0;
    gameState = myBoard.move(DOWN,score);
    EXPECT_EQ(score,8);
    EXPECT_EQ(gameState,UNFINISHED);
    EXPECT_EQ(myBoard.getBoardValues(),boardValAfter);
    
    // Left.
    boardValBefore = {{2,0,0,0},{2,0,0,0},{2,0,0,0},{2,0,0,0}};
    boardValAfter = {{4,0,0,0},{4,0,0,0},{0,0,0,0},{0,0,0,0}};
    myBoard.setBoardValues(boardValBefore);
    score = 0;
    gameState = myBoard.move(LEFT,score);
    EXPECT_EQ(score,8);
    EXPECT_EQ(gameState,UNFINISHED);
    EXPECT_EQ(myBoard.getBoardValues(),boardValAfter);
    
    // Right.
    boardValBefore = {{2,0,0,0},{2,0,0,0},{2,0,0,0},{2,0,0,0}};
    boardValAfter = {{0,0,0,0},{0,0,0,0},{4,0,0,0},{4,0,0,0}};
    myBoard.setBoardValues(boardValBefore);
    score = 0;
    gameState = myBoard.move(RIGHT,score);
    EXPECT_EQ(score,8);
    EXPECT_EQ(gameState,UNFINISHED);
    EXPECT_EQ(myBoard.getBoardValues(),boardValAfter);
}
