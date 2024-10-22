#include "Board.h"
#include <iostream>
#include <cctype> // For std::tolower

// ======= Piece Class Implementation =======

Piece::Piece()
    : x(0), y(0), id(0), alive(true), type(PieceType::PAWN), color(Color::WHITE) {
}

// Getters
int Piece::getX() const { return x; }
int Piece::getY() const { return y; }
int Piece::getId() const { return id; }
PieceType Piece::getType() const { return type; }
Color Piece::getColor() const { return color; }
bool Piece::isAlive() const { return alive; }

// Setters
void Piece::setLocation(int newX, int newY) {
    x = newX;
    y = newY;
}

void Piece::setIsAlive(bool newAlive) {
    alive = newAlive;
}

void Piece::setId(int newId) {
    id = newId;
}

void Piece::setType(PieceType newType) {
    type = newType;
}

void Piece::setColor(Color newColor) {
    color = newColor;
}

// Methods
std::vector<std::pair<int, int>> Piece::getAllValidMoves(const Board& board) const {
    std::vector<std::pair<int, int>> validMoves;

    switch (type) {
        case PieceType::PAWN:
            int pieceId = getId();
            Piece* currentPiece = board.getPieceAt(getX(), getY());

            break;

        case PieceType::ROOK:
            break;

        case PieceType::KNIGHT:
            break;

        case PieceType::BISHOP:
            break;

        case PieceType::QUEEN:
            break;

        case PieceType::KING:
            break;
    }

    return validMoves;
}

bool Piece::isMoveValid(int newX, int newY, const Board& board) const {
    // Move validation logic will be implemented later
    return false;
}

// ======= Board Class Implementation =======

Board::Board() {
    for (auto& row : boardArray) {
        row.fill(nullptr);
    }

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
    for (int i = 0; i < 8; ++i) {
        createAndPlacePiece(PieceType::PAWN, Color::WHITE, idCounter++, i, 1);
    }
    createAndPlacePiece(PieceType::ROOK, Color::WHITE, idCounter++, 0, 0);
    createAndPlacePiece(PieceType::KNIGHT, Color::WHITE, idCounter++, 1, 0);
    createAndPlacePiece(PieceType::BISHOP, Color::WHITE, idCounter++, 2, 0);
    createAndPlacePiece(PieceType::QUEEN, Color::WHITE, idCounter++, 3, 0);
    createAndPlacePiece(PieceType::KING, Color::WHITE, idCounter++, 4, 0);
    createAndPlacePiece(PieceType::BISHOP, Color::WHITE, idCounter++, 5, 0);
    createAndPlacePiece(PieceType::KNIGHT, Color::WHITE, idCounter++, 6, 0);
    createAndPlacePiece(PieceType::ROOK, Color::WHITE, idCounter++, 7, 0);

    for (int i = 0; i < 8; ++i) {
        createAndPlacePiece(PieceType::PAWN, Color::BLACK, idCounter++, i, 6);
    }
    createAndPlacePiece(PieceType::ROOK, Color::BLACK, idCounter++, 0, 7);
    createAndPlacePiece(PieceType::KNIGHT, Color::BLACK, idCounter++, 1, 7);
    createAndPlacePiece(PieceType::BISHOP, Color::BLACK, idCounter++, 2, 7);
    createAndPlacePiece(PieceType::QUEEN, Color::BLACK, idCounter++, 3, 7);
    createAndPlacePiece(PieceType::KING, Color::BLACK, idCounter++, 4, 7);
    createAndPlacePiece(PieceType::BISHOP, Color::BLACK, idCounter++, 5, 7);
    createAndPlacePiece(PieceType::KNIGHT, Color::BLACK, idCounter++, 6, 7);
    createAndPlacePiece(PieceType::ROOK, Color::BLACK, idCounter++, 7, 7);
}

void Board::displayBoard() const {
    std::cout << "  ";
    for (int col = 0; col < 8; ++col) {
        char colLabel = 'A' + col;
        std::cout << colLabel << " ";
    }
    std::cout << "\n";

    for (int row = 0; row < 8; ++row) {
        std::cout << row + 1 << " ";
        for (int col = 0; col < 8; ++col) {
            Piece* piece = boardArray[row][col];
            if (piece != nullptr && piece->isAlive()) {
                std::cout << getSymbol(*piece) << " ";
            }
            else {
                std::cout << "~ ";
            }
        }
        std::cout << "\n";
    }
}

Piece* Board::getPieceAt(int x, int y) const {
    if (x >= 0 && x < 8 && y >= 0 && y < 8) {
        return boardArray[y][x];
    }
    return nullptr;
}


void Board::updateBoard() {
    // Implementation will be added later
}

void Board::updatePieceStatus() {
    for (const Piece& piece : whitePieces) {
        aliveCheckWhite[piece.getId()] = piece.isAlive();
    }
    for (const Piece& piece : blackPieces) {
        aliveCheckBlack[piece.getId()] = piece.isAlive();
    }
}

int Board::getSquareStatus(int x, int y) const {
    if (x < 0 || x >= 8 || y < 0 || y >= 8) {
        return -1; 
    }

    Piece* piece = boardArray[y][x];
    if (piece != nullptr && piece->isAlive()) {
        return piece->getId(); 
    }

    return -1; 
}


bool Board::movePiece(int pieceId, int newX, int newY) {
    // Move execution logic will be implemented later
    return false;
}

std::array<std::array<int, 8>, 8> Board::getCurrentIdPlacement() const {
    std::array<std::array<int, 8>, 8> idPlacement = {};
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = boardArray[row][col];
            if (piece != nullptr && piece->isAlive()) {
                idPlacement[row][col] = piece->getId();
            }
            else {
                idPlacement[row][col] = -1; 
            }
        }
    }
    return idPlacement;
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
    return "~";
}
