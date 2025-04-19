#include "Bot.h"
#include <algorithm>
#include <iostream>

/*
   Simple minimax?style AI:
   - validMoves(): generate all safe moves (won’t leave own king in check)
   - makeMove(): test each move to depth=2, pick highest score
*/

// Execute the best move found
bool Bot::makeMove(Board& board)
{
    auto allMoves = validMoves(board, getColor());
    if (allMoves.empty()) return false;

    int  bestPiece = -1;
    std::pair<int, int> bestDest;
    int  bestScore = INT_MIN;
    Color me = getColor();

    // Traditional iteration (no structured bindings)
    for (auto it = allMoves.begin(); it != allMoves.end(); ++it) {
        int id = it->first;
        const auto& moves = it->second;
        for (size_t i = 0; i < moves.size(); ++i) {
            int nx = moves[i].first, ny = moves[i].second;
            Board tmp = board;
            if (!tmp.movePiece(id, nx, ny).first) continue;
            Color next = (me == Color::WHITE ? Color::BLACK : Color::WHITE);
            int score = evaluateMove(tmp, 2, next);
            if (score > bestScore) {
                bestScore = score;
                bestPiece = id;
                bestDest = moves[i];
            }
        }
    }

    if (bestPiece < 0) return false;
    auto res = board.movePiece(bestPiece, bestDest.first, bestDest.second);
    if (!res.first) return false;

    // Report the move
    char f1 = 'A' + board.getPieceById(bestPiece)->getX();
    int  r1 = 8 - board.getPieceById(bestPiece)->getY();
    char f2 = 'A' + bestDest.first;
    int  r2 = 8 - bestDest.second;
    std::cout << "Bot moves " << f1 << r1 << " to " << f2 << r2 << std::endl;

    if (res.second)
        addCapturedPiece(res.second);

    return true;
}

// Recursive minimax to given depth
int Bot::evaluateMove(Board& b, int depth, Color side)
{
    if (depth == 0 || !b.isGameRunning())
        return evaluateBoard(b);

    auto allMoves = validMoves(b, side);
    if (allMoves.empty()) {
        // no moves ? stalemate or checkmate
        if (b.isPlayerInCheck(side))
            // side is mated
            return (side == getColor() ? INT_MIN : INT_MAX);
        return 0;
    }

    int best = (side == getColor() ? INT_MIN : INT_MAX);
    for (auto it = allMoves.begin(); it != allMoves.end(); ++it) {
        int id = it->first;
        const auto& moves = it->second;
        for (size_t i = 0; i < moves.size(); ++i) {
            int nx = moves[i].first, ny = moves[i].second;
            Board tmp = b;
            if (!tmp.movePiece(id, nx, ny).first) continue;
            Color next = (side == Color::WHITE ? Color::BLACK : Color::WHITE);
            int v = evaluateMove(tmp, depth - 1, next);
            if (side == getColor()) {
                if (v > best) best = v;
            }
            else {
                if (v < best) best = v;
            }
        }
    }
    return best;
}

// Simple material count heuristic
int Bot::evaluateBoard(const Board& b)
{
    static const std::unordered_map<PieceType, int> values = {
        {PieceType::PAWN,1},
        {PieceType::KNIGHT,3},
        {PieceType::BISHOP,3},
        {PieceType::ROOK,5},
        {PieceType::QUEEN,9},
        {PieceType::KING,1000}
    };

    int score = 0;
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            Piece* p = b.getPieceAt(x, y);
            if (!p) continue;
            int v = values.at(p->getType());
            score += (p->getColor() == getColor() ? +v : -v);
        }
    }
    return score;
}

// Generate all legal moves for a given side (no leaving self in check)
std::unordered_map<int, std::vector<std::pair<int, int>>>
Bot::validMoves(const Board& b, Color side) const
{
    std::unordered_map<int, std::vector<std::pair<int, int>>> out;

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            Piece* p = b.getPieceAt(x, y);
            if (!p || p->getColor() != side) continue;

            auto candidates = p->getAllValidMoves(b);
            std::vector<std::pair<int, int>> legals;
            for (size_t i = 0; i < candidates.size(); ++i) {
                int nx = candidates[i].first, ny = candidates[i].second;
                Board tmp = b;
                if (!tmp.movePiece(p->getId(), nx, ny).first) continue;
                if (!tmp.isPlayerInCheck(side))
                    legals.push_back(candidates[i]);
            }
            if (!legals.empty())
                out[p->getId()] = std::move(legals);
        }
    }
    return out;
}
