#ifndef BOARD_H
#define BOARD_H

#include <unordered_map>
#include <array>
#include <string>

class Piece {
public:
	Piece();
	
	int getX() const;
	int getY() const;
	int getId() const;
	std::string getName() const;
	bool getIsAlive() const;

	void setLocation(int newX, int newY);
	void setIsAlive(bool newAlive);
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

	int helperInverse(int num);

private:
	std::unordered_map<int, bool> aliveCheckWhite;
	std::unordered_map<int, bool> aliveCheckBlack;

	std::vector<Piece> whitePieces;
	std::vector<Piece> blackPieces;
};



#endif // BOARD_H
