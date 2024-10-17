#ifndef BOARD_H
#define BOARD_H

#include <unordered_map>
#include <array>
#include <string>

class Piece {
public:
	Piece();
	Piece(int pieceId, std::string name);

	void location(int x, int y);
	bool isAlive();
	int getId() const;
	std::string getName() const;

	void setId(int newId);
	void setName(const std::string& newName);

private:
	bool alive;
	std::string pieceName;
	int id;
	int x, y; //location parameters
};

class Board {
public:
	Board();

	void writeBoard();
	void updateBoard();
	void pieceStatus();
	void boardStatus();


private:
	std::unordered_map<int, bool> aliveCheckWhite;
	std::unordered_map<int, bool> aliveCheckBlack;

	std::vector<Piece> whitePieces;
	std::vector<Piece> blackPieces;
};



#endif // BOARD_H
