#include "Board.h"
#include <unordered_map>
#include <vector>



Piece::Piece() {
    
}

Piece::Piece(int pieceId, std::string name) {

}

void Piece::location(int x, int y) {

}

bool Piece::isAlive() {
	return alive;
}

int Piece::getId() const {
	return id;
}

std::string Piece::getName() const {
	return pieceName;
}

void Piece::setId(int newId) {
    id = newId;
}

void Piece::setName(const std::string& newName) {
    pieceName = newName;
}

Board::Board() {
    int baseId = 1;

    for (int i = 0; i < 8; i++) {
        Piece whitePiece;
        whitePiece.setId(baseId++);
        whitePiece.location()
    }

    int x, y = 1;
    for (Piece& piece : whitePieces) {
        piece.location(x, y);
        if (y == 2) {
            piece.
        }
    }
}

void Board::writeBoard() {

}

void Board::updateBoard() {

}

void Board::pieceStatus() {
    for (const Piece& piece : whitePieces) {
        int id = piece.getId();
        aliveCheckWhite[id] = piece.isAlive();
    }

    for (const Piece& piece : blackPieces) {
        int id = piece.getId();
        aliveCheckBlack[id] = piece.isAlive();
    }
}


void Board::boardStatus() {

}
