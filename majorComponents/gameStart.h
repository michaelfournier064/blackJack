#ifndef GAME_START_H
#define GAME_START_H

#include "../majorComponents/cardDrawing.h"
#include "../helperFunctions/errorHandler.h"
#include "../helperFunctions/assistingFunctions.h"

#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <algorithm> // Include this for std::transform

class GameStart {
private:
    Auxiliary& auxiliary; // Reference to Auxiliary instance
    inputErrors playerError;
    Card cardGenerator;

    int playerAmount{};

public:
    int dealerPlayerNumber{};
    int userPlayerNumber{};

    // Constructor to initialize GameStart with an Auxiliary reference
    GameStart(Auxiliary& aux) : auxiliary(aux) {}

        int placeBet(int playerId) {
        int bet = 0;
        while (true) {
            std::cout << "Player " << playerId << ", you have " 
                      << auxiliary.getBankroll(playerId) << " units.\n";
            std::cout << "Enter your bet: ";
            std::cin >> bet;

            if (bet > 0 && bet <= auxiliary.getBankroll(playerId)) {
                std::cout << "You bet " << bet << " units.\n";
                return bet;
            } else {
                std::cout << "Invalid bet. Make sure it is positive and within your bankroll.\n";
            }
        }
    }

    bool playAgain() const {
        std::string choice;
        while (true) {
            std::cout << "Would you like to play another game? (yes/no): ";
            std::cin >> choice;

            // Convert input to lowercase
            std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

            if (choice == "yes" || choice == "y") {
                return true;  // Play another game
            } else if (choice == "no" || choice == "n") {
                return false; // End the game
            } else {
                std::cout << "Invalid choice. Please enter 'yes' or 'no'.\n";
            }
        }
    } 
    void gameInitialization() {
        do {
            std::cout << "How many players will be participating in this game? ";
            if (!(std::cin >> playerAmount)) {
                std::cin.clear(); // Clear error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                std::cout << "Invalid input. Please enter a number." << std::endl;
                continue;
            }
        } while (!playerError.playerAmountError(playerAmount));

        dealerPlayerNumber = playerAmount; // Set the dealer to the last player
    }

    void playerAssignment() {
        userPlayerNumber = auxiliary.restrictedRandom(1, playerAmount - 1);
        std::cout << "You are player " << userPlayerNumber << std::endl;
        std::cout << "The dealer is player " << dealerPlayerNumber << std::endl;
    }

    void initialDealing() {
        std::cout << "\nDealing initial cards..." << std::endl;

        for (int i = 1; i <= playerAmount; ++i) {
            if (i == userPlayerNumber) {
                std::cout << "Your (Player " << i << ") cards are:\n";
            } else if (i == dealerPlayerNumber) {
                std::cout << "Dealer (Player " << i << ")'s cards are:\n";
            } else {
                std::cout << "Player " << i << "'s cards are:\n";
            }

            // Generate two cards for each player
            for (int j = 0; j < 2; ++j) {
                cardGenerator.generateCard();
                std::string cardValue = cardGenerator.getCardValue();
                std::string cardType = cardGenerator.getCardType();
                auxiliary.addCardToPlayer(i, cardValue, cardType); // Store the card dynamically
                std::cout << "- " << cardValue << " of " << cardType << std::endl;
            }
        }
    }
    bool userHitOrStand() {
        std::string choice;
        while (true) {
            std::cout << "Do you want to hit or stand? (hit/stand): ";
            std::cin >> choice;

            // Convert input to lowercase for validation
            std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

            if (choice == "hit") {
                return true;  // User chose to hit
            } else if (choice == "stand") {
                return false; // User chose to stand
            } else {
                std::cout << "Invalid choice. Please enter 'hit' or 'stand'.\n";
            }
        }
    }
};

#endif