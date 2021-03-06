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

/*!\file main.cpp
 * \brief Main + IO funtions of the 2048 game.
 * 
 * This file contains the main function of the 2048 game including the event loop.
 * Also includes the io functions used to gather user input from STDIN.
 * 
 */

#include <iostream>
#include "board.h"
#include "helper.h"

/*! \brief Main routine.
 * 
 *  Main routine containing the main function of the 2048 game including the event loop.
 * 
 *  \param argc The number of commandline elements.
 *  \param argv The commandline elements.
 * 
 *  \return The error code.
 */
int main(int argc, char **argv) {

    // Get board size from STDIN.
    unsigned boardSize = getBoardSize();

    // Initialize random number generator.
    std::random_device rd;
    std::mt19937 mt(rd());

    // Make new board.
    unsigned score = 0;
    board myBoard(boardSize);
    myBoard.addRandomValue(mt);

    // Refresh screen + draw board for the first time.
    std::cout << std::string(80,'\n');
    std::cout << "Score: " << score << std::endl;
    myBoard.draw();
    
    // Event loop.
    gameState_t moveState = UNFINISHED;
    char actionCommandKey;
    while(1) {
        do {
            actionCommandKey = getActionCommandKey();
            if(actionCommandKey == QUIT) break;
            moveState = myBoard.move(actionCommandKey,score);
        } while(moveState == INVALID);
        if(actionCommandKey == QUIT) break;

        // Add a new value to the board.
        myBoard.addRandomValue(mt);
        
        // If gameover, print message.
        if(moveState == WIN || moveState == LOOSE) {
            printGameoverMessage(moveState,score);
            break;
        }

        // Not gameover, draw board.
        myBoard.draw();
        std::cout << "Score: " << score << std::endl;
    }
    
    return EXIT_SUCCESS;
}
