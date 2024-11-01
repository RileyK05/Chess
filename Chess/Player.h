// Player.h

#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include <vector>
#include <utility>

class Player {
public:
    Player(Color color, bool isHuman = true);

    std::pair<std::pair<int, int>, std::pair<int, int>> userInput();
    bool makeMove(Board& board);
    std::unordered_map<int, std::vector<std::pair<int, int>>> validMoves(const Board& board) const;

    Color getColor() const;
    void setColor(Color color);

    bool isHuman() const;
    void setHuman(bool human);

    void addCapturedPiece(const Piece& capturedPiece);
    const std::vector<Piece>& getCapturedPieces() const;

    void displayValidMoves() const;

private:
    Color playerColor;
    bool human;
    std::vector<Piece> capturedPieces;

};

#endif // PLAYER_H
