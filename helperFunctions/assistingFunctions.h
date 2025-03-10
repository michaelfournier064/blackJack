#ifndef ASSISTING_FUNCTIONS_H
#define ASSISTING_FUNCTIONS_H

#include <random>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <optional>


class Auxiliary {
private:
    std::unordered_map<int, std::vector<std::vector<std::string>>> playerHands; // Stores player hands
    std::unordered_map<int, int> playerBankrolls; // Stores player bankrolls

    static constexpr int FACE_CARD_VALUE = 10;
    static constexpr int ACE_HIGH_VALUE = 11;
    static constexpr int ACE_LOW_VALUE = 1;
    static constexpr int BLACKJACK_SCORE = 21;


public:
    void initializeBankroll(int playerId, int initialAmount = 100) {
        playerBankrolls[playerId] = initialAmount;
    }

    // Get the bankroll of a player
    int getBankroll(int playerId) const {
        auto it = playerBankrolls.find(playerId);
        if (it != playerBankrolls.end()) {
            return it->second;
        }
        throw std::runtime_error("Player ID not found in bankrolls.");
    }

    // Adjust bankroll (positive for winnings, negative for losses)
    void adjustBankroll(int playerId, int amount) {
        playerBankrolls[playerId] += amount;
    }

    // Print the bankroll of all players
    void printBankrolls() const {
        std::cout << "\n=====================================\n";
        std::cout << "          Player Bankrolls           \n";
        std::cout << "=====================================\n";
        for (const auto& [playerId, bankroll] : playerBankrolls) {
            std::cout << "Player " << playerId << ": " << bankroll << " units\n";
        }
    }

    // Add a card to a player's hand
    void addCardToPlayer(int playerId, const std::string& cardValue, const std::string& cardType) {
        playerHands[playerId].push_back({cardValue, cardType});
    }

    // Retrieve all hands (for external use if needed)
    const std::unordered_map<int, std::vector<std::vector<std::string>>>& getPlayerHands() const {
        return playerHands;
    }

    void resetPlayerHands() {
        playerHands.clear();
    }
    std::optional<int> checkBlackjack(int dealerPlayerNumber, int usersPlayerNumber) const {
        for (const auto& [playerId, hand] : playerHands) {
            if (hand.size() == 2) { // Blackjack requires exactly two cards
                int score = calculatePlayerScores().at(playerId); // Get player's score
                if (score == 21) {
                    if (playerId == dealerPlayerNumber) {
                        std::cout << "Dealer (Player " << playerId << ") has Blackjack!" << std::endl;
                    } else if (playerId == usersPlayerNumber) {
                        std::cout << "You (Player " << playerId << ") have Blackjack!" << std::endl;
                    } else {
                        std::cout << "Player " << playerId << " has Blackjack!" << std::endl;
                    }
                    return playerId; // Return the ID of the player with Blackjack
                }
            }
        }
        return std::nullopt; // No player has Blackjack
    }
    
    std::vector<int> checkBust() const {
        std::vector<int> bustedPlayers;
        std::unordered_map<int, int> playerScores = calculatePlayerScores();

        for (const auto& [playerId, score] : playerScores) {
            if (score > 21) {
                bustedPlayers.push_back(playerId);

                // Output which player has busted
                if (playerHands.at(playerId).size() > 0) { // Ensure player has cards
                    std::cout << "Player " << playerId << " has busted with a score of " << score << "!" << std::endl;
                }
            }
        }
        return bustedPlayers; // Return the IDs of players who busted
    }

    // Calculate the total value of cards for each player
    std::unordered_map<int, int> calculatePlayerScores() const {
        std::unordered_map<int, int> playerScores;

        for (const auto& [playerId, hand] : playerHands) {
            int totalValue = 0;
            int aceCount = 0;

            for (const auto& card : hand) {
                const std::string& cardValue = card[0]; // Card value (e.g., "2", "King", "Ace")

                // Determine the value of the card
                if (cardValue == "Jack" || cardValue == "Queen" || cardValue == "King") {
                    totalValue += FACE_CARD_VALUE;
                } else if (cardValue == "Ace") {
                    totalValue += ACE_HIGH_VALUE;
                    aceCount++;
                } else {
                    totalValue += std::stoi(cardValue);
                }
            }

            // Adjust for Aces if totalValue exceeds 21
            while (totalValue > 21 && aceCount > 0) {
                totalValue -= 10; // Reduce Ace value from 11 to 1
                aceCount--;
            }

            playerScores[playerId] = totalValue;
        }

        return playerScores;
    }
    
    void calculateAndPrintScores(int userPlayerNumber, int dealerPlayerNumber) const {
    std::unordered_map<int, int> playerScores = calculatePlayerScores();

    std::cout << "\nScores:\n";
    for (const auto& [playerId, score] : playerScores) {
        if (playerId == userPlayerNumber) {
            std::cout << "Your (Player " << playerId << ") score: " << score << std::endl;
        } else if (playerId == dealerPlayerNumber) {
            std::cout << "Dealer (Player " << playerId << ") score: " << score << std::endl;
        } else {
            std::cout << "Player " << playerId << " score: " << score << std::endl;
        }
    }
}

    // Print all hands (for debugging or game updates)
    void printAllHands(int userPlayerNumber, int dealerPlayerNumber) const {
        std::cout << "\nCurrent hands of all players:\n";
        for (const auto& [playerId, hand] : playerHands) {
            if (playerId == userPlayerNumber) {
                std::cout << "Your (Player " << playerId << ") cards:\n";
            } else if (playerId == dealerPlayerNumber) {
                std::cout << "Dealer (Player " << playerId << ") cards:\n";
            } else {
                std::cout << "Player " << playerId << " cards:\n";
            }

            for (const auto& card : hand) {
                std::cout << "- " << card[0] << " of " << card[1] << std::endl;
            }
        }
    }
    // Generate a random number within a range
    int restrictedRandom(int lower, int upper) {
        if (lower > upper) {
            throw std::invalid_argument("Lower bound must not exceed upper bound.");
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(lower, upper);
        return dist(gen);
    }
};

#endif