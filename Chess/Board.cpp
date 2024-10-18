#include "Board.h"
#include <unordered_map>
#include <vector>



Piece::Piece() {
    
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


void Piece::setLocation(int x, int y) {

}
void Piece::setId(int newId) {
    id = newId;
}

void Piece::setName(const std::string& newName) {
    pieceName = newName;
}

Board::Board() {

    for (int i = 0; i < 8; i++) {
        Piece whitePawn;
        whitePawn.setId(i+1);
        whitePawn.setLocation(i, 1);
        whitePawn.setName("White Pawn");
        whitePieces.push_back(whitePawn);
    }

    Piece whiteKnight1;
    whiteKnight1.setId(9);
    whiteKnight1.setLocation(0, 0);
    whiteKnight1.setName("White Knight");
    whitePieces.push_back(whiteKnight1);
    
    Piece whiteKnight2;
    whiteKnight2.setId(10);
    whiteKnight2.setLocation(0, 7);
    whiteKnight2.setName("White Knight");
    whitePieces.push_back(whiteKnight2);

    Piece whiteRook1;
    whiteRook1.setId(11);
    whiteRook1.setLocation(0, 1);
    whiteRook1.setName("White Rook");
    whitePieces.push_back(whiteRook1);
    
    Piece whiteRook2;
    whiteRook2.setId(12);
    whiteRook2.setLocation(0, 6);
    whiteRook2.setName("White Rook");
    whitePieces.push_back(whiteRook2);

    Piece whiteBishop1;
    whiteBishop1.setId(13);
    whiteBishop1.setLocation(0, 2);
    whiteBishop1.setName("White Bishop");
    whitePieces.push_back(whiteBishop1);

    Piece whiteBishop2;
    whiteBishop2.setId(14);
    whiteBishop2.setLocation(0, 5);
    whiteBishop2.setName("White Bishop");
    whitePieces.push_back(whiteBishop2);

    Piece whiteQueen;
    whiteQueen.setId(4);
    whiteQueen.setLocation(0, 4);
    whiteQueen.setName("White Queen");
    whitePieces.push_back(whiteQueen);



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
