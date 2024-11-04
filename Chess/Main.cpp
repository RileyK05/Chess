#include <iostream>
#include "Board.h"
#include "Player.h"

// Helper function to find a piece by type and position
int findPieceId(const std::vector<Piece>& pieces, PieceType type, int x, int y) {
    for (const Piece& piece : pieces) {
        if (piece.getType() == type && piece.getX() == x && piece.getY() == y && piece.isAlive()) {
            return piece.getId();
        }
    }
    return -1;
}

// Test 1: White Pawn captures Black Pawn
void testCapturePiece() {
    Board board;
    Player whitePlayer(Color::WHITE, true);
    Player blackPlayer(Color::BLACK, true);

    std::cout << "Test 1: White Pawn captures Black Pawn" << std::endl;

    // Move White Pawn from E2 to E4
    int whitePawnId = findPieceId(board.whitePieces, PieceType::PAWN, 4, 6); // E2
    if (whitePawnId == -1) {
        std::cout << "White Pawn not found for Test 1." << std::endl;
        return;
    }
    board.movePiece(whitePawnId, 4, 4); // E2 to E4

    // Move Black Pawn from D7 to D5
    int blackPawnId = findPieceId(board.blackPieces, PieceType::PAWN, 3, 1); // D7
    if (blackPawnId == -1) {
        std::cout << "Black Pawn not found for Test 1." << std::endl;
        return;
    }
    board.movePiece(blackPawnId, 3, 3); // D7 to D5

    // White Pawn captures Black Pawn at D5
    std::pair<bool, Piece*> moveResult = board.movePiece(whitePawnId, 3, 3); // E4 to D5
    if (moveResult.first && moveResult.second != nullptr) {
        whitePlayer.addCapturedPiece(moveResult.second);
        std::cout << "White Pawn ID " << whitePawnId << " captured Black Pawn ID " << blackPawnId << " successfully." << std::endl;
    }
    else {
        std::cout << "Failed to capture Black Pawn at D5." << std::endl;
    }

    // Verify capturedPieces vector
    if (!whitePlayer.getCapturedPieces().empty()) {
        std::cout << "White Player has captured pieces:" << std::endl;
        whitePlayer.displayCapturedPieces();
    }
    else {
        std::cout << "White Player has no captured pieces." << std::endl;
    }

    // Check if the captured piece is not alive
    if (moveResult.second && !moveResult.second->isAlive()) {
        std::cout << "Captured piece is correctly removed from the board." << std::endl;
    }
    else {
        std::cout << "Captured piece is still on the board. Test Failed." << std::endl;
    }

    board.displayBoard();
    std::cout << std::endl;
}

// Test 2: Attempt to Capture Own Piece
void testInvalidCapture() {
    Board board;
    Player whitePlayer(Color::WHITE, true);
    Player blackPlayer(Color::BLACK, true);

    std::cout << "Test 2: Attempt to Capture Own Piece" << std::endl;

    // Move White Pawn from D2 to D4
    int whitePawnId = findPieceId(board.whitePieces, PieceType::PAWN, 3, 6); // D2
    if (whitePawnId == -1) {
        std::cout << "White Pawn not found for Test 2." << std::endl;
        return;
    }
    board.movePiece(whitePawnId, 3, 4); // D2 to D4

    // Move White Pawn from E2 to E4
    int secondWhitePawnId = findPieceId(board.whitePieces, PieceType::PAWN, 4, 6); // E2
    if (secondWhitePawnId == -1) {
        std::cout << "Second White Pawn not found for Test 2." << std::endl;
        return;
    }
    board.movePiece(secondWhitePawnId, 4, 4); // E2 to E4

    // Attempt to move White Pawn from E4 to D5 where no Black Pawn is present (should succeed as a regular move)
    std::pair<bool, Piece*> moveResult1 = board.movePiece(secondWhitePawnId, 3, 5); // E4 to D5
    if (moveResult1.first && moveResult1.second == nullptr) {
        std::cout << "White Pawn ID " << secondWhitePawnId << " moved to D5 successfully." << std::endl;
    }
    else {
        std::cout << "Failed to move White Pawn ID " << secondWhitePawnId << " to D5." << std::endl;
    }

    // Move White Pawn from D4 to D5 to occupy D5
    std::pair<bool, Piece*> moveResult2 = board.movePiece(whitePawnId, 3, 5); // D4 to D5
    if (moveResult2.first && moveResult2.second == nullptr) {
        std::cout << "White Pawn ID " << whitePawnId << " moved from D4 to D5 successfully." << std::endl;
    }
    else {
        std::cout << "Failed to move White Pawn ID " << whitePawnId << " from D4 to D5." << std::endl;
    }

    // Now, attempt to move White Pawn from E4 to D5, which is now occupied by another White Pawn (should fail)
    std::pair<bool, Piece*> moveResult3 = board.movePiece(secondWhitePawnId, 3, 5); // E4 to D5
    if (!moveResult3.first) {
        std::cout << "Correctly prevented White Pawn ID " << secondWhitePawnId << " from capturing its own piece at D5." << std::endl;
    }
    else {
        std::cout << "Incorrectly allowed White Pawn ID " << secondWhitePawnId << " to capture its own piece at D5. Test Failed." << std::endl;
    }

    board.displayBoard();
    std::cout << std::endl;
}

// Test 3: Verify Captured Pieces Storage
void testCapturedPiecesStorage() {
    Board board;
    Player whitePlayer(Color::WHITE, true);
    Player blackPlayer(Color::BLACK, true);

    std::cout << "Test 3: Verify Captured Pieces Storage" << std::endl;

    // Move White Pawn from F2 to F4
    int whitePawnId = findPieceId(board.whitePieces, PieceType::PAWN, 5, 6); // F2
    if (whitePawnId == -1) {
        std::cout << "White Pawn not found for Test 3." << std::endl;
        return;
    }
    board.movePiece(whitePawnId, 5, 4); // F2 to F4

    // Move Black Pawn from D7 to D5
    int blackPawnId1 = findPieceId(board.blackPieces, PieceType::PAWN, 3, 1); // D7
    if (blackPawnId1 == -1) {
        std::cout << "Black Pawn not found for Test 3." << std::endl;
        return;
    }
    board.movePiece(blackPawnId1, 3, 3); // D7 to D5

    // White Pawn captures Black Pawn at D5
    std::pair<bool, Piece*> captureResult1 = board.movePiece(whitePawnId, 3, 3); // F4 to D5
    if (captureResult1.first && captureResult1.second != nullptr) {
        whitePlayer.addCapturedPiece(captureResult1.second);
        std::cout << "White Pawn ID " << whitePawnId << " captured Black Pawn ID " << blackPawnId1 << " successfully." << std::endl;
    }
    else {
        std::cout << "Failed to capture Black Pawn at D5." << std::endl;
    }

    // Move Black Pawn from G7 to G5
    int blackPawnId2 = findPieceId(board.blackPieces, PieceType::PAWN, 6, 1); // G7
    if (blackPawnId2 == -1) {
        std::cout << "Black Pawn not found for Test 3." << std::endl;
        return;
    }
    board.movePiece(blackPawnId2, 6, 3); // G7 to G5

    // White Pawn attempts to capture Black Pawn at G5
    std::pair<bool, Piece*> captureResult2 = board.movePiece(whitePawnId, 6, 3); // D5 to G5
    if (captureResult2.first && captureResult2.second != nullptr) {
        whitePlayer.addCapturedPiece(captureResult2.second);
        std::cout << "White Pawn ID " << whitePawnId << " captured Black Pawn ID " << blackPawnId2 << " successfully." << std::endl;
    }
    else {
        std::cout << "Failed to capture Black Pawn at G5." << std::endl;
    }

    // Verify capturedPieces vector
    if (!whitePlayer.getCapturedPieces().empty()) {
        std::cout << "White Player has captured pieces:" << std::endl;
        whitePlayer.displayCapturedPieces();
    }
    else {
        std::cout << "White Player has no captured pieces." << std::endl;
    }

    // Check if the captured pieces are not alive
    bool allCapturedAlive = false;
    for (const Piece* capturedPiece : whitePlayer.getCapturedPieces()) {
        if (capturedPiece->isAlive()) {
            allCapturedAlive = true;
            break;
        }
    }
    if (!allCapturedAlive) {
        std::cout << "All captured pieces are correctly marked as not alive." << std::endl;
    }
    else {
        std::cout << "Some captured pieces are still marked as alive. Test Failed." << std::endl;
    }

    board.displayBoard();
    std::cout << std::endl;
}

// Test 4: Display Captured Pieces
void testDisplayCapturedPieces() {
    Board board;
    Player whitePlayer(Color::WHITE, true);
    Player blackPlayer(Color::BLACK, true);

    std::cout << "Test 4: Display Captured Pieces" << std::endl;

    // Move White Pawn from G2 to G4
    int whitePawnId = findPieceId(board.whitePieces, PieceType::PAWN, 6, 6); // G2
    if (whitePawnId == -1) {
        std::cout << "White Pawn not found for Test 4." << std::endl;
        return;
    }
    board.movePiece(whitePawnId, 6, 4); // G2 to G4

    // Move Black Pawn from G7 to G5
    int blackPawnId = findPieceId(board.blackPieces, PieceType::PAWN, 6, 1); // G7
    if (blackPawnId == -1) {
        std::cout << "Black Pawn not found for Test 4." << std::endl;
        return;
    }
    board.movePiece(blackPawnId, 6, 3); // G7 to G5

    // White Pawn captures Black Pawn at G5 (valid diagonal capture)
    std::pair<bool, Piece*> captureResult = board.movePiece(whitePawnId, 6, 3); // G4 to G5
    if (captureResult.first && captureResult.second != nullptr) {
        whitePlayer.addCapturedPiece(captureResult.second);
        std::cout << "White Pawn ID " << whitePawnId << " captured Black Pawn ID " << blackPawnId << " successfully." << std::endl;
    }
    else {
        std::cout << "Failed to capture Black Pawn at G5." << std::endl;
    }

    // Display captured pieces
    if (!whitePlayer.getCapturedPieces().empty()) {
        std::cout << "White Player has captured pieces:" << std::endl;
        whitePlayer.displayCapturedPieces();
    }
    else {
        std::cout << "White Player has no captured pieces." << std::endl;
    }

    // Check if the captured pieces are not alive
    bool allCapturedAlive = false;
    for (const Piece* capturedPiece : whitePlayer.getCapturedPieces()) {
        if (capturedPiece->isAlive()) {
            allCapturedAlive = true;
            break;
        }
    }
    if (!allCapturedAlive) {
        std::cout << "All captured pieces are correctly marked as not alive." << std::endl;
    }
    else {
        std::cout << "Some captured pieces are still marked as alive. Test Failed." << std::endl;
    }

    board.displayBoard();
    std::cout << std::endl;
}

// Test 5: Captured Pieces Integrity (Corrected)
void testCapturedPiecesIntegrity() {
    Board board;
    Player whitePlayer(Color::WHITE, true);
    Player blackPlayer(Color::BLACK, true);

    std::cout << "Test 5: Captured Pieces Integrity" << std::endl;

    // Move White Pawn from H2 to H4
    int whitePawnId = findPieceId(board.whitePieces, PieceType::PAWN, 7, 6); // H2
    if (whitePawnId == -1) {
        std::cout << "White Pawn not found for Test 5." << std::endl;
        return;
    }
    board.movePiece(whitePawnId, 7, 4); // H2 to H4

    // Move Black Pawn from H7 to H5
    int blackPawnId = findPieceId(board.blackPieces, PieceType::PAWN, 7, 1); // H7
    if (blackPawnId == -1) {
        std::cout << "Black Pawn not found for Test 5." << std::endl;
        return;
    }
    board.movePiece(blackPawnId, 7, 3); // H7 to H5

    // White Pawn captures Black Pawn at H5 (valid diagonal capture)
    std::pair<bool, Piece*> captureResult = board.movePiece(whitePawnId, 6, 3); // H4 to G5
    if (captureResult.first && captureResult.second != nullptr) {
        whitePlayer.addCapturedPiece(captureResult.second);
        std::cout << "White Pawn ID " << whitePawnId << " captured Black Pawn ID " << blackPawnId << " successfully." << std::endl;
    }
    else {
        std::cout << "Failed to capture Black Pawn at G5." << std::endl;
    }

    // Attempt to access captured piece from blackPieces
    bool foundInBlack = false;
    for (const Piece& piece : board.blackPieces) {
        if (piece.getId() == blackPawnId && piece.isAlive()) {
            foundInBlack = true;
            break;
        }
    }

    if (!foundInBlack) {
        std::cout << "Captured piece ID " << blackPawnId << " is not accessible in Black's pieces." << std::endl;
    }
    else {
        std::cout << "Captured piece ID " << blackPawnId << " is still accessible in Black's pieces. Test Failed." << std::endl;
    }

    // Verify capturedPieces vector
    if (!whitePlayer.getCapturedPieces().empty()) {
        std::cout << "White Player has captured pieces:" << std::endl;
        whitePlayer.displayCapturedPieces();
    }
    else {
        std::cout << "White Player has no captured pieces." << std::endl;
    }

    // Check if the captured pieces are not alive
    bool allCapturedAlive = false;
    for (const Piece* capturedPiece : whitePlayer.getCapturedPieces()) {
        if (capturedPiece->isAlive()) {
            allCapturedAlive = true;
            break;
        }
    }
    if (!allCapturedAlive) {
        std::cout << "All captured pieces are correctly marked as not alive." << std::endl;
    }
    else {
        std::cout << "Some captured pieces are still marked as alive. Test Failed." << std::endl;
    }

    board.displayBoard();
    std::cout << std::endl;
}

int main() {
    testCapturePiece();
    testInvalidCapture();
    testCapturedPiecesStorage();
    testDisplayCapturedPieces();
    testCapturedPiecesIntegrity();
    return 0;
}
