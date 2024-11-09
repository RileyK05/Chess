// Board.cpp

#include "Board.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <unordered_map>

Board::Board() {
    for (auto& row : boardArray) {
        row.fill(nullptr);
    }
    gameRunning = true;
    currentPlayerColor = Color::WHITE;
    whitePieces.reserve(16);
    blackPieces.reserve(16);
    auto createAndPlacePiece = [this](PieceType type, Color color, int id, int x, int y) {
        Piece piece;
        piece.setType(type);
        piece.setColor(color);
        piece.setId(id);
        piece.setLocation(x, y);
        if (color == Color::WHITE) {
            whitePieces.push_back(piece);
            boardArray[y][x] = &whitePieces.back();
        }
        else {
            blackPieces.push_back(piece);
            boardArray[y][x] = &blackPieces.back();
        }
        };
    int idCounter = 1;
    for (int i = 0; i < 8; i++) {
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
    for (int i = 0; i < 8; i++) {
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
    gameRunning = other.gameRunning;
    currentPlayerColor = other.currentPlayerColor;
    whitePieces = other.whitePieces;
    blackPieces = other.blackPieces;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            Piece* piece = other.boardArray[y][x];
            if (piece) {
                auto it = std::find_if(whitePieces.begin(), whitePieces.end(), [&](const Piece& p) { return p.getId() == piece->getId(); });
                if (it != whitePieces.end()) {
                    boardArray[y][x] = &(*it);
                }
                else {
                    it = std::find_if(blackPieces.begin(), blackPieces.end(), [&](const Piece& p) { return p.getId() == piece->getId(); });
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
}

Board& Board::operator=(const Board& other) {
    if (this == &other) return *this;
    whitePieces = other.whitePieces;
    blackPieces = other.blackPieces;
    gameRunning = other.gameRunning;
    currentPlayerColor = other.currentPlayerColor;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            Piece* piece = other.boardArray[y][x];
            if (piece) {
                auto it = std::find_if(whitePieces.begin(), whitePieces.end(), [&](const Piece& p) { return p.getId() == piece->getId(); });
                if (it != whitePieces.end()) {
                    boardArray[y][x] = &(*it);
                }
                else {
                    it = std::find_if(blackPieces.begin(), blackPieces.end(), [&](const Piece& p) { return p.getId() == piece->getId(); });
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
    std::cout << "  A B C D E F G H\n";
    for (int row = 0; row < 8; row++) {
        std::cout << 8 - row << " ";
        for (int col = 0; col < 8; col++) {
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
    if (isPlayerInCheck(currentPlayerColor)) {
        std::cout << "You are in check!\n";
    }
}

Piece* Board::getPieceAt(int x, int y) const {
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
    Piece* piece = getPieceById(pieceId);
    if (!piece || !piece->isAlive()) {
        return { false, nullptr };
    }
    if (piece->getColor() != currentPlayerColor) {
        return { false, nullptr };
    }
    std::vector<std::pair<int, int>> validMoves = piece->getAllValidMoves(*this);
    auto it = std::find(validMoves.begin(), validMoves.end(), std::make_pair(newX, newY));
    if (it == validMoves.end()) {
        return { false, nullptr };
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
    if (piece->getType() == PieceType::PAWN && (newY == 0 || newY == 7)) {
        piece->setType(PieceType::QUEEN);
    }
    Move lastMove = { pieceId, {oldX, oldY}, {newX, newY}, capturedPiece };
    moveHistory.push(lastMove);
    currentPlayerColor = (currentPlayerColor == Color::WHITE) ? Color::BLACK : Color::WHITE;
    if (isCheckmate(currentPlayerColor)) {
        gameRunning = false;
        std::cout << (currentPlayerColor == Color::WHITE ? "Black" : "White") << " wins by checkmate!\n";
    }
    return { true, capturedPiece };
}

Piece* Board::getPieceById(int pieceId) {
    for (Piece& p : whitePieces) {
        if (p.getId() == pieceId && p.isAlive()) {
            return &p;
        }
    }
    for (Piece& p : blackPieces) {
        if (p.getId() == pieceId && p.isAlive()) {
            return &p;
        }
    }
    return nullptr;
}

bool Board::isPlayerInCheck(Color playerColor) const {
    Piece* king = nullptr;
    const std::vector<Piece>& pieces = (playerColor == Color::WHITE) ? whitePieces : blackPieces;
    for (const Piece& piece : pieces) {
        if (piece.getType() == PieceType::KING && piece.isAlive()) {
            king = const_cast<Piece*>(&piece);
            break;
        }
    }
    if (!king) return false;
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
    if (!isPlayerInCheck(playerColor)) {
        return false;
    }
    std::vector<Piece>& pieces = (playerColor == Color::WHITE) ? whitePieces : blackPieces;
    for (Piece& piece : pieces) {
        if (piece.isAlive()) {
            std::vector<std::pair<int, int>> moves = piece.getAllValidMoves(*this);
            for (const auto& move : moves) {
                Piece* capturedPiece = makeMoveForCheck(piece.getId(), move.first, move.second);
                bool stillInCheck = isPlayerInCheck(playerColor);
                undoMoveForCheck();
                if (!stillInCheck) {
                    return false;
                }
            }
        }
    }
    return true;
}

Piece* Board::makeMoveForCheck(int pieceId, int newX, int newY) {
    Piece* piece = getPieceById(pieceId);
    if (!piece) return nullptr;
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
    Move tempMove = { pieceId, {oldX, oldY}, {newX, newY}, capturedPiece };
    moveHistory.push(tempMove);
    return capturedPiece;
}

void Board::undoMoveForCheck() {
    if (moveHistory.empty()) return;
    Move lastMove = moveHistory.top();
    moveHistory.pop();
    Piece* piece = getPieceById(lastMove.pieceId);
    if (!piece) return;
    boardArray[lastMove.to.second][lastMove.to.first] = nullptr;
    piece->setLocation(lastMove.from.first, lastMove.from.second);
    boardArray[lastMove.from.second][lastMove.from.first] = piece;
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
    return isPlayerInCheck(currentPlayerColor);
}

bool Board::checkMate() {
    return isCheckmate(currentPlayerColor);
}

std::string Board::getSymbol(const Piece& piece) const {
    static const std::unordered_map<PieceType, std::string> typeToSymbol = {
        {PieceType::PAWN, "P"},
        {PieceType::KNIGHT, "N"},
        {PieceType::ROOK, "R"},
        {PieceType::BISHOP, "B"},
        {PieceType::QUEEN, "Q"},
        {PieceType::KING, "K"}
    };
    auto it = typeToSymbol.find(piece.getType());
    if (it != typeToSymbol.end()) {
        std::string symbol = it->second;
        if (piece.getColor() == Color::BLACK) {
            symbol[0] = std::tolower(symbol[0]);
        }
        return symbol;
    }
    return ".";
}
