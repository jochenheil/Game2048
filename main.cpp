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
#include <sstream>
#include "board.h"

/*! \brief Get the board size from STDIN.
 * 
 *  Get the board size from STDIN. Catch erroneous input.
 * 
 *  \return The size of the 2048 board.
 */
unsigned getBoardSize() {
    
    int boardSize;
    std::string input;
    bool isValid = false;

    std::cout << "How large should the board be (4)?";    
    while(!isValid) {
        std::getline(std::cin,input);
        if(input.empty()) {
            boardSize = 4;
            isValid = true;
        }
        else {
            std::istringstream stream(input);
            stream >> boardSize;
            if(boardSize <= 0) {
                std::cout << "Invalid number. Please enter a positive integer." << std::endl;
                isValid = false;
            }
            else {
                std::cout << "Using a board of size " << boardSize << "." << std::endl;
                isValid = true;
            }
        }
    }
    return unsigned(boardSize);
}

/*! \brief Get a single character (a, s, d, w or q) from the keyboard.
 * 
 *  Get a single character (a, s, d, w or q) from the keyboard. These are used to 
 *  play the game or exit (q).
 * 
 *  \return The character obtained from the keybord.
 */
char getActionCommandKey() {
    char actionCommandKey = ' ';
    std::string actionCommandKeyString;
    int charCode = 0;
    bool isValidCmdKey;
    do {
        /* 
         * I know that getchar needs the user to hit enter, but direct action
         * upon hitting a key is not supported on the linux console.
         */
        actionCommandKey = char(std::getchar());
    } while(actionCommandKey != UP && 
            actionCommandKey != DOWN && 
            actionCommandKey != LEFT && 
            actionCommandKey != RIGHT && 
            actionCommandKey != QUIT);
    return actionCommandKey;
}

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
    bool isFinished = false;
    char actionCommandKey;
    while(1) {
        actionCommandKey = getActionCommandKey();
        if(actionCommandKey == QUIT) {
            break;
        }
        else {
            if(myBoard.move(actionCommandKey,score)) {
                std::cout << "!!! 2048 REACHED !!!" << std::endl;
                std::cout << "!!!   Game over  !!!" << std::endl;
                std::cout << "Score: " << score << std::endl;
                break;
            }
            else {
                if(!myBoard.addRandomValue(mt)) {
                    std::cout << "!!! NO SPACE  !!!" << std::endl;
                    std::cout << "!!! Game over !!!" << std::endl;
                    std::cout << "Score: " << score << std::endl;
                    break;
                }
                myBoard.draw();
                std::cout << "Score: " << score << std::endl;
            }
        }
    }
    
    return EXIT_SUCCESS;
}
