// Piece.cpp

#include "Piece.h"
#include "Board.h"
#include <array>
#include <cctype>

Piece::Piece()
    : x(0), y(0), id(0), alive(true), type(PieceType::PAWN), color(Color::WHITE) {}

int Piece::getX() const { return x; }
int Piece::getY() const { return y; }
int Piece::getId() const { return id; }
PieceType Piece::getType() const { return type; }
Color Piece::getColor() const { return color; }
bool Piece::isAlive() const { return alive; }

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

bool Piece::isMoveValid(int newX, int newY, const Board& board) const {
    if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) {
        return false;
    }
    SquareStatus squareStatus = board.getSquareStatus(newX, newY);
    if (!squareStatus.isOccupied) {
        return true;
    }
    else if (squareStatus.pieceColor != getColor()) {
        return true;
    }
    return false;
}

std::vector<std::pair<int, int>> Piece::getAllValidMoves(const Board& board) const {
    std::vector<std::pair<int, int>> validMoves;
    int xPos = getX();
    int yPos = getY();

    switch (type) {
    case PieceType::PAWN: {
        int direction = (getColor() == Color::WHITE) ? -1 : 1;
        int startRow = (getColor() == Color::WHITE) ? 6 : 1;

        int newY = yPos + direction;
        if (isMoveValid(xPos, newY, board) && !board.getSquareStatus(xPos, newY).isOccupied) {
            validMoves.emplace_back(xPos, newY);

            if (yPos == startRow) {
                int doubleStepY = yPos + 2 * direction;
                if (isMoveValid(xPos, doubleStepY, board) &&
                    !board.getSquareStatus(xPos, doubleStepY).isOccupied &&
                    !board.getSquareStatus(xPos, newY).isOccupied) {
                    validMoves.emplace_back(xPos, doubleStepY);
                }
            }
        }

        for (int dx : { -1, 1 }) {
            int newX = xPos + dx;
            newY = yPos + direction;
            if (isMoveValid(newX, newY, board)) {
                SquareStatus status = board.getSquareStatus(newX, newY);
                if (status.isOccupied && status.pieceColor != getColor()) {
                    validMoves.emplace_back(newX, newY);
                }
            }
        }
        break;
    }
    case PieceType::KNIGHT: {
        std::array<std::pair<int, int>, 8> moves = {
            std::make_pair(xPos + 1, yPos + 2),
            std::make_pair(xPos + 1, yPos - 2),
            std::make_pair(xPos - 1, yPos + 2),
            std::make_pair(xPos - 1, yPos - 2),
            std::make_pair(xPos + 2, yPos + 1),
            std::make_pair(xPos + 2, yPos - 1),
            std::make_pair(xPos - 2, yPos + 1),
            std::make_pair(xPos - 2, yPos - 1)
        };
        for (const auto& move : moves) {
            int newX = move.first;
            int newY = move.second;
            if (isMoveValid(newX, newY, board)) {
                SquareStatus status = board.getSquareStatus(newX, newY);
                if (!status.isOccupied || status.pieceColor != getColor()) {
                    validMoves.emplace_back(newX, newY);
                }
            }
        }
        break;
    }
    case PieceType::BISHOP: {
        std::array<std::pair<int, int>, 4> directions = {
            std::make_pair(1, 1),
            std::make_pair(1, -1),
            std::make_pair(-1, 1),
            std::make_pair(-1, -1)
        };
        for (const auto& dir : directions) {
            int currX = xPos + dir.first;
            int currY = yPos + dir.second;
            while (isMoveValid(currX, currY, board)) {
                SquareStatus status = board.getSquareStatus(currX, currY);
                if (!status.isOccupied) {
                    validMoves.emplace_back(currX, currY);
                }
                else {
                    if (status.pieceColor != getColor()) {
                        validMoves.emplace_back(currX, currY);
                    }
                    break;
                }
                currX += dir.first;
                currY += dir.second;
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
        for (const auto& dir : directions) {
            int currX = xPos + dir.first;
            int currY = yPos + dir.second;
            while (isMoveValid(currX, currY, board)) {
                SquareStatus status = board.getSquareStatus(currX, currY);
                if (!status.isOccupied) {
                    validMoves.emplace_back(currX, currY);
                }
                else {
                    if (status.pieceColor != getColor()) {
                        validMoves.emplace_back(currX, currY);
                    }
                    break;
                }
                currX += dir.first;
                currY += dir.second;
            }
        }
        break;
    }
    case PieceType::QUEEN: {
        std::array<std::pair<int, int>, 8> directions = {
            std::make_pair(1, 0),
            std::make_pair(-1, 0),
            std::make_pair(0, 1),
            std::make_pair(0, -1),
            std::make_pair(1, 1),
            std::make_pair(1, -1),
            std::make_pair(-1, 1),
            std::make_pair(-1, -1)
        };
        for (const auto& dir : directions) {
            int currX = xPos + dir.first;
            int currY = yPos + dir.second;
            while (isMoveValid(currX, currY, board)) {
                SquareStatus status = board.getSquareStatus(currX, currY);
                if (!status.isOccupied) {
                    validMoves.emplace_back(currX, currY);
                }
                else {
                    if (status.pieceColor != getColor()) {
                        validMoves.emplace_back(currX, currY);
                    }
                    break;
                }
                currX += dir.first;
                currY += dir.second;
            }
        }
        break;
    }
    case PieceType::KING: {
        std::array<std::pair<int, int>, 8> moves = {
            std::make_pair(xPos + 1, yPos),
            std::make_pair(xPos - 1, yPos),
            std::make_pair(xPos, yPos + 1),
            std::make_pair(xPos, yPos - 1),
            std::make_pair(xPos + 1, yPos + 1),
            std::make_pair(xPos + 1, yPos - 1),
            std::make_pair(xPos - 1, yPos + 1),
            std::make_pair(xPos - 1, yPos - 1)
        };
        for (const auto& move : moves) {
            int newX = move.first;
            int newY = move.second;
            if (isMoveValid(newX, newY, board)) {
                SquareStatus status = board.getSquareStatus(newX, newY);
                if (!status.isOccupied || status.pieceColor != getColor()) {
                    validMoves.emplace_back(newX, newY);
                }
            }
        }
        break;
    }
    default:
        break;
    }
    return validMoves;
}
