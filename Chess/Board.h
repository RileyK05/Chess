#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <array>
#include <utility>
#include <unordered_map>
#include <string>
#include <stack>
#include "Piece.h"

struct SquareStatus {
    bool           isOccupied = false;
    PieceType      pieceType = PieceType::PAWN;
    Color          pieceColor = Color::WHITE;
    int            pieceId = 0;
};

struct Move {
    int                      pieceId;
    std::pair<int, int>       from;
    std::pair<int, int>       to;
    Piece* capturedPiece = nullptr;
};

class Board {
public:
    Board();
    Board(const Board&);
    Board& operator=(const Board&);
    ~Board() = default;

    // display & query
    void displayBoard() const;
    Piece* getPieceAt(int x, int y) const;
    SquareStatus getSquareStatus(int x, int y) const;

    // move execution & validation
    std::pair<bool, Piece*> movePiece(int pieceId, int newX, int newY);
    bool isPlayerInCheck(Color playerColor) const;
    bool isCheckmate(Color playerColor);
    Piece* makeMoveForCheck(int pieceId, int newX, int newY);
    void undoMoveForCheck();

    // control
    void setGameRunning(bool running);
    bool isGameRunning() const;

    // utilities
    std::string getSymbol(const Piece& piece) const;
    Piece* getPieceById(int pieceId);
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    std::stack<Move> getMoveHistory() const;

    // convenience wrappers (must be NON‑CONST to match Board.cpp)
    bool isPlayerChecked();
    bool checkMate();

    // board state
    std::vector<Piece>                      whitePieces;
    std::vector<Piece>                      blackPieces;
    std::array<std::array<Piece*, 8>, 8>      boardArray;
    Color                                   currentPlayerColor;

private:
    bool gameRunning{ true };
    std::stack<Move> moveHistory;
};

#endif // BOARD_H
