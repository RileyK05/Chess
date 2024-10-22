#include <unordered_set>
#include <iostream>
#include "Board.h"
#include "Bot.h"
#include "Bot.h"
#include "Player.h"

void testUniquePieceIds(const Board& board) {
    std::unordered_set<int> ids;
    bool duplicatesFound = false;

    for (const Piece& piece : board.getWhitePieces()) {
        int id = piece.getId();
        if (ids.find(id) != ids.end()) {
            std::cout << "Duplicate ID found for white piece: " << id << std::endl;
            duplicatesFound = true;
        }
        else {
            ids.insert(id);
        }
    }

    for (const Piece& piece : board.getBlackPieces()) {
        int id = piece.getId();
        if (ids.find(id) != ids.end()) {
            std::cout << "Duplicate ID found for black piece: " << id << std::endl;
            duplicatesFound = true;
        }
        else {
            ids.insert(id);
        }
    }

    if (!duplicatesFound) {
        std::cout << "Test 1 Passed: All piece IDs are unique." << std::endl;
    }
    else {
        std::cout << "Test 1 Failed: Duplicate piece IDs found." << std::endl;
    }
}

void testBoardRepresentation(Board& board) {
    std::cout << "Test 2: Board Representation" << std::endl;
    board.writeBoard();
    std::cout << "Please verify that the board matches the standard initial chess setup." << std::endl;
}

int main() {
    Board board;

    testUniquePieceIds(board);

    std::cout << std::endl;

    testBoardRepresentation(board);

    return 0;
}
