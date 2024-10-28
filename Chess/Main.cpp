// test_chess.cpp

#include <unordered_set>
#include <iostream>
#include "Board.h"

// Helper function to convert coordinates to chess notation
std::string coordToNotation(int x, int y) {
    char file = 'A' + x;
    char rank = '8' - y;
    return std::string(1, file) + rank;
}

// Test 1: Check for Unique Piece IDs
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

// Test 2: Verify Initial Board Setup
void testBoardRepresentation(const Board& board) {
    std::cout << "Test 2: Board Representation" << std::endl;
    board.displayBoard();
    std::cout << "Please verify that the board matches the standard initial chess setup." << std::endl;
}

// Test 3: Test movePiece Function with Valid Moves
void testMovePieceValidMoves() {
    std::cout << "Test 3: movePiece Function with Valid Moves" << std::endl;
    Board board;

    // Move white pawn from E2 to E4
    int pawnId = -1;
    for (const Piece& piece : board.getWhitePieces()) {
        if (piece.getType() == PieceType::PAWN && piece.getX() == 4 && piece.getY() == 6) {
            pawnId = piece.getId();
            break;
        }
    }

    bool moveResult = board.movePiece(pawnId, 4, 4);
    if (moveResult) {
        std::cout << "Moved white pawn ID " << pawnId << " from E2 to E4 successfully." << std::endl;
    }
    else {
        std::cout << "Failed to move white pawn ID " << pawnId << " from E2 to E4." << std::endl;
    }

    // Verify the pawn's new position
    Piece* movedPawn = board.getPieceAt(4, 4);
    if (movedPawn && movedPawn->getId() == pawnId) {
        std::cout << "Pawn is now at E4." << std::endl;
    }
    else {
        std::cout << "Pawn is not at E4. Test Failed." << std::endl;
    }

    // Display the board after the move
    board.displayBoard();
    std::cout << std::endl;
}

// Test 4: Test movePiece Function with Invalid Moves
void testMovePieceInvalidMoves() {
    std::cout << "Test 4: movePiece Function with Invalid Moves" << std::endl;
    Board board;

    // Attempt to move white pawn from E2 to E5 (invalid)
    int pawnId = -1;
    for (const Piece& piece : board.getWhitePieces()) {
        if (piece.getType() == PieceType::PAWN && piece.getX() == 4 && piece.getY() == 6) {
            pawnId = piece.getId();
            break;
        }
    }

    bool moveResult = board.movePiece(pawnId, 4, 3); // E2 to E5
    if (!moveResult) {
        std::cout << "Correctly failed to move white pawn ID " << pawnId << " from E2 to E5 (invalid move)." << std::endl;
    }
    else {
        std::cout << "Incorrectly moved white pawn ID " << pawnId << " from E2 to E5. Test Failed." << std::endl;
    }

    // Display the board to verify no changes occurred
    board.displayBoard();
    std::cout << std::endl;
}

// Test 5: Test movePiece Function with Capture
void testMovePieceCapture() {
    std::cout << "Test 5: movePiece Function with Capture" << std::endl;
    Board board;

    // Move white pawn from E2 to E4
    int whitePawnId = -1;
    for (const Piece& piece : board.getWhitePieces()) {
        if (piece.getType() == PieceType::PAWN && piece.getX() == 4 && piece.getY() == 6) {
            whitePawnId = piece.getId();
            break;
        }
    }
    board.movePiece(whitePawnId, 4, 4); // E2 to E4

    // Move black pawn from D7 to D5
    int blackPawnId = -1;
    for (const Piece& piece : board.getBlackPieces()) {
        if (piece.getType() == PieceType::PAWN && piece.getX() == 3 && piece.getY() == 1) {
            blackPawnId = piece.getId();
            break;
        }
    }
    board.movePiece(blackPawnId, 3, 3); // D7 to D5

    // Move white pawn from E4 to D5 (capture)
    bool captureResult = board.movePiece(whitePawnId, 3, 3);
    if (captureResult) {
        std::cout << "White pawn ID " << whitePawnId << " captured black pawn at D5." << std::endl;
    }
    else {
        std::cout << "Failed to capture black pawn at D5. Test Failed." << std::endl;
    }

    // Verify that the black pawn is no longer alive
    bool blackPawnAlive = false;
    for (const Piece& piece : board.getBlackPieces()) {
        if (piece.getId() == blackPawnId) {
            blackPawnAlive = piece.isAlive();
            break;
        }
    }
    if (!blackPawnAlive) {
        std::cout << "Black pawn ID " << blackPawnId << " is captured." << std::endl;
    }
    else {
        std::cout << "Black pawn ID " << blackPawnId << " is still alive. Test Failed." << std::endl;
    }

    // Display the board after the capture
    board.displayBoard();
    std::cout << std::endl;
}

// Main Function with All Tests
int main() {
    // Create a board instance
    Board board;

    // Run Test 1: Unique Piece IDs
    testUniquePieceIds(board);
    std::cout << std::endl;

    // Run Test 2: Board Representation
    testBoardRepresentation(board);
    std::cout << std::endl;

    // Run Test 3: Valid Moves
    testMovePieceValidMoves();
    std::cout << std::endl;

    // Run Test 4: Invalid Moves
    testMovePieceInvalidMoves();
    std::cout << std::endl;

    // Run Test 5: Capture
    testMovePieceCapture();
    std::cout << std::endl;

    return 0;
}
