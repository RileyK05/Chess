/**
 * @file main.cpp
 * @brief Main program file for the chess game.
 *
 * This file contains the main function and menu system for the chess game. It creates a Menu object
 * to allow the user to start a new game, load a saved game, view the game log, or exit. The game logic
 * uses the GameSession class to manage each game.
 */
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include "Board.h"
#include "Player.h"
#include "Bot.h"

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

 /**
  * @class GameSession
  * @brief Manages a single game session between a human player and the AI.
  *
  * The GameSession class ties together the Board, Player (human), and Bot (AI) for a single game.
  * It handles turn-by-turn execution of the game, including input handling, turn switching,
  * detecting game end conditions, saving mid-game, and logging results.
  */
class GameSession {
public:
    GameSession() : human(Color::WHITE, true), ai(Color::BLACK) {
        // Board is initialized with default constructor (standard chess starting positions).
    }

    /**
     * @brief Start a new game session loop.
     * @param loadFilename If non-empty, a saved game state will be loaded from this file before starting.
     *
     * This function runs the main game loop, alternating turns between the human and AI. It catches
     * SaveGameException and QuitGameException to handle save and quit commands from the human player.
     * When the game ends (by checkmate, stalemate, or user quitting), it logs the game result to a file.
     */
    void play(const std::string& loadFilename = "") {
        try {
            if (!loadFilename.empty()) {
                board.loadFromFile(loadFilename);
                std::cout << "Game loaded from " << loadFilename << ".\n";
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error loading game: " << e.what() << std::endl;
            return;
        }

        bool gameAborted = false;
        // Main game loop
        while (board.isGameRunning()) {
            system(CLEAR_COMMAND);
            board.displayBoard();
            if (board.currentPlayerColor == human.getColor()) {
                // Human's turn
                std::cout << "Your turn (" << (human.getColor() == Color::WHITE ? "White" : "Black") << "):" << std::endl;
                bool moveMade = false;
                // Keep prompting until a valid move is made or the player decides to save/quit.
                while (!moveMade) {
                    try {
                        moveMade = human.makeMove(board);
                    }
                    catch (const SaveGameException&) {
                        // Handle save request.
                        std::string filename;
                        std::cout << "Enter filename to save the game: ";
                        std::cin >> filename;
                        try {
                            board.saveToFile(filename);
                            std::cout << "Game saved to " << filename << ".\n";
                        }
                        catch (const std::exception& ex) {
                            std::cerr << "Failed to save game: " << ex.what() << std::endl;
                        }
                        // Continue the loop without changing turn.
                        continue;
                    }
                    catch (const QuitGameException&) {
                        // Handle quit request: abort the game and return to menu.
                        std::cout << "Quitting to main menu...\n";
                        gameAborted = true;
                        board.setGameRunning(false); // mark game as no longer running
                        break;
                    }
                    if (!moveMade) {
                        std::cout << "Invalid move. Try again." << std::endl;
                    }
                }
                if (gameAborted) break; // exit the outer game loop if user quit
            }
            else {
                // AI's turn
                std::cout << "AI's turn (" << (ai.getColor() == Color::WHITE ? "White" : "Black") << "):" << std::endl;
                bool moveMade = ai.makeMove(board);
                if (!moveMade) {
                    // No valid moves for AI: game over (either checkmate or stalemate).
                    if (board.isPlayerInCheck(ai.getColor())) {
                        std::cout << "AI has no moves and is in check - checkmate!" << std::endl;
                    }
                    else {
                        std::cout << "AI has no moves - stalemate!" << std::endl;
                    }
                    board.setGameRunning(false);
                }
            }
        }

        // Game loop ended.
        system(CLEAR_COMMAND);
        board.displayBoard();
        std::string result;
        if (gameAborted) {
            result = "Game aborted by user.";
        }
        else {
            // Determine result of the finished game.
            if (board.isPlayerInCheck(board.currentPlayerColor)) {
                // The current player to move is in check and has no moves: checkmate.
                Color winner = (board.currentPlayerColor == Color::WHITE ? Color::BLACK : Color::WHITE);
                result = (winner == Color::WHITE ? "White" : "Black");
                result += " wins by checkmate.";
            }
            else {
                result = "Draw by stalemate.";
            }
        }
        std::cout << "Game over. " << result << std::endl;

        // Log the game result to a log file.
        if (!gameAborted) {
            logGameResult(result);
        }
    }

private:
    Board board;
    Player human;
    Bot ai;

    /**
     * @brief Log the game outcome and moves to a log file.
     * @param result A description of the game result (e.g., "White wins by checkmate.")
     *
     * This function appends the result of the game to a "game_log.txt" file, including a timestamp and move count.
     */
    void logGameResult(const std::string& result) {
        std::ofstream logFile("game_log.txt", std::ios::app);
        if (!logFile.is_open()) {
            std::cerr << "Could not open log file to record game result." << std::endl;
            return;
        }
        // Get current date/time for log.
        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);
        char timeBuf[100];
        if (localTime && std::strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", localTime)) {
            logFile << "[" << timeBuf << "] ";
        }
        // Count the number of half-moves (plies) in the game using move history.
        std::stack<Move> moves = board.getMoveHistory();
        int halfMoves = moves.size();
        int fullMoves = (halfMoves + 1) / 2;
        logFile << result << " Moves: " << fullMoves << " full moves (" << halfMoves << " plies)." << std::endl;
        logFile.close();
    }
};

/**
 * @class Menu
 * @brief Provides a text-based menu for the user to start new games, load games, view logs, or exit.
 */
class Menu {
public:
    /**
     * @brief Display the main menu and handle user selection.
     *
     * This function uses recursion for handling menu navigation and repeats until the user chooses to exit.
     */
    void show() {
        std::cout << "\n=== Chess Game Menu ===\n";
        std::cout << "1. Start New Game\n";
        std::cout << "2. Load Game from File\n";
        std::cout << "3. View Game Log\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter choice (1-4): ";
        int choice;
        if (!(std::cin >> choice)) {
            // Handle non-integer input
            std::cin.clear();
            std::string dummy;
            std::getline(std::cin, dummy);
            choice = 0;
        }
        switch (choice) {
        case 1: {
            // Start a new game.
            GameSession game;
            game.play();
            break;
        }
        case 2: {
            // Load a game from a file.
            std::string filename;
            std::cout << "Enter filename to load: ";
            std::cin >> filename;
            GameSession game;
            game.play(filename);
            break;
        }
        case 3: {
            // View past game logs.
            viewLog();
            break;
        }
        case 4: {
            std::cout << "Exiting program. Goodbye!" << std::endl;
            return;
        }
        default: {
            std::cout << "Invalid choice. Please try again." << std::endl;
            // Use recursion to show the menu again for invalid input.
            show();
            return;
        }
        }
        // After handling the choice (if not exit), show the menu again.
        show();
    }

private:
    /**
     * @brief Display the contents of the game log file.
     */
    void viewLog() {
        std::ifstream logFile("game_log.txt");
        if (!logFile.is_open()) {
            std::cout << "No log file found or unable to open log file." << std::endl;
            return;
        }
        std::cout << "\n--- Game Log ---" << std::endl;
        std::string line;
        while (std::getline(logFile, line)) {
            std::cout << line << std::endl;
        }
        std::cout << "----------------\n";
        logFile.close();
    }
};

int main() {
    Menu menu;
    menu.show();
    return 0;
}
