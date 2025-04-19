#ifndef BOT_H
#define BOT_H

#include <vector>
#include <utility>
#include <unordered_map>
#include <climits>
#include "Board.h"
#include "Player.h"

/**
 * @class Bot
 * @brief Simple AI player using minimax-like evaluation.
 */
class Bot : public Player {
public:
    Bot(Color color)
        : Player(color, false) {
    }      ///< Initialize as AI for given color.

    bool makeMove(Board& board) override;  ///< Choose and execute best move.

private:
    int evaluateMove(Board& board, int depth, Color currentPlayer);
    ///< Recursively score moves.
    int evaluateBoard(const Board& board); ///< Heuristic board scoring.
    std::unordered_map<int, std::vector<std::pair<int, int>>>
        validMoves(const Board& board, Color color) const;
    ///< Moves for specified color.
};

#endif // BOT_H
