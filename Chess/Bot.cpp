#include "Bot.h"

std::array<std::array<int, 8>, 8> Bot::boardValue(Board& board) {
	return std::array<std::array<int, 8>, 8>();
}

std::pair<std::pair<int, int>, std::pair<int, int>> Bot::bestMove(
	Piece* piece, 
	Board& board, 
	std::unordered_map<int, std::vector<std::pair<int, int>>> validMoves) {

	return std::pair<std::pair<int, int>, std::pair<int, int>>();
}

std::vector<EnemyPiece> Bot::evaluateEnemyPieces(const Board& board) {

	return std::vector<EnemyPiece>();
}

int Bot::evaluateMove(const Board& board, const std::pair<int, int>& move, Piece* piece) {

	return 0;
}

std::pair<int, int> Bot::prioritizeCaptureOrAvoidance(
	Piece* piece, 
	const std::vector<std::pair<int, int>>& validMoves, 
	const Board& board, const std::vector<EnemyPiece>& enemyPieces) {


	return std::pair<int, int>();
}
