#include "Player.h"
#include <iostream>
#include <cctype>
#include <unordered_map>

Player::Player(Color color, bool isHuman) {
    this->human = isHuman;
    this->playerColor = color;
}

std::pair<std::pair<int, int>, std::pair<int, int>> Player::userInput() {
    std::string input;
    std::cout << "Enter your move (e.g., e2e4): ";
    std::cin >> input;

    for (char& c : input) {
        c = std::tolower(c);
    }

    if (input.size() < 4) {
        std::cerr << "Invalid input format. Please enter moves like e2e4." << std::endl;
        return { {0, 0}, {0, 0} };
    }

    std::unordered_map<char, int> parsingMat = {
        {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3},
        {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}
    };

    if (parsingMat.find(input[0]) == parsingMat.end() ||
        parsingMat.find(input[2]) == parsingMat.end() ||
        !isdigit(input[1]) || !isdigit(input[3])) {
        std::cerr << "Invalid input characters. Use letters a-h and numbers 1-8." << std::endl;
        return { {0, 0}, {0, 0} };
    }

    int sourceX = parsingMat[input[0]];
    int sourceY = input[1] - '1';
    int targetX = parsingMat[input[2]];
    int targetY = input[3] - '1';

    if (sourceX < 0 || sourceX >= 8 || sourceY < 0 || sourceY >= 8 ||
        targetX < 0 || targetX >= 8 || targetY < 0 || targetY >= 8) {
        std::cerr << "Move coordinates out of bounds." << std::endl;
        return { {0, 0}, {0, 0} };
    }

    return { {sourceX, sourceY}, {targetX, targetY} };
}

bool Player::makeMove(Board& board) {
    auto moveCords = userInput();

    int currentX = moveCords.first.first;
    int currentY = moveCords.first.second;
    int moveToX = moveCords.second.first;
    int moveToY = moveCords.second.second;

    Piece* piece = board.getPieceAt(currentX, currentY);

    if (piece == nullptr) {
        std::cerr << "No piece found at the source coordinates." << std::endl;
        return false;
    }

    if (piece->getColor() != this->playerColor) {
        std::cerr << "You can only move your own pieces." << std::endl;
        return false;
    }

    auto moveResult = board.movePiece(piece->getId(), moveToX, moveToY);
    bool moveSuccessful = moveResult.first;
    Piece* capturedPiece = moveResult.second;

    if (moveSuccessful) {
        if (capturedPiece != nullptr) {
            addCapturedPiece(capturedPiece);
            std::cout << "Captured piece ID " << capturedPiece->getId() << "!" << std::endl;
        }
    }
    else {
        std::cerr << "Move failed. Invalid move." << std::endl;
    }

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

void Player::setHuman(bool isHuman) {
    human = isHuman;
}

void Player::addCapturedPiece(Piece* piece) {
    capturedPieces.push_back(piece);
}

const std::vector<Piece*>& Player::getCapturedPieces() const {
    return capturedPieces;
}

void Player::displayCapturedPieces() const {
    if (capturedPieces.empty()) {
        std::cout << "No captured pieces.\n";
        return;
    }

    std::cout << "Captured Pieces:\n";
    for (const Piece* piece : capturedPieces) {
        std::cout << "ID: " << piece->getId()
            << " Type: " << pieceTypeToString(piece->getType())
            << " Color: " << (piece->getColor() == Color::WHITE ? "White" : "Black")
            << "\n";
    }
}

std::string Player::pieceTypeToString(PieceType type) const {
    switch (type) {
    case PieceType::PAWN: return "Pawn";
    case PieceType::KNIGHT: return "Knight";
    case PieceType::BISHOP: return "Bishop";
    case PieceType::ROOK: return "Rook";
    case PieceType::QUEEN: return "Queen";
    case PieceType::KING: return "King";
    default: return "Unknown";
    }
}
