#include <unordered_set>
#include <iostream>
#include "Board.h"

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

// Test 3: Verify Initial Pawn Moves
void testInitialPawnMoves(const Board& board) {
    std::cout << "Test 3: Initial Pawn Moves" << std::endl;
    bool allPassed = true;

    // Test white pawns
    for (const Piece& piece : board.getWhitePieces()) {
        if (piece.getType() == PieceType::PAWN) {
            std::vector<std::pair<int, int>> validMoves = piece.getAllValidMoves(board);
            if (validMoves.size() != 2) {
                std::cout << "White pawn ID " << piece.getId() << " has " << validMoves.size()
                    << " valid moves (expected 2)." << std::endl;
                allPassed = false;
            }
        }
    }

    // Test black pawns
    for (const Piece& piece : board.getBlackPieces()) {
        if (piece.getType() == PieceType::PAWN) {
            std::vector<std::pair<int, int>> validMoves = piece.getAllValidMoves(board);
            if (validMoves.size() != 2) {
                std::cout << "Black pawn ID " << piece.getId() << " has " << validMoves.size()
                    << " valid moves (expected 2)." << std::endl;
                allPassed = false;
            }
        }
    }

    if (allPassed) {
        std::cout << "Test 3 Passed: All initial pawns have two valid moves." << std::endl;
    }
    else {
        std::cout << "Test 3 Failed: Some pawns do not have two valid moves." << std::endl;
    }
}

// Test 4: Verify Initial Knight Moves
void testInitialKnightMoves(const Board& board) {
    std::cout << "Test 4: Initial Knight Moves" << std::endl;
    bool allPassed = true;

    // Test white knights
    for (const Piece& piece : board.getWhitePieces()) {
        if (piece.getType() == PieceType::KNIGHT) {
            std::vector<std::pair<int, int>> validMoves = piece.getAllValidMoves(board);
            if (validMoves.size() != 2) {
                std::cout << "White knight ID " << piece.getId() << " has " << validMoves.size()
                    << " valid moves (expected 2)." << std::endl;
                allPassed = false;
            }
        }
    }

    // Test black knights
    for (const Piece& piece : board.getBlackPieces()) {
        if (piece.getType() == PieceType::KNIGHT) {
            std::vector<std::pair<int, int>> validMoves = piece.getAllValidMoves(board);
            if (validMoves.size() != 2) {
                std::cout << "Black knight ID " << piece.getId() << " has " << validMoves.size()
                    << " valid moves (expected 2)." << std::endl;
                allPassed = false;
            }
        }
    }

    if (allPassed) {
        std::cout << "Test 4 Passed: All initial knights have two valid moves." << std::endl;
    }
    else {
        std::cout << "Test 4 Failed: Some knights do not have two valid moves." << std::endl;
    }
}

// Test 5: Verify Rooks Have No Initial Moves (Blocked)
void testRookBlockedMoves(const Board& board) {
    std::cout << "Test 5: Initial Rook Moves" << std::endl;
    bool allPassed = true;

    // Test white rooks
    for (const Piece& piece : board.getWhitePieces()) {
        if (piece.getType() == PieceType::ROOK) {
            std::vector<std::pair<int, int>> validMoves = piece.getAllValidMoves(board);
            if (!validMoves.empty()) {
                std::cout << "White rook ID " << piece.getId() << " has " << validMoves.size()
                    << " valid moves (expected 0)." << std::endl;
                allPassed = false;
            }
        }
    }

    // Test black rooks
    for (const Piece& piece : board.getBlackPieces()) {
        if (piece.getType() == PieceType::ROOK) {
            std::vector<std::pair<int, int>> validMoves = piece.getAllValidMoves(board);
            if (!validMoves.empty()) {
                std::cout << "Black rook ID " << piece.getId() << " has " << validMoves.size()
                    << " valid moves (expected 0)." << std::endl;
                allPassed = false;
            }
        }
    }

    if (allPassed) {
        std::cout << "Test 5 Passed: All initial rooks have zero valid moves (blocked)." << std::endl;
    }
    else {
        std::cout << "Test 5 Failed: Some rooks have unexpected valid moves." << std::endl;
    }
}

// Test 6: Verify Bishops Have No Initial Moves (Blocked)
void testBishopBlockedMoves(const Board& board) {
    std::cout << "Test 6: Initial Bishop Moves" << std::endl;
    bool allPassed = true;

    // Test white bishops
    for (const Piece& piece : board.getWhitePieces()) {
        if (piece.getType() == PieceType::BISHOP) {
            std::vector<std::pair<int, int>> validMoves = piece.getAllValidMoves(board);
            if (!validMoves.empty()) {
                std::cout << "White bishop ID " << piece.getId() << " has " << validMoves.size()
                    << " valid moves (expected 0)." << std::endl;
                allPassed = false;
            }
        }
    }

    // Test black bishops
    for (const Piece& piece : board.getBlackPieces()) {
        if (piece.getType() == PieceType::BISHOP) {
            std::vector<std::pair<int, int>> validMoves = piece.getAllValidMoves(board);
            if (!validMoves.empty()) {
                std::cout << "Black bishop ID " << piece.getId() << " has " << validMoves.size()
                    << " valid moves (expected 0)." << std::endl;
                allPassed = false;
            }
        }
    }

    if (allPassed) {
        std::cout << "Test 6 Passed: All initial bishops have zero valid moves (blocked)." << std::endl;
    }
    else {
        std::cout << "Test 6 Failed: Some bishops have unexpected valid moves." << std::endl;
    }
}

// Test 7: Verify Queens Have No Initial Moves (Blocked)
void testQueenBlockedMoves(const Board& board) {
    std::cout << "Test 7: Initial Queen Moves" << std::endl;
    bool allPassed = true;

    // Test white queen
    for (const Piece& piece : board.getWhitePieces()) {
        if (piece.getType() == PieceType::QUEEN) {
            std::vector<std::pair<int, int>> validMoves = piece.getAllValidMoves(board);
            if (!validMoves.empty()) {
                std::cout << "White queen ID " << piece.getId() << " has " << validMoves.size()
                    << " valid moves (expected 0)." << std::endl;
                allPassed = false;
            }
        }
    }

    // Test black queen
    for (const Piece& piece : board.getBlackPieces()) {
        if (piece.getType() == PieceType::QUEEN) {
            std::vector<std::pair<int, int>> validMoves = piece.getAllValidMoves(board);
            if (!validMoves.empty()) {
                std::cout << "Black queen ID " << piece.getId() << " has " << validMoves.size()
                    << " valid moves (expected 0)." << std::endl;
                allPassed = false;
            }
        }
    }

    if (allPassed) {
        std::cout << "Test 7 Passed: All initial queens have zero valid moves (blocked)." << std::endl;
    }
    else {
        std::cout << "Test 7 Failed: Some queens have unexpected valid moves." << std::endl;
    }
}

// Test 8: Verify Kings Have No Initial Moves (Blocked)
void testKingBlockedMoves(const Board& board) {
    std::cout << "Test 8: Initial King Moves" << std::endl;
    bool allPassed = true;

    // Test white king
    for (const Piece& piece : board.getWhitePieces()) {
        if (piece.getType() == PieceType::KING) {
            std::vector<std::pair<int, int>> validMoves = piece.getAllValidMoves(board);
            if (!validMoves.empty()) {
                std::cout << "White king ID " << piece.getId() << " has " << validMoves.size()
                    << " valid moves (expected 0)." << std::endl;
                allPassed = false;
            }
        }
    }

    // Test black king
    for (const Piece& piece : board.getBlackPieces()) {
        if (piece.getType() == PieceType::KING) {
            std::vector<std::pair<int, int>> validMoves = piece.getAllValidMoves(board);
            if (!validMoves.empty()) {
                std::cout << "Black king ID " << piece.getId() << " has " << validMoves.size()
                    << " valid moves (expected 0)." << std::endl;
                allPassed = false;
            }
        }
    }

    if (allPassed) {
        std::cout << "Test 8 Passed: All initial kings have zero valid moves (blocked)." << std::endl;
    }
    else {
        std::cout << "Test 8 Failed: Some kings have unexpected valid moves." << std::endl;
    }
}

// Main Function with All Tests
int main() {
    Board board;

    // Run Test 1: Unique Piece IDs
    testUniquePieceIds(board);
    std::cout << std::endl;

    // Run Test 2: Board Representation
    testBoardRepresentation(board);
    std::cout << std::endl;

    // Run Test 3: Initial Pawn Moves
    testInitialPawnMoves(board);
    std::cout << std::endl;

    // Run Test 4: Initial Knight Moves
    testInitialKnightMoves(board);
    std::cout << std::endl;

    // Run Test 5: Rooks Blocked Moves
    testRookBlockedMoves(board);
    std::cout << std::endl;

    // Run Test 6: Bishops Blocked Moves
    testBishopBlockedMoves(board);
    std::cout << std::endl;

    // Run Test 7: Queens Blocked Moves
    testQueenBlockedMoves(board);
    std::cout << std::endl;

    // Run Test 8: Kings Blocked Moves
    testKingBlockedMoves(board);
    std::cout << std::endl;

    // Since we cannot move pieces without modifying the Board class, we'll skip Test 9
    // Alternatively, we can adjust Test 9 to test other aspects that don't require moving pieces

    return 0;
}
