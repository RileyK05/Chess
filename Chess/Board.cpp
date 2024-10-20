#include <unordered_map>
#include <vector>
#include <iostream>
#include <array>
#include "Board.h"
#include "Player.h"
#include "Bot.h"


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

bool Piece::moveValidCheck(int newX, int newY) const {
    switch (type) {
    case PieceType::PAWN:
        if (color == Color::WHITE) {

        }
        else if (color == Color::BLACK) {

        }
        break;

    case PieceType::KNIGHT:
        if (color == Color::WHITE) {

        }
        else if (color == Color::BLACK) {

        }
        break;

    case PieceType::ROOK:
        if (color == Color::WHITE) {

        }
        else if (color == Color::BLACK) {

        }
        break;

    case PieceType::BISHOP:
        if (color == Color::WHITE) {

        }
        else if (color == Color::BLACK) {

        }
        break;

    case PieceType::QUEEN:
        if (color == Color::WHITE) {

        }
        else if (color == Color::BLACK) {

        }
        break;

    case PieceType::KING:
        if (color == Color::WHITE) {

        }
        else if (color == Color::BLACK) {

        }
        break;

    default:
        break;
    }

    return false;
}



Board::Board() {
    for (int i = 0; i < 8; i++) {
        Piece whitePawn;
        whitePawn.setId(i + 1);
        whitePawn.setLocation(i, 1);
        whitePawn.setType(PieceType::PAWN);
        whitePawn.setColor(Color::WHITE);
        whitePieces.push_back(whitePawn);
    }

    Piece whiteKnight1;
    whiteKnight1.setId(9);
    whiteKnight1.setLocation(0, 0);
    whiteKnight1.setType(PieceType::KNIGHT);
    whiteKnight1.setColor(Color::WHITE);
    whitePieces.push_back(whiteKnight1);

    Piece whiteKnight2;
    whiteKnight2.setId(10);
    whiteKnight2.setLocation(7, 0);
    whiteKnight2.setType(PieceType::KNIGHT);
    whiteKnight2.setColor(Color::WHITE);
    whitePieces.push_back(whiteKnight2);

    Piece whiteRook1;
    whiteRook1.setId(11);
    whiteRook1.setLocation(1, 0);
    whiteRook1.setType(PieceType::ROOK);
    whiteRook1.setColor(Color::WHITE);
    whitePieces.push_back(whiteRook1);

    Piece whiteRook2;
    whiteRook2.setId(12);
    whiteRook2.setLocation(6, 0);
    whiteRook2.setType(PieceType::ROOK);
    whiteRook2.setColor(Color::WHITE);
    whitePieces.push_back(whiteRook2);

    Piece whiteBishop1;
    whiteBishop1.setId(13);
    whiteBishop1.setLocation(2, 0);
    whiteBishop1.setType(PieceType::BISHOP);
    whiteBishop1.setColor(Color::WHITE);
    whitePieces.push_back(whiteBishop1);

    Piece whiteBishop2;
    whiteBishop2.setId(14);
    whiteBishop2.setLocation(5, 0);
    whiteBishop2.setType(PieceType::BISHOP);
    whiteBishop2.setColor(Color::WHITE);
    whitePieces.push_back(whiteBishop2);

    Piece whiteQueen;
    whiteQueen.setId(15);
    whiteQueen.setLocation(4, 0);
    whiteQueen.setType(PieceType::QUEEN);
    whiteQueen.setColor(Color::WHITE);
    whitePieces.push_back(whiteQueen);

    Piece whiteKing;
    whiteKing.setId(16);
    whiteKing.setLocation(3, 0);
    whiteKing.setType(PieceType::KING);
    whiteKing.setColor(Color::WHITE);
    whitePieces.push_back(whiteKing);

    for (int i = 0; i < 8; i++) {
        Piece blackPawn;
        blackPawn.setId(i + 1);
        blackPawn.setLocation(i, 1);
        blackPawn.setType(PieceType::PAWN);
        blackPawn.setColor(Color::BLACK);
        blackPieces.push_back(blackPawn);
    }

    Piece blackKnight1;
    blackKnight1.setId(9);
    blackKnight1.setLocation(0, 0);
    blackKnight1.setType(PieceType::KNIGHT);
    blackKnight1.setColor(Color::BLACK);
    blackPieces.push_back(blackKnight1);

    Piece blackKnight2;
    blackKnight2.setId(10);
    blackKnight2.setLocation(7, 0);
    blackKnight2.setType(PieceType::KNIGHT);
    blackKnight2.setColor(Color::BLACK);
    blackPieces.push_back(blackKnight2);

    Piece blackRook1;
    blackRook1.setId(11);
    blackRook1.setLocation(1, 0);
    blackRook1.setType(PieceType::ROOK);
    blackRook1.setColor(Color::BLACK);
    blackPieces.push_back(blackRook1);

    Piece blackRook2;
    blackRook2.setId(12);
    blackRook2.setLocation(6, 0);
    blackRook2.setType(PieceType::ROOK);
    blackRook2.setColor(Color::BLACK);
    blackPieces.push_back(blackRook2);

    Piece blackBishop1;
    blackBishop1.setId(13);
    blackBishop1.setLocation(2, 0);
    blackBishop1.setType(PieceType::BISHOP);
    blackBishop1.setColor(Color::BLACK);
    blackPieces.push_back(blackBishop1);

    Piece blackBishop2;
    blackBishop2.setId(14);
    blackBishop2.setLocation(5, 0);
    blackBishop2.setType(PieceType::BISHOP);
    blackBishop2.setColor(Color::BLACK);
    blackPieces.push_back(blackBishop2);

    Piece blackQueen;
    blackQueen.setId(15);
    blackQueen.setLocation(4, 0);
    blackQueen.setType(PieceType::QUEEN);
    blackQueen.setColor(Color::BLACK);
    blackPieces.push_back(blackQueen);

    Piece blackKing;
    blackKing.setId(16);
    blackKing.setLocation(3, 0);
    blackKing.setType(PieceType::KING);
    blackKing.setColor(Color::BLACK);
    blackPieces.push_back(blackKing);
}

void Board::writeBoard() {
    std::array<std::array<std::string, 8>, 8> boardArray;
    for (auto& row : boardArray) {
        row.fill("~");
    }

    for (const Piece& piece : whitePieces) {
        if (!piece.getIsAlive()) continue;

        int pieceX = piece.getX();
        int pieceY = piece.getY();

        boardArray[pieceY][pieceX] = getSymbol(piece, true);
    }

    for (const Piece& piece : blackPieces) {
        if (!piece.getIsAlive()) continue;

        int pieceX = piece.getX();
        int pieceY = piece.getY();

        boardArray[pieceY][pieceX] = getSymbol(piece, false);
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

void Board::boardStatus() {
}

int Board::helperInverse(int num) {
    return 7 - num;
}

bool Board::movePiece(int pieceId, int newX, int newY, bool isWhite) {
    if (isWhite) {
    }
    else {
    }
    return false;
}

std::string Board::getSymbol(const Piece& piece, bool isWhite) const {
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
        if (isWhite) {
            return it->second;
        }
        else {
            std::string symbol = it->second;
            if (!symbol.empty()) {
                symbol[0] = std::tolower(symbol[0]);
            }
            return symbol;
        }
    }
    return "~";
}
