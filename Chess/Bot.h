// Bot.h

#ifndef BOT_H
#define BOT_H

#include <vector>
#include <utility>
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
	
	std::array<std::array<int, 8>, 8> boardValue(Board& board);
	std::pair<std::pair<int, int>, std::pair<int, int>> bestMove(
		Piece* piece,
		Board& board,
		std::unordered_map<int, std::vector<std::pair<int, int>>> validMoves);

	std::vector<EnemyPiece> evaluateEnemyPieces(const Board& board);
private:
	int evaluateMove(const Board& board, const std::pair<int, int>& move, Piece* piece);

	std::pair<int, int> prioritizeCaptureOrAvoidance(
		Piece* piece,
		const std::vector<std::pair<int, int>>& validMoves,
		const Board& board,
		const std::vector<EnemyPiece>& enemyPieces);
};

#endif // BOT_H
