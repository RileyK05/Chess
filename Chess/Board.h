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
    bool moveValidCheck(int newX, int newY, Board& board) const;

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
    std::vector<std::pair<int, int>> squareStatus(int x, int y, bool isWhite);
    int helperInverse(int num);

    bool movePiece(int pieceId, int newX, int newY, bool isWhite);
    std::array<std::array<int, 8>, 8> currentIdPlacement(std::vector<std::pair<int, int>> squareStatus, int x, int y, bool istWhite);

    const std::vector<Piece>& getWhitePieces() const { return whitePieces; }
    const std::vector<Piece>& getBlackPieces() const { return blackPieces; }

private:
    std::unordered_map<int, bool> aliveCheckWhite;
    std::unordered_map<int, bool> aliveCheckBlack;

    std::vector<Piece> whitePieces;
    std::vector<Piece> blackPieces;
    std::string getSymbol(const Piece& piece) const;

    std::array<std::array<int, 8>, 8> boardMap;


};

#endif // BOARD_H
