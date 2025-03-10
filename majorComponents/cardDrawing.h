#ifndef CARD_DRAWING_H
#define CARD_DRAWING_H

#include "../helperFunctions/assistingFunctions.h"
#include "../majorComponents/gameStart.h"

#include <array>
#include <iostream>
#include <random>

class Card {
private:
    const std::array<std::string, 13> cardValues{
        "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"
    };
    const std::array<std::string, 4> cardTypes{
        "Hearts", "Diamonds", "Spades", "Clubs"
    };
    std::string cardValue{};
    std::string cardType{};

public:
    void generateCard() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<std::size_t> valueDist(0, cardValues.size() - 1);
        std::uniform_int_distribution<std::size_t> typeDist(0, cardTypes.size() - 1);

        cardType = cardTypes[typeDist(gen)];
        cardValue = cardValues[valueDist(gen)];
    }

    std::string getCardValue() const {
        return cardValue;
    }

    std::string getCardType() const {
        return cardType;
    }
    
    void dealerForcedDraw(int dealerPlayerNumber, Auxiliary& auxiliary) {
        std::unordered_map<int, int> playerScores = auxiliary.calculatePlayerScores();

        auto it = playerScores.find(dealerPlayerNumber);
        if (it == playerScores.end()) {
            std::cerr << "Error: Dealer not found in player scores.\n";
            return;
        }

        int dealerScore = it->second;

        if (dealerScore >= 17) {
            std::cout << "The dealer will stand with a score of " << dealerScore << "." << std::endl;
        } else {
            std::cout << "The dealer will hit with a score of " << dealerScore << "." << std::endl;

            // Dealer draws a new card
            generateCard();
            std::string newCardValue = getCardValue();
            std::string newCardType = getCardType();

            // Add the new card to the dealer's hand
            auxiliary.addCardToPlayer(dealerPlayerNumber, newCardValue, newCardType);

            // Print the new card
            std::cout << "The dealer draws: " << newCardValue << " of " << newCardType << std::endl;

            // Recalculate the dealer's score
            playerScores = auxiliary.calculatePlayerScores();
            dealerScore = playerScores[dealerPlayerNumber];

            // Print the dealer's new score
            std::cout << "The dealer's new score is: " << dealerScore << "." << std::endl;

            // If the dealer's score is still <= 16, they must draw again
            if (dealerScore <= 16) {
                dealerForcedDraw(dealerPlayerNumber, auxiliary);
            }
        }
    }
};

#endif
