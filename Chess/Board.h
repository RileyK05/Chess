#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <array>
#include <utility>
#include <unordered_map>
#include <string>

enum class Color { WHITE, BLACK };
enum class PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

struct SquareStatus {
    bool isOccupied = false;
    PieceType pieceType;
    Color pieceColor;
    int pieceId;
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

class Board {
public:
    Board();
    void displayBoard() const;
    Piece* getPieceAt(int x, int y) const;
    void manageViews(int pieceId);
    void updatePieceStatus();
    SquareStatus getSquareStatus(int x, int y) const;
    std::pair<bool, Piece*> movePiece(int pieceId, int newX, int newY);
    std::array<std::array<int, 8>, 8> getCurrentIdPlacement() const;
    void displayUserOptions(int pieceId);
    bool isPlayerChecked();
    bool checkMate();
    std::string getSymbol(const Piece& piece) const;

    std::vector<Piece> whitePieces;
    std::vector<Piece> blackPieces;

private:
    std::array<std::array<Piece*, 8>, 8> boardArray;
    bool gameRunning;
    std::unordered_map<int, bool> aliveCheckWhite;
    std::unordered_map<int, bool> aliveCheckBlack;
};

#endif // BOARD_H
