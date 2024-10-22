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

// Define the SquareStatus struct here
struct SquareStatus {
    bool isOccupied;
    PieceType pieceType;
    Color pieceColor;
    int pieceId;

    SquareStatus() : isOccupied(false), pieceType(PieceType::PAWN), pieceColor(Color::WHITE), pieceId(-1) {}  // Default values
};

class Board;

class Piece {
public:
    Piece();

    // Getters
    int getX() const;
    int getY() const;
    int getId() const;
    PieceType getType() const;
    Color getColor() const;
    bool isAlive() const;

    // Setters
    void setLocation(int newX, int newY);
    void setIsAlive(bool newAlive);
    void setId(int newId);
    void setType(PieceType newType);
    void setColor(Color newColor);

    // Methods
    std::vector<std::pair<int, int>> getAllValidMoves(const Board& board) const;
    bool isMoveValid(int newX, int newY, const Board& board) const;

private:
    int x, y;   // Location parameters
    int id;
    bool alive;
    PieceType type;
    Color color;
};

class Board {
public:
    Board();

    // Getters
    Piece* getPieceAt(int x, int y) const;

    // Methods
    void displayBoard() const;
    void updateBoard();
    void updatePieceStatus();
    SquareStatus getSquareStatus(int x, int y) const;
    bool movePiece(int pieceId, int newX, int newY);
    std::array<std::array<int, 8>, 8> getCurrentIdPlacement() const;

    // Accessors
    const std::vector<Piece>& getWhitePieces() const { return whitePieces; }
    const std::vector<Piece>& getBlackPieces() const { return blackPieces; }

private:
    // Helper Methods
    std::string getSymbol(const Piece& piece) const;

    // Members
    std::vector<Piece> whitePieces;
    std::vector<Piece> blackPieces;
    std::array<std::array<Piece*, 8>, 8> boardArray;

    // Piece status maps
    std::unordered_map<int, bool> aliveCheckWhite;
    std::unordered_map<int, bool> aliveCheckBlack;
};

#endif // BOARD_H
