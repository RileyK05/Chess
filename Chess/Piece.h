#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <utility>

enum class Color { WHITE, BLACK };
enum class PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

class Board;  // forward declaration to avoid circular include

/**
 * @class Piece
 * @brief Encapsulates a single chess piece’s state and move logic.
 */
class Piece {
public:
    Piece();  ///< Initialize with defaults: at (0,0), pawn, white, alive.

    // --- Accessors ---
    int getX() const;               ///< Current file (0=a, …, 7=h)
    int getY() const;               ///< Current rank (0=8th, …, 7=1st)
    int getId() const;              ///< Unique piece identifier
    PieceType getType() const;      ///< Pawn, Knight, Bishop, Rook, Queen, or King
    Color getColor() const;         ///< WHITE or BLACK
    bool isAlive() const;           ///< True if not captured

    // --- Mutators ---
    void setLocation(int newX, int newY);  ///< Move piece to (newX,newY)
    void setIsAlive(bool newAlive);        ///< Mark captured/alive
    void setId(int newId);                 ///< Assign unique ID
    void setType(PieceType newType);       ///< Change piece type (e.g., promotion)
    void setColor(Color newColor);         ///< Set piece color

    /**
     * @brief Compute all legal destinations based on piece rules.
     * @param board Current board state for occupancy checks.
     * @return List of valid (x,y) target squares.
     */
    std::vector<std::pair<int, int>> getAllValidMoves(const Board& board) const;

    /**
     * @brief Basic move validity: in-bounds and not landing on friendly.
     * @param newX  Target file
     * @param newY  Target rank
     * @param board Board to check for occupying pieces
     * @return True if move is within [0,7]² and either empty or enemy-occupied.
     */
    bool isMoveValid(int newX, int newY, const Board& board) const;

private:
    int x{ 0 }, y{ 0 };              ///< Position on board (0–7)
    int id{ 0 };                   ///< Unique ID for tracking/mapping
    bool alive{ true };            ///< Alive = on board; false = captured
    PieceType type{ PieceType::PAWN };
    Color color{ Color::WHITE };
};

#endif // PIECE_H
