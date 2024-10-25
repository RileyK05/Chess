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
        case PieceType::PAWN: {
            int newX = getX();
            int newY = getY();

            int direction = (getColor() == Color::WHITE) ? 1 : -1; 

            if (isMoveValid(newX, newY + direction, board)) {
                if (!board.getSquareStatus(newX, newY + direction).isOccupied) {
                    validMoves.push_back({ newX, newY + direction });
                }
            }

            if ((getColor() == Color::WHITE && newY == 1) || (getColor() == Color::BLACK && newY == 6)) {
                if (isMoveValid(newX, newY + 2 * direction, board)) {
                    if (!board.getSquareStatus(newX, newY + direction).isOccupied && !board.getSquareStatus(newX, newY + 2 * direction).isOccupied) {
                        validMoves.push_back({ newX, newY + 2 * direction });
                    }
                }
            }

            for (int dx : {-1, 1}) {
                if (isMoveValid(newX + dx, newY + direction, board)) {
                    SquareStatus status = board.getSquareStatus(newX + dx, newY + direction);
                    if (status.isOccupied && status.pieceColor != getColor()) {
                        validMoves.push_back({ newX + dx, newY + direction });
                    }
                }
            }
            break;
        }
        case PieceType::ROOK: {
            std::array<std::pair<int, int>, 4> directions = {
                std::make_pair(1, 0),
                std::make_pair(-1, 0), 
                std::make_pair(0, 1),
                std::make_pair(0, -1)
            };

            for (const std::pair<int,int>& dir : directions) {
                int dirX = dir.first;
                int dirY = dir.second;

                int currentX = getX() + dirX;
                int currentY = getY() + dirY;

                while (currentX >= 0 && currentY < 8 && currentY >= 0 && currentX < 8 && isMoveValid(currentX, currentY, board)) {
                    SquareStatus squareStatus = board.getSquareStatus(currentX, currentY);
                    if (squareStatus.isOccupied) {
                        if (squareStatus.pieceColor != getColor()) {
                            validMoves.push_back({ currentX, currentY });
                        }
                        break;
                    }
                    validMoves.push_back({ currentX, currentY });

                    currentX += dir.first;
                    currentY += dir.second;
                }
            }

            break;
        }
        case PieceType::KNIGHT: {
            std::array<std::pair<int, int>, 8> directions = {
                std::make_pair(2, 1),
                std::make_pair(2, -1),
                std::make_pair(-2, 1),
                std::make_pair(-2, -1),
                std::make_pair(1, 2),
                std::make_pair(1, -2),
                std::make_pair(-1, 2),
                std::make_pair(-1, -2)
            };

            for (const std::pair<int, int>& dir : directions) {
                int newX = getX() + dir.first;
                int newY = getY() + dir.second;

                if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 && isMoveValid(newX, newY, board)) {
                    SquareStatus squareStatus = board.getSquareStatus(newX, newY);
                    if (!squareStatus.isOccupied || squareStatus.pieceColor != getColor()) {
                        validMoves.push_back({ newX, newY });
                    }
                }
            }
            break;
        }
        case PieceType::BISHOP: {
            std::array<std::pair<int, int>, 4> directions = {
                std::make_pair(1, 1),
                std::make_pair(-1, 1),
                std::make_pair(1, -1),
                std::make_pair(-1, -1)
            };


            for (const std::pair<int, int>& dir : directions) {
                int dirX = dir.first;
                int dirY = dir.second;

                int currentX = getX() + dirX;
                int currentY = getY() + dirY;

                while (currentX >= 0 && currentY < 8 && currentY >= 0 && currentX < 8 && isMoveValid(currentX, currentY, board)) {
                    SquareStatus squareStatus = board.getSquareStatus(currentX, currentY);
                    if (squareStatus.isOccupied) {
                        if (squareStatus.pieceColor != getColor()) {
                            validMoves.push_back({ currentX, currentY });
                        }
                        break;
                    }
                    validMoves.push_back({ currentX, currentY });

                    currentX += dir.first;
                    currentY += dir.second;
                }
            }

            break;
        }
        case PieceType::QUEEN: {

            break;
        }
        case PieceType::KING: {

            break;
        }
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

SquareStatus Board::getSquareStatus(int x, int y) const {
    SquareStatus status;

    if (x < 0 || x >= 8 || y < 0 || y >= 8) {
        return status;
    }

    Piece* piece = boardArray[y][x];
    if (piece != nullptr && piece->isAlive()) {
        status.isOccupied = true;
        status.pieceType = piece->getType();
        status.pieceColor = piece->getColor();
        status.pieceId = piece->getId();
    }

    return status;
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
