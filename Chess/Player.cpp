#include "Player.h"
#include "Board.h"
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
        return { {-1, -1}, {-1, -1} };
    }

    std::unordered_map<char, int> parsingMat = {
        {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3},
        {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}
    };

    if (parsingMat.find(input[0]) == parsingMat.end() ||
        parsingMat.find(input[2]) == parsingMat.end() ||
        !isdigit(input[1]) || !isdigit(input[3])) {
        std::cerr << "Invalid input characters. Use letters a-h and numbers 1-8." << std::endl;
        return { {-1, -1}, {-1, -1} };
    }

    int sourceX = parsingMat[input[0]];
    int sourceY = 8 - (input[1] - '0');
    int targetX = parsingMat[input[2]];
    int targetY = 8 - (input[3] - '0');

    if (sourceX < 0 || sourceX >= 8 || sourceY < 0 || sourceY >= 8 ||
        targetX < 0 || targetX >= 8 || targetY < 0 || targetY >= 8) {
        std::cerr << "Move coordinates out of bounds." << std::endl;
        return { {-1, -1}, {-1, -1} };
    }

    return { {sourceX, sourceY}, {targetX, targetY} };
}

bool Player::makeMove(Board& board) {
    auto moveCords = userInput();

    int currentX = moveCords.first.first;
    int currentY = moveCords.first.second;
    int moveToX = moveCords.second.first;
    int moveToY = moveCords.second.second;

    if (currentX == -1) {
        return false;
    }

    Piece* piece = board.getPieceAt(currentX, currentY);

    if (piece == nullptr) {
        std::cerr << "No piece found at the source coordinates." << std::endl;
        return false;
    }

    if (piece->getColor() != this->playerColor) {
        std::cerr << "You can only move your own pieces." << std::endl;
        return false;
    }

    std::vector<std::pair<int, int>> validMoves = piece->getAllValidMoves(board);
    bool moveIsValid = false;
    for (const auto& move : validMoves) {
        if (move.first == moveToX && move.second == moveToY) {
            moveIsValid = true;
            break;
        }
    }
    if (!moveIsValid) {
        std::cerr << "Move is not valid for the selected piece." << std::endl;
        return false;
    }

    Board testBoard = board;
    testBoard.movePiece(piece->getId(), moveToX, moveToY);

    if (testBoard.isPlayerInCheck(this->playerColor)) {
        std::cerr << "Move would put your own king in check. Invalid move." << std::endl;
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
        if (piece->getType() == PieceType::PAWN && (moveToY == 0 || moveToY == 7)) {
            char choice;
            std::cout << "Pawn reached the end of the board. Promote to (Q)ueen, (R)ook, (B)ishop, or k(N)ight? ";
            std::cin >> choice;
            choice = std::tolower(choice);
            switch (choice) {
            case 'q':
                piece->setType(PieceType::QUEEN);
                break;
            case 'r':
                piece->setType(PieceType::ROOK);
                break;
            case 'b':
                piece->setType(PieceType::BISHOP);
                break;
            case 'n':
                piece->setType(PieceType::KNIGHT);
                break;
            default:
                std::cout << "Invalid choice. Promoting to Queen by default." << std::endl;
                piece->setType(PieceType::QUEEN);
                break;
            }
        }

        Color opponentColor = (this->playerColor == Color::WHITE) ? Color::BLACK : Color::WHITE;
        if (board.isPlayerInCheck(opponentColor)) {
            std::cout << "You have put the opponent in check!" << std::endl;
            if (board.isCheckmate(opponentColor)) {
                std::cout << "Checkmate! You win!" << std::endl;
                board.setGameRunning(false);
            }
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
                std::vector<std::pair<int, int>> legalMoves;
                for (const auto& move : moves) {
                    Board testBoard = board;
                    testBoard.movePiece(piece->getId(), move.first, move.second);
                    if (!testBoard.isPlayerInCheck(playerColor)) {
                        legalMoves.push_back(move);
                    }
                }
                if (!legalMoves.empty()) {
                    pieceMovesMap[piece->getId()] = legalMoves;
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
