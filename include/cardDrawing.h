#ifndef CARD_DRAWING_H
#define CARD_DRAWING_H

#include "assistingFunctions.h"

#include <array>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>

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
    void generateCard();
    std::string getCardValue() const;
    std::string getCardType() const;
    void dealerForcedDraw(int dealerPlayerNumber, Auxiliary& auxiliary);
};

#endif
