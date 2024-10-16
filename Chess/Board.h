#ifndef BOARD_H
#define BOARD_H

#include <unordered_map>
#include <array>
#include <string>

class Piece {
public:
	void location(int x, int y);
	bool isAlive();
	int id;

private:
	std::unordered_map<int, std::string> pieceType;
	std::array<std::array<int, 8>, 8> position;
};

class Board {
public:
	void writeBoard();
	void updateBoard();
	void pieceStatus();
	void boardStatus();

private:
	std::unordered_map<bool, int> aliveCheck;
};



#endif // BOARD_H
