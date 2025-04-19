/**
 * @file Board.cpp
 * @brief Implementation of the Board class methods for managing the chess game state.
 *
 * This file provides the implementation of the Board class defined in Board.h, including
 * initialization of the board with pieces, move execution, check and checkmate detection,
 * and saving/loading game state to a file. The Board class uses advanced C++ features such as
 * STL containers (vector, array, stack) to manage collections of pieces and moves, and
 * an overloaded assignment operator for copying board state.
 */
#include "Board.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <stdexcept>

Board::Board() {
    // Initialize the board array with null pointers (no pieces placed yet).
    for (auto& row : boardArray) {
        row.fill(nullptr);
    }
    gameRunning = true;
    currentPlayerColor = Color::WHITE;
    // Reserve space for pieces to avoid reallocation (we know each side has 16 pieces initially).
    whitePieces.reserve(16);
    blackPieces.reserve(16);

    // Lambda function to create a piece and place it on the board.
    auto createAndPlacePiece = [this](PieceType type, Color color, int id, int x, int y) {
        Piece piece;
        piece.setType(type);
        piece.setColor(color);
        piece.setId(id);
        piece.setLocation(x, y);
        piece.setIsAlive(true);
        if (color == Color::WHITE) {
            whitePieces.push_back(piece);
            boardArray[y][x] = &whitePieces.back();
        }
        else {
            blackPieces.push_back(piece);
            boardArray[y][x] = &blackPieces.back();
        }
        };

    // Set up White pieces (White starts at y=6 for pawns and y=7 for other pieces).
    int idCounter = 1;
    for (int i = 0; i < 8; ++i) {
        createAndPlacePiece(PieceType::PAWN, Color::WHITE, idCounter++, i, 6);
    }
    createAndPlacePiece(PieceType::ROOK, Color::WHITE, idCounter++, 0, 7);
    createAndPlacePiece(PieceType::KNIGHT, Color::WHITE, idCounter++, 1, 7);
    createAndPlacePiece(PieceType::BISHOP, Color::WHITE, idCounter++, 2, 7);
    createAndPlacePiece(PieceType::QUEEN, Color::WHITE, idCounter++, 3, 7);
    createAndPlacePiece(PieceType::KING, Color::WHITE, idCounter++, 4, 7);
    createAndPlacePiece(PieceType::BISHOP, Color::WHITE, idCounter++, 5, 7);
    createAndPlacePiece(PieceType::KNIGHT, Color::WHITE, idCounter++, 6, 7);
    createAndPlacePiece(PieceType::ROOK, Color::WHITE, idCounter++, 7, 7);

    // Set up Black pieces (Black starts at y=1 for pawns and y=0 for other pieces).
    for (int i = 0; i < 8; ++i) {
        createAndPlacePiece(PieceType::PAWN, Color::BLACK, idCounter++, i, 1);
    }
    createAndPlacePiece(PieceType::ROOK, Color::BLACK, idCounter++, 0, 0);
    createAndPlacePiece(PieceType::KNIGHT, Color::BLACK, idCounter++, 1, 0);
    createAndPlacePiece(PieceType::BISHOP, Color::BLACK, idCounter++, 2, 0);
    createAndPlacePiece(PieceType::QUEEN, Color::BLACK, idCounter++, 3, 0);
    createAndPlacePiece(PieceType::KING, Color::BLACK, idCounter++, 4, 0);
    createAndPlacePiece(PieceType::BISHOP, Color::BLACK, idCounter++, 5, 0);
    createAndPlacePiece(PieceType::KNIGHT, Color::BLACK, idCounter++, 6, 0);
    createAndPlacePiece(PieceType::ROOK, Color::BLACK, idCounter++, 7, 0);
}

Board::Board(const Board& other) {
    // Copy basic state flags.
    gameRunning = other.gameRunning;
    currentPlayerColor = other.currentPlayerColor;
    // Copy piece lists (vector copy will duplicate Piece objects).
    whitePieces = other.whitePieces;
    blackPieces = other.blackPieces;
    // Rebuild boardArray pointers to point to the pieces in the copied vectors.
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            Piece* piece = other.boardArray[y][x];
            if (piece && piece->isAlive()) {
                // Find the corresponding piece in the copied whitePieces or blackPieces by ID.
                auto it = std::find_if(whitePieces.begin(), whitePieces.end(),
                    [&](const Piece& p) { return p.getId() == piece->getId(); });
                if (it != whitePieces.end()) {
                    boardArray[y][x] = &(*it);
                }
                else {
                    it = std::find_if(blackPieces.begin(), blackPieces.end(),
                        [&](const Piece& p) { return p.getId() == piece->getId(); });
                    if (it != blackPieces.end()) {
                        boardArray[y][x] = &(*it);
                    }
                    else {
                        boardArray[y][x] = nullptr;
                    }
                }
            }
            else {
                boardArray[y][x] = nullptr;
            }
        }
    }
    // Copy move history stack (shallow copy of Moves, which is fine as they contain pointers and ids).
    moveHistory = other.moveHistory;
}

Board& Board::operator=(const Board& other) {
    if (this == &other) {
        return *this;
    }
    // Copy basic state flags.
    gameRunning = other.gameRunning;
    currentPlayerColor = other.currentPlayerColor;
    // Copy piece lists.
    whitePieces = other.whitePieces;
    blackPieces = other.blackPieces;
    // Rebuild boardArray similar to copy constructor.
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            Piece* piece = other.boardArray[y][x];
            if (piece && piece->isAlive()) {
                auto it = std::find_if(whitePieces.begin(), whitePieces.end(),
                    [&](const Piece& p) { return p.getId() == piece->getId(); });
                if (it != whitePieces.end()) {
                    boardArray[y][x] = &(*it);
                }
                else {
                    it = std::find_if(blackPieces.begin(), blackPieces.end(),
                        [&](const Piece& p) { return p.getId() == piece->getId(); });
                    if (it != blackPieces.end()) {
                        boardArray[y][x] = &(*it);
                    }
                    else {
                        boardArray[y][x] = nullptr;
                    }
                }
            }
            else {
                boardArray[y][x] = nullptr;
            }
        }
    }
    moveHistory = other.moveHistory;
    return *this;
}

void Board::displayBoard() const {
    // Display column labels
    std::cout << "  A B C D E F G H\n";
    for (int row = 0; row < 8; ++row) {
        std::cout << 8 - row << " ";  // Display row numbers 8 to 1.
        for (int col = 0; col < 8; ++col) {
            Piece* piece = boardArray[row][col];
            if (piece && piece->isAlive()) {
                std::cout << getSymbol(*piece) << " ";
            }
            else {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "Current Player: " << (currentPlayerColor == Color::WHITE ? "White" : "Black") << "\n";
    // Warn if current player's king is in check.
    if (isPlayerInCheck(currentPlayerColor)) {
        std::cout << "You are in check!\n";
    }
}

Piece* Board::getPieceAt(int x, int y) const {
    // Return the piece pointer at the given coordinates if within bounds and occupied.
    if (x >= 0 && x < 8 && y >= 0 && y < 8) {
        Piece* piece = boardArray[y][x];
        if (piece && piece->isAlive()) {
            return piece;
        }
    }
    return nullptr;
}

SquareStatus Board::getSquareStatus(int x, int y) const {
    SquareStatus status;
    // If out of bounds, return unoccupied status.
    if (x < 0 || x >= 8 || y < 0 || y >= 8) {
        status.isOccupied = false;
        return status;
    }
    Piece* piece = boardArray[y][x];
    if (piece && piece->isAlive()) {
        status.isOccupied = true;
        status.pieceType = piece->getType();
        status.pieceColor = piece->getColor();
        status.pieceId = piece->getId();
    }
    else {
        status.isOccupied = false;
    }
    return status;
}

std::pair<bool, Piece*> Board::movePiece(int pieceId, int newX, int newY) {
    // Find the piece by ID.
    Piece* piece = getPieceById(pieceId);
    if (!piece || !piece->isAlive()) {
        return { false, nullptr };  // Piece not found or already captured.
    }
    // Enforce turn order: only move if it's this piece's color's turn.
    if (piece->getColor() != currentPlayerColor) {
        return { false, nullptr };
    }
    // Get all valid moves for this piece and check if desired move is among them.
    std::vector<std::pair<int, int>> validMoves = piece->getAllValidMoves(*this);
    auto it = std::find(validMoves.begin(), validMoves.end(), std::make_pair(newX, newY));
    if (it == validMoves.end()) {
        return { false, nullptr };  // Move not in list of valid moves.
    }
    // Save original position.
    int oldX = piece->getX();
    int oldY = piece->getY();
    // Check if there's a piece at the destination (potential capture).
    Piece* capturedPiece = boardArray[newY][newX];
    if (capturedPiece && capturedPiece->getColor() != piece->getColor()) {
        // Capture the opponent's piece.
        capturedPiece->setIsAlive(false);
        // Remove the captured piece from the board.
        boardArray[newY][newX] = nullptr;
    }
    // Move the piece: clear its old position and update its coordinates.
    boardArray[oldY][oldX] = nullptr;
    piece->setLocation(newX, newY);
    boardArray[newY][newX] = piece;
    // Pawn promotion: if a pawn reaches the opposite end, auto-promote to Queen by default.
    if (piece->getType() == PieceType::PAWN && (newY == 0 || newY == 7)) {
        piece->setType(PieceType::QUEEN);
    }
    // Record this move in the move history stack.
    Move lastMove = { pieceId, {oldX, oldY}, {newX, newY}, capturedPiece };
    moveHistory.push(lastMove);
    // Switch turn to the other player.
    currentPlayerColor = (currentPlayerColor == Color::WHITE) ? Color::BLACK : Color::WHITE;
    // Check if this move has delivered checkmate to the opponent.
    if (isCheckmate(currentPlayerColor)) {
        gameRunning = false;
        std::cout << (currentPlayerColor == Color::WHITE ? "Black" : "White") << " wins by checkmate!\n";
    }
    return { true, capturedPiece };
}

Piece* Board::getPieceById(int pieceId) {
    // Search in white pieces first.
    for (Piece& p : whitePieces) {
        if (p.getId() == pieceId && p.isAlive()) {
            return &p;
        }
    }
    // Then search in black pieces.
    for (Piece& p : blackPieces) {
        if (p.getId() == pieceId && p.isAlive()) {
            return &p;
        }
    }
    return nullptr;
}

bool Board::isPlayerInCheck(Color playerColor) const {
    // Locate the king of the given color.
    Piece* king = nullptr;
    const std::vector<Piece>& pieces = (playerColor == Color::WHITE) ? whitePieces : blackPieces;
    for (const Piece& piece : pieces) {
        if (piece.getType() == PieceType::KING && piece.isAlive()) {
            king = const_cast<Piece*>(&piece);
            break;
        }
    }
    if (!king) {
        return false;
    }
    // Check all enemy pieces to see if any can move to the king's position.
    const std::vector<Piece>& enemyPieces = (playerColor == Color::WHITE) ? blackPieces : whitePieces;
    for (const Piece& enemy : enemyPieces) {
        if (enemy.isAlive()) {
            std::vector<std::pair<int, int>> enemyMoves = enemy.getAllValidMoves(*this);
            for (const auto& move : enemyMoves) {
                if (move.first == king->getX() && move.second == king->getY()) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::isCheckmate(Color playerColor) {
    // If the player is not in check, it can't be checkmate.
    if (!isPlayerInCheck(playerColor)) {
        return false;
    }
    // Try all possible moves for all pieces of the player. If any move results in the player no longer being in check, it's not checkmate.
    std::vector<Piece>& pieces = (playerColor == Color::WHITE) ? whitePieces : blackPieces;
    for (Piece& piece : pieces) {
        if (piece.isAlive()) {
            std::vector<std::pair<int, int>> moves = piece.getAllValidMoves(*this);
            for (const auto& move : moves) {
                Piece* capturedPiece = makeMoveForCheck(piece.getId(), move.first, move.second);
                bool stillInCheck = isPlayerInCheck(playerColor);
                undoMoveForCheck();
                if (!stillInCheck) {
                    return false;  // Found a move that escapes check.
                }
            }
        }
    }
    return true;  // No move can escape check: checkmate.
}

Piece* Board::makeMoveForCheck(int pieceId, int newX, int newY) {
    // Similar to movePiece but used for hypothetical moves (does not switch turn or permanently update moveHistory beyond this function).
    Piece* piece = getPieceById(pieceId);
    if (!piece) {
        return nullptr;
    }
    int oldX = piece->getX();
    int oldY = piece->getY();
    Piece* capturedPiece = boardArray[newY][newX];
    if (capturedPiece && capturedPiece->getColor() != piece->getColor()) {
        capturedPiece->setIsAlive(false);
        boardArray[newY][newX] = nullptr;
    }
    boardArray[oldY][oldX] = nullptr;
    piece->setLocation(newX, newY);
    boardArray[newY][newX] = piece;
    // Push this hypothetical move on the stack for undo.
    Move tempMove = { pieceId, {oldX, oldY}, {newX, newY}, capturedPiece };
    moveHistory.push(tempMove);
    return capturedPiece;
}

void Board::undoMoveForCheck() {
    if (moveHistory.empty()) {
        return;
    }
    Move lastMove = moveHistory.top();
    moveHistory.pop();
    Piece* piece = getPieceById(lastMove.pieceId);
    if (!piece) {
        return;
    }
    // Restore piece's original position.
    boardArray[lastMove.to.second][lastMove.to.first] = nullptr;
    piece->setLocation(lastMove.from.first, lastMove.from.second);
    boardArray[lastMove.from.second][lastMove.from.first] = piece;
    // Revive any captured piece (undo capture).
    if (lastMove.capturedPiece) {
        lastMove.capturedPiece->setIsAlive(true);
        boardArray[lastMove.to.second][lastMove.to.first] = lastMove.capturedPiece;
    }
}

void Board::setGameRunning(bool running) {
    gameRunning = running;
}

bool Board::isGameRunning() const {
    return gameRunning;
}

bool Board::isPlayerChecked() {
    // Convenience function to check current player's check status.
    return isPlayerInCheck(currentPlayerColor);
}

bool Board::checkMate() {
    // Convenience function to check current player's checkmate status.
    return isCheckmate(currentPlayerColor);
}

std::string Board::getSymbol(const Piece& piece) const {
    // Map each piece type to its display symbol.
    static const std::unordered_map<PieceType, std::string> typeToSymbol = {
        {PieceType::PAWN,   "P"},
        {PieceType::KNIGHT, "N"},
        {PieceType::BISHOP, "B"},
        {PieceType::ROOK,   "R"},
        {PieceType::QUEEN,  "Q"},
        {PieceType::KING,   "K"}
    };
    auto it = typeToSymbol.find(piece.getType());
    if (it != typeToSymbol.end()) {
        std::string symbol = it->second;
        // Use lowercase symbol for black pieces, uppercase for white.
        if (piece.getColor() == Color::BLACK) {
            symbol[0] = std::tolower(symbol[0]);
        }
        return symbol;
    }
    return ".";
}

void Board::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open file for saving: " + filename);
    }
    // Write current player's turn.
    outFile << "CurrentPlayer: " << (currentPlayerColor == Color::WHITE ? "White" : "Black") << "\n";
    // Write all white pieces.
    outFile << "WhitePieces:\n";
    for (const Piece& p : whitePieces) {
        // Convert piece type to string.
        std::string typeStr;
        switch (p.getType()) {
        case PieceType::PAWN:   typeStr = "PAWN"; break;
        case PieceType::KNIGHT: typeStr = "KNIGHT"; break;
        case PieceType::BISHOP: typeStr = "BISHOP"; break;
        case PieceType::ROOK:   typeStr = "ROOK"; break;
        case PieceType::QUEEN:  typeStr = "QUEEN"; break;
        case PieceType::KING:   typeStr = "KING"; break;
        }
        int aliveFlag = p.isAlive() ? 1 : 0;
        int px = p.isAlive() ? p.getX() : -1;
        int py = p.isAlive() ? p.getY() : -1;
        outFile << p.getId() << " " << typeStr << " " << aliveFlag << " " << px << " " << py << "\n";
    }
    // Write all black pieces.
    outFile << "BlackPieces:\n";
    for (const Piece& p : blackPieces) {
        std::string typeStr;
        switch (p.getType()) {
        case PieceType::PAWN:   typeStr = "PAWN"; break;
        case PieceType::KNIGHT: typeStr = "KNIGHT"; break;
        case PieceType::BISHOP: typeStr = "BISHOP"; break;
        case PieceType::ROOK:   typeStr = "ROOK"; break;
        case PieceType::QUEEN:  typeStr = "QUEEN"; break;
        case PieceType::KING:   typeStr = "KING"; break;
        }
        int aliveFlag = p.isAlive() ? 1 : 0;
        int px = p.isAlive() ? p.getX() : -1;
        int py = p.isAlive() ? p.getY() : -1;
        outFile << p.getId() << " " << typeStr << " " << aliveFlag << " " << px << " " << py << "\n";
    }
    outFile.close();
}

void Board::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        throw std::runtime_error("Failed to open file for loading: " + filename);
    }
    // Clear current board state.
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            boardArray[y][x] = nullptr;
        }
    }
    whitePieces.clear();
    blackPieces.clear();
    whitePieces.reserve(16);
    blackPieces.reserve(16);
    while (!moveHistory.empty()) {
        moveHistory.pop();
    }

    std::string line;
    // Read current player line.
    if (!std::getline(inFile, line)) {
        throw std::runtime_error("Failed to read from save file (empty file).");
    }
    std::string currentPlayerToken = "CurrentPlayer:";
    if (line.rfind(currentPlayerToken, 0) != 0) {
        throw std::runtime_error("Save file format error: missing CurrentPlayer line.");
    }
    // Extract color from the line.
    std::string colorStr = line.substr(currentPlayerToken.size());
    // Trim any whitespace from colorStr.
    colorStr.erase(0, colorStr.find_first_not_of(" :\t"));  // remove leading spaces and colon
    colorStr.erase(colorStr.find_last_not_of(" \t") + 1);   // remove trailing spaces
    if (colorStr == "White") {
        currentPlayerColor = Color::WHITE;
    }
    else if (colorStr == "Black") {
        currentPlayerColor = Color::BLACK;
    }
    else {
        throw std::runtime_error("Save file format error: invalid player color.");
    }

    // Expect "WhitePieces:" label.
    if (!std::getline(inFile, line) || line.find("WhitePieces:") == std::string::npos) {
        throw std::runtime_error("Save file format error: missing WhitePieces section.");
    }
    // Read 16 white pieces.
    for (int i = 0; i < 16; ++i) {
        int id, aliveFlag, x, y;
        std::string typeStr;
        if (!(inFile >> id >> typeStr >> aliveFlag >> x >> y)) {
            throw std::runtime_error("Save file format error: insufficient white piece data.");
        }
        // Convert type string to PieceType.
        PieceType type;
        if (typeStr == "PAWN") type = PieceType::PAWN;
        else if (typeStr == "KNIGHT") type = PieceType::KNIGHT;
        else if (typeStr == "BISHOP") type = PieceType::BISHOP;
        else if (typeStr == "ROOK") type = PieceType::ROOK;
        else if (typeStr == "QUEEN") type = PieceType::QUEEN;
        else if (typeStr == "KING") type = PieceType::KING;
        else {
            throw std::runtime_error("Save file format error: unknown piece type '" + typeStr + "'.");
        }
        bool isAlive = (aliveFlag == 1);
        Piece piece;
        piece.setId(id);
        piece.setType(type);
        piece.setColor(Color::WHITE);
        piece.setIsAlive(isAlive);
        // If piece is alive, set its location and place it on board; if not alive, use -1,-1 as placeholder location.
        if (isAlive) {
            piece.setLocation(x, y);
            boardArray[y][x] = &piece;
        }
        else {
            piece.setLocation(x, y);
        }
        whitePieces.push_back(piece);
        // After push_back, update the board pointer to this piece (address might have changed).
        if (isAlive) {
            boardArray[y][x] = &whitePieces.back();
        }
    }
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // consume the rest of the line if any

    // Expect "BlackPieces:" label.
    if (!std::getline(inFile, line) || line.find("BlackPieces:") == std::string::npos) {
        throw std::runtime_error("Save file format error: missing BlackPieces section.");
    }
    // Read 16 black pieces.
    for (int i = 0; i < 16; ++i) {
        int id, aliveFlag, x, y;
        std::string typeStr;
        if (!(inFile >> id >> typeStr >> aliveFlag >> x >> y)) {
            throw std::runtime_error("Save file format error: insufficient black piece data.");
        }
        PieceType type;
        if (typeStr == "PAWN") type = PieceType::PAWN;
        else if (typeStr == "KNIGHT") type = PieceType::KNIGHT;
        else if (typeStr == "BISHOP") type = PieceType::BISHOP;
        else if (typeStr == "ROOK") type = PieceType::ROOK;
        else if (typeStr == "QUEEN") type = PieceType::QUEEN;
        else if (typeStr == "KING") type = PieceType::KING;
        else {
            throw std::runtime_error("Save file format error: unknown piece type '" + typeStr + "'.");
        }
        bool isAlive = (aliveFlag == 1);
        Piece piece;
        piece.setId(id);
        piece.setType(type);
        piece.setColor(Color::BLACK);
        piece.setIsAlive(isAlive);
        if (isAlive) {
            piece.setLocation(x, y);
            boardArray[y][x] = &piece;
        }
        else {
            piece.setLocation(x, y);
        }
        blackPieces.push_back(piece);
        if (isAlive) {
            boardArray[y][x] = &blackPieces.back();
        }
    }
    // Set game as running since we loaded a game in progress (the player whose turn is currentPlayerColor will move next).
    gameRunning = true;
    inFile.close();
}

std::stack<Move> Board::getMoveHistory() const {
    return moveHistory;
}
