/**
 * @file Piece.cpp
 * @brief Implementation of the Piece class methods.
 *
 * This file implements the member functions of the Piece class defined in Piece.h.
 * Functions include basic getters and setters for piece attributes, and
 * move generation logic for each type of chess piece.
 *
 * The move generation (getAllValidMoves) covers the standard movement rules for each piece type:
 * Pawn (including initial double move and diagonal captures), Knight (L-shaped moves),
 * Bishop (diagonal moves), Rook (straight moves), Queen (straight and diagonal moves),
 * and King (adjacent one-square moves). It does not handle special moves like castling or en passant.
 */
#include "Piece.h"
#include "Board.h"
#include <array>
#include <cctype>

Piece::Piece()
    : x(0), y(0), id(0), alive(true), type(PieceType::PAWN), color(Color::WHITE) {
    // Default piece initialization (used primarily for creating pieces to place on the board).
}

int Piece::getX() const {
    return x;
}

int Piece::getY() const {
    return y;
}

int Piece::getId() const {
    return id;
}

PieceType Piece::getType() const {
    return type;
}

Color Piece::getColor() const {
    return color;
}

bool Piece::isAlive() const {
    return alive;
}

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
    // Check board boundaries.
    if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) {
        return false;
    }
    // Get status of target square (occupied or not, and by which color).
    SquareStatus squareStatus = board.getSquareStatus(newX, newY);
    // A move is valid if the target square is empty or contains an opponent's piece.
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

    // Determine moves based on the type of the piece.
    switch (type) {
    case PieceType::PAWN: {
        // Pawns move forward (direction depends on color), with an optional double move from the start row,
        // and can capture diagonally forward.
        int direction = (getColor() == Color::WHITE) ? -1 : 1;    // White pawns move up (decreasing y), Black move down.
        int startRow = (getColor() == Color::WHITE) ? 6 : 1;      // Starting row for white pawns is y=6, for black y=1.

        // Single step forward.
        int forwardY = yPos + direction;
        if (isMoveValid(xPos, forwardY, board) && !board.getSquareStatus(xPos, forwardY).isOccupied) {
            validMoves.emplace_back(xPos, forwardY);

            // Double step forward from starting position (only if single step was valid and start position).
            if (yPos == startRow) {
                int doubleStepY = yPos + 2 * direction;
                if (isMoveValid(xPos, doubleStepY, board) &&
                    !board.getSquareStatus(xPos, doubleStepY).isOccupied &&
                    !board.getSquareStatus(xPos, forwardY).isOccupied) {
                    validMoves.emplace_back(xPos, doubleStepY);
                }
            }
        }

        // Diagonal captures (one step diagonally forward if an opponent piece is there).
        for (int dx : { -1, 1 }) {
            int diagX = xPos + dx;
            int diagY = yPos + direction;
            if (isMoveValid(diagX, diagY, board)) {
                SquareStatus status = board.getSquareStatus(diagX, diagY);
                if (status.isOccupied && status.pieceColor != getColor()) {
                    validMoves.emplace_back(diagX, diagY);
                }
            }
        }
        break;
    }

    case PieceType::KNIGHT: {
        // Knights move in L-shapes: 2 in one direction and 1 perpendicular.
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
                // Knight can jump: if target square is empty or has enemy piece, it's a valid move.
                if (!status.isOccupied || status.pieceColor != getColor()) {
                    validMoves.emplace_back(newX, newY);
                }
            }
        }
        break;
    }

    case PieceType::BISHOP: {
        // Bishops move diagonally any number of squares until blocked.
        std::array<std::pair<int, int>, 4> directions = {
            std::make_pair(1, 1),   // down-right
            std::make_pair(1, -1),  // up-right
            std::make_pair(-1, 1),  // down-left
            std::make_pair(-1, -1)  // up-left
        };
        for (const auto& dir : directions) {
            int currX = xPos + dir.first;
            int currY = yPos + dir.second;
            while (isMoveValid(currX, currY, board)) {
                SquareStatus status = board.getSquareStatus(currX, currY);
                if (!status.isOccupied) {
                    // Empty square: bishop can move here and continue further in this direction.
                    validMoves.emplace_back(currX, currY);
                }
                else {
                    // Occupied: if by enemy piece, it can be captured (include move, then stop); if by same color, stop.
                    if (status.pieceColor != getColor()) {
                        validMoves.emplace_back(currX, currY);
                    }
                    break;  // Stop moving further in this direction when blocked.
                }
                currX += dir.first;
                currY += dir.second;
            }
        }
        break;
    }

    case PieceType::ROOK: {
        // Rooks move straight (horizontal or vertical) any number of squares until blocked.
        std::array<std::pair<int, int>, 4> directions = {
            std::make_pair(1, 0),   // right
            std::make_pair(-1, 0),  // left
            std::make_pair(0, 1),   // down
            std::make_pair(0, -1)   // up
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
        // Queens move like both a rook and a bishop (any number of squares in any direction).
        std::array<std::pair<int, int>, 8> directions = {
            std::make_pair(1, 0),    // right
            std::make_pair(-1, 0),   // left
            std::make_pair(0, 1),    // down
            std::make_pair(0, -1),   // up
            std::make_pair(1, 1),    // down-right
            std::make_pair(1, -1),   // up-right
            std::make_pair(-1, 1),   // down-left
            std::make_pair(-1, -1)   // up-left
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
        // Kings move exactly one square in any direction.
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

