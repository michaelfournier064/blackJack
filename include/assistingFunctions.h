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
    std::unordered_map<int, std::vector<std::vector<std::string>>> playerHands;
    std::unordered_map<int, int> playerBankrolls;

    static constexpr int FACE_CARD_VALUE = 10;
    static constexpr int ACE_HIGH_VALUE = 11;
    static constexpr int ACE_LOW_VALUE = 1;
    static constexpr int BLACKJACK_SCORE = 21;

public:
    void initializeBankroll(int playerId, int initialAmount = 100);
    int getBankroll(int playerId) const;
    void adjustBankroll(int playerId, int amount);
    void printBankrolls() const;
    void addCardToPlayer(int playerId, const std::string& cardValue, const std::string& cardType);
    const std::unordered_map<int, std::vector<std::vector<std::string>>>& getPlayerHands() const;
    void resetPlayerHands();
    std::optional<int> checkBlackjack(int dealerPlayerNumber, int usersPlayerNumber) const;
    std::vector<int> checkBust() const;
    std::unordered_map<int, int> calculatePlayerScores() const;
    void calculateAndPrintScores(int userPlayerNumber, int dealerPlayerNumber) const;
    void printAllHands(int userPlayerNumber, int dealerPlayerNumber) const;
    int restrictedRandom(int lower, int upper);
};

#endif
