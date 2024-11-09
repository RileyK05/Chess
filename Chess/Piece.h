// Piece.h

#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <utility>

// Define enums here
enum class Color { WHITE, BLACK };
enum class PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

// Forward declaration to avoid circular dependency
class Board;

class Piece {
public:
    Piece();
    int getX() const;
    int getY() const;
    int getId() const;
    PieceType getType() const;
    Color getColor() const;
    bool isAlive() const;

    void setLocation(int newX, int newY);
    void setIsAlive(bool newAlive);
    void setId(int newId);
    void setType(PieceType newType);
    void setColor(Color newColor);

    std::vector<std::pair<int, int>> getAllValidMoves(const Board& board) const;
    bool isMoveValid(int newX, int newY, const Board& board) const;

private:
    int x;
    int y;
    int id;
    bool alive;
    PieceType type;
    Color color;
};

#endif // PIECE_H
