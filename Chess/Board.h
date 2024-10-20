#ifndef BOARD_H
#define BOARD_H

#include <unordered_map>
#include <array>
#include <string>
#include <vector> 

enum class Color {
    WHITE,
    BLACK
};

enum class PieceType {
    PAWN,
    KNIGHT,
    ROOK,
    BISHOP,
    QUEEN,
    KING
};

class Board;

class Piece {
public:
    Piece();

    int getX() const;
    int getY() const;
    int getId() const;
    PieceType getType() const;
    Color getColor() const;
    bool getIsAlive() const;

    void setLocation(int newX, int newY);
    void setIsAlive(bool newAlive);
    void setId(int newId);
    void setType(PieceType newType);
    void setColor(Color newColor);

    std::vector<std::pair<int, int>> getAllValidMoves(const Board& board) const;
    bool moveValidCheck(int newX, int newY) const; 

private:
    bool alive;
    PieceType type;
    Color color; 
    int id;
    int x, y; // Location parameters
};

class Board {
public:
    Board();

    void writeBoard();
    void updateBoard();
    void pieceStatus();
    void boardStatus();

    int helperInverse(int num);

    bool movePiece(int pieceId, int newX, int newY, bool isWhite);

private:
    std::unordered_map<int, bool> aliveCheckWhite;
    std::unordered_map<int, bool> aliveCheckBlack;

    std::vector<Piece> whitePieces;
    std::vector<Piece> blackPieces;

    std::string getSymbol(const Piece& piece, bool isWhite) const;
};

#endif // BOARD_H
