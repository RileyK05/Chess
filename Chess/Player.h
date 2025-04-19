#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include <vector>
#include <utility>
#include <string>
#include <unordered_map>
#include <exception>

// Signal to save the game
class SaveGameException : public std::exception {
public:
    const char* what() const noexcept override { return "SaveGameRequested"; }
};

// Signal to quit the game
class QuitGameException : public std::exception {
public:
    const char* what() const noexcept override { return "QuitGameRequested"; }
};

// Represents a player (human or AI)
class Player {
public:
    Player(Color color, bool isHuman = true);
    virtual ~Player() = default;

    // Attempt a move; may throw SaveGameException or QuitGameException
    virtual bool makeMove(Board& board);

    // Get all legal moves for each piece (excluding moves into check)
    std::unordered_map<int, std::vector<std::pair<int, int>>> validMoves(const Board& board) const;

    // Player properties
    Color getColor() const;
    void setColor(Color color);
    bool isHuman() const;
    void setHuman(bool human);

    // Captured pieces management
    void addCapturedPiece(Piece* piece);
    const std::vector<Piece*>& getCapturedPieces() const;
    void displayCapturedPieces() const;

protected:
    // Parse user input (e.g., "e2e4"); may throw Save/Quit exceptions
    std::pair<std::pair<int, int>, std::pair<int, int>> userInput();

private:
    Color playerColor;
    bool human;
    std::vector<Piece*> capturedPieces;

    // Convert PieceType to string for display
    std::string pieceTypeToString(PieceType type) const;
};

#endif // PLAYER_H
