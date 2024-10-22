#include <unordered_map>
#include <vector>
#include <iostream>
#include <array>
#include "Board.h"
// #include "Player.h" // include these later
// #include "Bot.h" 

Piece::Piece() : alive(true), id(0), x(0), y(0), type(PieceType::PAWN), color(Color::WHITE) {
}

int Piece::getX() const {
    return x;
}

int Piece::getY() const {
    return y;
}

bool Piece::getIsAlive() const {
    return alive;
}

int Piece::getId() const {
    return id;
}

PieceType Piece::getType() const {
    return type;
}

Color Piece::getColor() const {
    return color;
}

void Piece::setLocation(int newX, int newY) {
    x = newX;
    y = newY;
}

void Piece::setIsAlive(bool newAlive) {
    alive = newAlive;
}

void Piece::setId(int newId) {
    id = newId;
}

void Piece::setType(PieceType newType) {
    type = newType;
}

void Piece::setColor(Color newColor) {
    color = newColor;
}

std::vector<std::pair<int, int>> Piece::getAllValidMoves(const Board& board) const {
    return {};
}

bool Piece::moveValidCheck(int newX, int newY, Board& board) const {
    // Move validation logic will be implemented later
    return false;
}

Board::Board() {

    for (auto& row : boardMap) {
        row.fill(-1);
    }

    for (int i = 0; i < 8; i++) {
        Piece whitePawn;
        whitePawn.setId(i + 1);
        whitePawn.setLocation(i, 1);
        whitePawn.setType(PieceType::PAWN);
        whitePawn.setColor(Color::WHITE);
        whitePieces.push_back(whitePawn);
    }

    Piece whiteRook1;
    whiteRook1.setId(9);
    whiteRook1.setLocation(0, 0);
    whiteRook1.setType(PieceType::ROOK);
    whiteRook1.setColor(Color::WHITE);
    whitePieces.push_back(whiteRook1);

    Piece whiteKnight1;
    whiteKnight1.setId(10);
    whiteKnight1.setLocation(1, 0);
    whiteKnight1.setType(PieceType::KNIGHT);
    whiteKnight1.setColor(Color::WHITE);
    whitePieces.push_back(whiteKnight1);

    Piece whiteBishop1;
    whiteBishop1.setId(11);
    whiteBishop1.setLocation(2, 0);
    whiteBishop1.setType(PieceType::BISHOP);
    whiteBishop1.setColor(Color::WHITE);
    whitePieces.push_back(whiteBishop1);

    Piece whiteQueen;
    whiteQueen.setId(12);
    whiteQueen.setLocation(3, 0);
    whiteQueen.setType(PieceType::QUEEN);
    whiteQueen.setColor(Color::WHITE);
    whitePieces.push_back(whiteQueen);

    Piece whiteKing;
    whiteKing.setId(13);
    whiteKing.setLocation(4, 0);
    whiteKing.setType(PieceType::KING);
    whiteKing.setColor(Color::WHITE);
    whitePieces.push_back(whiteKing);

    Piece whiteBishop2;
    whiteBishop2.setId(14);
    whiteBishop2.setLocation(5, 0);
    whiteBishop2.setType(PieceType::BISHOP);
    whiteBishop2.setColor(Color::WHITE);
    whitePieces.push_back(whiteBishop2);

    Piece whiteKnight2;
    whiteKnight2.setId(15);
    whiteKnight2.setLocation(6, 0);
    whiteKnight2.setType(PieceType::KNIGHT);
    whiteKnight2.setColor(Color::WHITE);
    whitePieces.push_back(whiteKnight2);

    Piece whiteRook2;
    whiteRook2.setId(16);
    whiteRook2.setLocation(7, 0);
    whiteRook2.setType(PieceType::ROOK);
    whiteRook2.setColor(Color::WHITE);
    whitePieces.push_back(whiteRook2);

    for (int i = 0; i < 8; i++) {
        Piece blackPawn;
        blackPawn.setId(i + 17);
        blackPawn.setLocation(i, 6);
        blackPawn.setType(PieceType::PAWN);
        blackPawn.setColor(Color::BLACK);
        blackPieces.push_back(blackPawn);
    }

    Piece blackRook1;
    blackRook1.setId(25);
    blackRook1.setLocation(0, 7);
    blackRook1.setType(PieceType::ROOK);
    blackRook1.setColor(Color::BLACK);
    blackPieces.push_back(blackRook1);

    Piece blackKnight1;
    blackKnight1.setId(26);
    blackKnight1.setLocation(1, 7);
    blackKnight1.setType(PieceType::KNIGHT);
    blackKnight1.setColor(Color::BLACK);
    blackPieces.push_back(blackKnight1);

    Piece blackBishop1;
    blackBishop1.setId(27);
    blackBishop1.setLocation(2, 7);
    blackBishop1.setType(PieceType::BISHOP);
    blackBishop1.setColor(Color::BLACK);
    blackPieces.push_back(blackBishop1);

    Piece blackQueen;
    blackQueen.setId(28);
    blackQueen.setLocation(3, 7);
    blackQueen.setType(PieceType::QUEEN);
    blackQueen.setColor(Color::BLACK);
    blackPieces.push_back(blackQueen);

    Piece blackKing;
    blackKing.setId(29);
    blackKing.setLocation(4, 7);
    blackKing.setType(PieceType::KING);
    blackKing.setColor(Color::BLACK);
    blackPieces.push_back(blackKing);

    Piece blackBishop2;
    blackBishop2.setId(30);
    blackBishop2.setLocation(5, 7);
    blackBishop2.setType(PieceType::BISHOP);
    blackBishop2.setColor(Color::BLACK);
    blackPieces.push_back(blackBishop2);

    Piece blackKnight2;
    blackKnight2.setId(31);
    blackKnight2.setLocation(6, 7);
    blackKnight2.setType(PieceType::KNIGHT);
    blackKnight2.setColor(Color::BLACK);
    blackPieces.push_back(blackKnight2);

    Piece blackRook2;
    blackRook2.setId(32);
    blackRook2.setLocation(7, 7);
    blackRook2.setType(PieceType::ROOK);
    blackRook2.setColor(Color::BLACK);
    blackPieces.push_back(blackRook2);
}

void Board::writeBoard() {
    std::array<std::array<std::string, 8>, 8> boardArray;
    for (auto& row : boardArray) {
        row.fill("~");
    }

    for (auto& row : boardMap) {
        row.fill(0);
    }

    for (const Piece& piece : whitePieces) {
        if (!piece.getIsAlive()) continue;

        int pieceX = piece.getX();
        int pieceY = piece.getY();

        boardArray[pieceY][pieceX] = getSymbol(piece);
        boardMap[pieceY][pieceX] = piece.getId();
    }

    for (const Piece& piece : blackPieces) {
        if (!piece.getIsAlive()) continue;

        int pieceX = piece.getX();
        int pieceY = piece.getY();

        boardArray[pieceY][pieceX] = getSymbol(piece);
        boardMap[pieceY][pieceX] = piece.getId();
    }

    std::cout << "  ";
    for (int col = 0; col < 8; ++col) {
        char colLabel = 'A' + col;
        std::cout << colLabel << " ";
    }
    std::cout << "\n";

    for (int row = 0; row < 8; ++row) {
        std::cout << row + 1 << " ";
        for (int col = 0; col < 8; ++col) {
            std::cout << boardArray[row][col] << " ";
        }
        std::cout << "\n";
    }
}

void Board::updateBoard() {
    // Implementation will be added later
}

void Board::pieceStatus() {
    for (const Piece& piece : whitePieces) {
        int id = piece.getId();
        aliveCheckWhite[id] = piece.getIsAlive();
    }

    for (const Piece& piece : blackPieces) {
        int id = piece.getId();
        aliveCheckBlack[id] = piece.getIsAlive();
    }
}

std::vector<std::pair<int, int>> Board::squareStatus(int x, int y, bool isWhite) {
    // Implementation will be added later
    return {};
}

int Board::helperInverse(int num) {
    return 7 - num;
}

bool Board::movePiece(int pieceId, int newX, int newY, bool isWhite) {
    // Move execution logic will be implemented later
    return false;
}

std::array<std::array<int, 8>, 8> Board::currentIdPlacement(std::vector<std::pair<int, int>> squareStatus, int x, int y, bool isWhite) {
    // Implementation will be added later
    return {};
}

std::string Board::getSymbol(const Piece& piece) const {
    static const std::unordered_map<PieceType, std::string> typeToSymbol = {
        {PieceType::PAWN, "P"},
        {PieceType::KNIGHT, "N"},
        {PieceType::ROOK, "R"},
        {PieceType::BISHOP, "B"},
        {PieceType::QUEEN, "Q"},
        {PieceType::KING, "K"}
    };

    auto it = typeToSymbol.find(piece.getType());
    if (it != typeToSymbol.end()) {
        std::string symbol = it->second;
        if (piece.getColor() == Color::BLACK) {
            symbol[0] = std::tolower(symbol[0]);
        }
        return symbol;
    }
    return "~";
}
