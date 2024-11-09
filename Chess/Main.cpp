// main.cpp

#include <iostream>
#include <cstdlib> 
#include "Board.h"
#include "Player.h"
#include "Bot.h"

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

int main() {
    Player humanPlayer(Color::WHITE, true);
    Bot aiPlayer(Color::BLACK);

    Board board;

    while (board.isGameRunning()) {
        system(CLEAR_COMMAND);

        board.displayBoard();

        std::cout << "Your turn (White):" << std::endl;
        bool moveMade = false;
        while (!moveMade) {
            moveMade = humanPlayer.makeMove(board);
            if (!moveMade) {
                std::cout << "Invalid move. Try again." << std::endl;
            }
        }

        if (!board.isGameRunning()) {
            break;
        }

        system(CLEAR_COMMAND);

        board.displayBoard();

        std::cout << "AI's turn (Black):" << std::endl;
        moveMade = aiPlayer.makeMove(board);
        if (!moveMade) {
            std::cout << "AI has no valid moves. Game over." << std::endl;
            board.setGameRunning(false);
        }
    }

    std::cout << "Game over." << std::endl;
    return 0;
}
