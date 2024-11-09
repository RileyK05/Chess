// bot.cpp

#include "Bot.h"
#include <iostream>
#include <algorithm>

bool Bot::makeMove(Board& board) {
    std::unordered_map<int, std::vector<std::pair<int, int>>> allValidMoves = validMoves(board, this->getColor());

    if (allValidMoves.empty()) {
        return false;
    }

    int bestPieceId = -1;
    std::pair<int, int> bestMove;
    int bestValue = INT_MIN;

    for (const auto& entry : allValidMoves) {
        int pieceId = entry.first;
        const std::vector<std::pair<int, int>>& moves = entry.second;

        for (const auto& move : moves) {
            Board testBoard = board;
            auto moveResult = testBoard.movePiece(pieceId, move.first, move.second);

            if (!moveResult.first) {
                continue;
            }

            Color nextPlayer = (this->getColor() == Color::WHITE) ? Color::BLACK : Color::WHITE;

            int value = evaluateMove(testBoard, 2, nextPlayer);

            if (value > bestValue) {
                bestValue = value;
                bestPieceId = pieceId;
                bestMove = move;
            }
        }
    }

    if (bestPieceId != -1) {
        auto moveResult = board.movePiece(bestPieceId, bestMove.first, bestMove.second);
        if (moveResult.first) {
            char colFrom = 'A' + board.getPieceById(bestPieceId)->getX();
            int rowFrom = 8 - board.getPieceById(bestPieceId)->getY();
            char colTo = 'A' + bestMove.first;
            int rowTo = 8 - bestMove.second;
            std::cout << "Bot moves from " << colFrom << rowFrom << " to " << colTo << rowTo << "\n";
            return true;
        }
    }

    return false;
}

int Bot::evaluateMove(Board& board, int depth, Color currentPlayer) {
    if (depth == 0 || !board.isGameRunning()) {
        return evaluateBoard(board);
    }

    std::unordered_map<int, std::vector<std::pair<int, int>>> allValidMoves = validMoves(board, currentPlayer);

    if (allValidMoves.empty()) {
        if (board.isPlayerInCheck(currentPlayer)) {
            if (currentPlayer == this->getColor()) {
                return INT_MIN;
            }
            else {
                return INT_MAX;
            }
        }
        else {
            return 0;
        }
    }

    if (currentPlayer == this->getColor()) {
        int maxEval = INT_MIN;

        for (const auto& entry : allValidMoves) {
            int pieceId = entry.first;
            const std::vector<std::pair<int, int>>& moves = entry.second;

            for (const auto& move : moves) {
                Board newBoard = board;
                auto moveResult = newBoard.movePiece(pieceId, move.first, move.second);

                if (!moveResult.first) {
                    continue;
                }

                Color nextPlayer = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;

                int eval = evaluateMove(newBoard, depth - 1, nextPlayer);

                maxEval = std::max(maxEval, eval);
            }
        }
        return maxEval;
    }
    else {
        int minEval = INT_MAX;

        for (const auto& entry : allValidMoves) {
            int pieceId = entry.first;
            const std::vector<std::pair<int, int>>& moves = entry.second;

            for (const auto& move : moves) {
                Board newBoard = board;
                auto moveResult = newBoard.movePiece(pieceId, move.first, move.second);

                if (!moveResult.first) {
                    continue;
                }

                Color nextPlayer = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;

                int eval = evaluateMove(newBoard, depth - 1, nextPlayer);

                minEval = std::min(minEval, eval);
            }
        }
        return minEval;
    }
}

int Bot::evaluateBoard(const Board& board) {
    int score = 0;

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            Piece* piece = board.getPieceAt(x, y);
            if (piece != nullptr) {
                int pieceVal = 0;
                switch (piece->getType()) {
                case PieceType::PAWN: pieceVal = 1; break;
                case PieceType::KNIGHT: pieceVal = 3; break;
                case PieceType::BISHOP: pieceVal = 3; break;
                case PieceType::ROOK: pieceVal = 5; break;
                case PieceType::QUEEN: pieceVal = 9; break;
                case PieceType::KING: pieceVal = 1000; break;
                }

                if (piece->getColor() == this->getColor()) {
                    score += pieceVal;
                }
                else {
                    score -= pieceVal;
                }
            }
        }
    }
    return score;
}

std::unordered_map<int, std::vector<std::pair<int, int>>> Bot::validMoves(const Board& board, Color color) const {
    std::unordered_map<int, std::vector<std::pair<int, int>>> pieceMovesMap;

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            Piece* piece = board.getPieceAt(x, y);
            if (piece && piece->isAlive() && piece->getColor() == color) {
                std::vector<std::pair<int, int>> moves = piece->getAllValidMoves(board);
                std::vector<std::pair<int, int>> legalMoves;
                for (const auto& move : moves) {
                    Board testBoard = board;
                    auto moveResult = testBoard.movePiece(piece->getId(), move.first, move.second);
                    if (!moveResult.first) {
                        continue;
                    }
                    if (!testBoard.isPlayerInCheck(color)) {
                        legalMoves.push_back(move);
                    }
                }
                if (!legalMoves.empty()) {
                    pieceMovesMap[piece->getId()] = legalMoves;
                }
            }
        }
    }
    return pieceMovesMap;
}
