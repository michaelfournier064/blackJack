#include "cardDrawing.h"

void Card::generateCard() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<std::size_t> valueDist(0, cardValues.size() - 1);
    std::uniform_int_distribution<std::size_t> typeDist(0, cardTypes.size() - 1);

    cardType = cardTypes[typeDist(gen)];
    cardValue = cardValues[valueDist(gen)];
}

std::string Card::getCardValue() const {
    return cardValue;
}

std::string Card::getCardType() const {
    return cardType;
}

void Card::dealerForcedDraw(int dealerPlayerNumber, Auxiliary& auxiliary) {
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
        generateCard();
        std::string newCardValue = getCardValue();
        std::string newCardType = getCardType();
        auxiliary.addCardToPlayer(dealerPlayerNumber, newCardValue, newCardType);
        std::cout << "The dealer draws: " << newCardValue << " of " << newCardType << std::endl;
        playerScores = auxiliary.calculatePlayerScores();
        dealerScore = playerScores[dealerPlayerNumber];
        std::cout << "The dealer's new score is: " << dealerScore << "." << std::endl;
        if (dealerScore <= 16) {
            dealerForcedDraw(dealerPlayerNumber, auxiliary);
        }
    }
}
