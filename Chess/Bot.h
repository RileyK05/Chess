// bot.h

#ifndef BOT_H
#define BOT_H

#include <vector>
#include <utility>
#include <unordered_map>
#include <climits>
#include "Board.h"
#include "Player.h"

struct EnemyPiece {
    Piece& piece;
    int value; // 1-99 to determine how important it is. 1 is low value. 99 is high value
    int threat; // same concept as above. A piece with high threat will be given a high value
    bool isKing; // just to be sure that, you know, it isn't a king
};

class Bot : public Player {
public:
    Bot(Color color) : Player(color, false) {}
    bool makeMove(Board& board);
private:
    int evaluateMove(Board& board, int depth, Color currentPlayer);
    int evaluateBoard(const Board& board);
    std::unordered_map<int, std::vector<std::pair<int, int>>> validMoves(const Board& board, Color color) const;
};

#endif // BOT_H
