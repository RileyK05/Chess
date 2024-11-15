// Board.h
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
    bool isOccupied = false;
    PieceType pieceType = PieceType::PAWN;
    Color pieceColor = Color::WHITE;
    int pieceId = 0;
};

struct Move {
    int pieceId;
    std::pair<int, int> from;
    std::pair<int, int> to;
    Piece* capturedPiece = nullptr;
};

class Board {
public:
    Board();
    Board(const Board& other);
    Board& operator=(const Board& other);
    void displayBoard() const;
    Piece* getPieceAt(int x, int y) const;
    SquareStatus getSquareStatus(int x, int y) const;
    std::pair<bool, Piece*> movePiece(int pieceId, int newX, int newY);
    bool isPlayerInCheck(Color playerColor) const;
    bool isCheckmate(Color playerColor);
    Piece* makeMoveForCheck(int pieceId, int newX, int newY);
    void undoMoveForCheck();
    void setGameRunning(bool running);
    bool isGameRunning() const;
    bool isPlayerChecked();
    bool checkMate();
    std::string getSymbol(const Piece& piece) const;
    Piece* getPieceById(int pieceId);
    std::vector<Piece> whitePieces;
    std::vector<Piece> blackPieces;
    std::array<std::array<Piece*, 8>, 8> boardArray{};
    Color currentPlayerColor;
private:
    bool gameRunning = false;
    std::stack<Move> moveHistory;
};

#endif // BOARD_H
