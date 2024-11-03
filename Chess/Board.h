// Board.h

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

struct SquareStatus {
    bool isOccupied;
    PieceType pieceType;
    Color pieceColor;
    int pieceId;

    SquareStatus() : isOccupied(false), pieceType(PieceType::PAWN), pieceColor(Color::WHITE), pieceId(-1) {}
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
    int x, y;
    int id;
    bool alive;
    PieceType type;
    Color color;
};

class Board {
public:
    Board();

    Piece* getPieceAt(int x, int y) const;

    void displayBoard() const;
    void manageViews(int pieceId = -1);
    void updatePieceStatus();
    SquareStatus getSquareStatus(int x, int y) const;
    std::pair<bool, Piece*> movePiece(int pieceId, int newX, int newY);
    std::array<std::array<int, 8>, 8> getCurrentIdPlacement() const;
    void displayUserOptions(int pieceId);

    const std::vector<Piece>& getWhitePieces() const { return whitePieces; }
    const std::vector<Piece>& getBlackPieces() const { return blackPieces; }

    bool isPlayerChecked();
    bool checkMate();

private:
    std::string getSymbol(const Piece& piece) const;

    std::vector<Piece> whitePieces;
    std::vector<Piece> blackPieces;
    std::array<std::array<Piece*, 8>, 8> boardArray;

    std::unordered_map<int, bool> aliveCheckWhite;
    std::unordered_map<int, bool> aliveCheckBlack;

    bool gameRunning;
};

#endif // BOARD_H
