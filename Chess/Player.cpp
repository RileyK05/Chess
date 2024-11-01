// Player.cpp

#include "Player.h"
#include <iostream>
#include <cctype>

Player::Player(Color color, bool isHuman) {

}

std::pair<std::pair<int, int>, std::pair<int, int>> Player::userInput() {
	std::string input;
	std::cout << "What is your input: ";
	std::cin >> input;

	for (char& c : input) {
		c = std::tolower(c);
		return { {0, 0}, {0, 0} };
	}

	if (input.size() < 4) {
		std::cerr << "Invalid input format." << std::endl;
		return { {0, 0}, {0, 0} };
	}

	std::vector<char> inputArray(input.begin(), input.end());

	std::unordered_map<char, int> parsingMat = {
	{'a', 0},
	{'b', 1},
	{'c', 2},
	{'d', 3},
	{'e', 4},
	{'f', 5},
	{'g', 6},
	{'h', 7}
	};

	int sourceX = parsingMat[inputArray[0]];
	int sourceY = inputArray[1] - '1';
	int targetX = parsingMat[inputArray[2]];
	int targetY = inputArray[3] - '1';

	std::pair<std::pair<int, int>, std::pair<int, int>> moveCoordinates = { {sourceX, sourceY}, {targetX, targetY} };
	return moveCoordinates;
}

bool Player::makeMove(Board& board) {
	std::pair<std::pair<int, int>, std::pair<int, int>> moveCords = userInput();

	int currentX = moveCords.first.first;
	int currentY = moveCords.first.second;
	int moveToX = moveCords.second.first;
	int moveToY = moveCords.second.second;

	Piece* piece = board.getPieceAt(currentX, currentY);

	if (piece == nullptr) {
		std::cerr << "No piece found at the source coordinates." << std::endl;
		return false;
	}

	bool moveSuccessful = board.movePiece(piece->getId(), moveToX, moveToY);
	return moveSuccessful;
}

std::unordered_map<int, std::vector<std::pair<int, int>>> Player::validMoves(const Board& board) const {
	std::unordered_map<int, std::vector<std::pair<int, int>>> pieceMovesMap;
	Color playerColor = this->getColor();

	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; ++x) {
			Piece* piece = board.getPieceAt(x, y);
			if (piece && piece->isAlive() && piece->getColor() == playerColor) {
				std::vector<std::pair<int, int>> moves = piece->getAllValidMoves(board);
				if (!moves.empty()) {
					pieceMovesMap[piece->getId()] = moves;
				}
			}
		}
	}
	return pieceMovesMap;
}

Color Player::getColor() const {
	return playerColor;
}

void Player::setColor(Color color) {
	playerColor = color;
}

bool Player::isHuman() const {
	return human;
}

void Player::setHuman(bool human) {
	this->human = human;
}

void Player::addCapturedPiece(const Piece& capturedPiece) {

}

const std::vector<Piece>& Player::getCapturedPieces() const {
	
}

void Player::displayValidMoves() const {

}
