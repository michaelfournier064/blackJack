#include "assistingFunctions.h"

void Auxiliary::initializeBankroll(int playerId, int initialAmount) {
    playerBankrolls[playerId] = initialAmount;
}

int Auxiliary::getBankroll(int playerId) const {
    auto it = playerBankrolls.find(playerId);
    if (it != playerBankrolls.end()) {
        return it->second;
    }
    throw std::runtime_error("Player ID not found in bankrolls.");
}

void Auxiliary::adjustBankroll(int playerId, int amount) {
    playerBankrolls[playerId] += amount;
}

void Auxiliary::printBankrolls() const {
    std::cout << "\n=====================================\n";
    std::cout << "          Player Bankrolls           \n";
    std::cout << "=====================================\n";
    for (const auto& [playerId, bankroll] : playerBankrolls) {
        std::cout << "Player " << playerId << ": " << bankroll << " units\n";
    }
}

void Auxiliary::addCardToPlayer(int playerId, const std::string& cardValue, const std::string& cardType) {
    playerHands[playerId].push_back({cardValue, cardType});
}

const std::unordered_map<int, std::vector<std::vector<std::string>>>& Auxiliary::getPlayerHands() const {
    return playerHands;
}

void Auxiliary::resetPlayerHands() {
    playerHands.clear();
}

std::optional<int> Auxiliary::checkBlackjack(int dealerPlayerNumber, int usersPlayerNumber) const {
    for (const auto& [playerId, hand] : playerHands) {
        if (hand.size() == 2) {
            int score = calculatePlayerScores().at(playerId);
            if (score == BLACKJACK_SCORE) {
                if (playerId == dealerPlayerNumber) {
                    std::cout << "Dealer (Player " << playerId << ") has Blackjack!" << std::endl;
                } else if (playerId == usersPlayerNumber) {
                    std::cout << "You (Player " << playerId << ") have Blackjack!" << std::endl;
                } else {
                    std::cout << "Player " << playerId << " has Blackjack!" << std::endl;
                }
                return playerId;
            }
        }
    }
    return std::nullopt;
}

std::vector<int> Auxiliary::checkBust() const {
    std::vector<int> bustedPlayers;
    std::unordered_map<int, int> playerScores = calculatePlayerScores();

    for (const auto& [playerId, score] : playerScores) {
        if (score > BLACKJACK_SCORE) {
            bustedPlayers.push_back(playerId);
            if (playerHands.at(playerId).size() > 0) {
                std::cout << "Player " << playerId << " has busted with a score of " << score << "!" << std::endl;
            }
        }
    }
    return bustedPlayers;
}

std::unordered_map<int, int> Auxiliary::calculatePlayerScores() const {
    std::unordered_map<int, int> playerScores;

    for (const auto& [playerId, hand] : playerHands) {
        int totalValue = 0;
        int aceCount = 0;

        for (const auto& card : hand) {
            const std::string& cardValue = card[0];
            if (cardValue == "Jack" || cardValue == "Queen" || cardValue == "King") {
                totalValue += FACE_CARD_VALUE;
            } else if (cardValue == "Ace") {
                totalValue += ACE_HIGH_VALUE;
                aceCount++;
            } else {
                totalValue += std::stoi(cardValue);
            }
        }

        while (totalValue > BLACKJACK_SCORE && aceCount > 0) {
            totalValue -= 10;
            aceCount--;
        }

        playerScores[playerId] = totalValue;
    }

    return playerScores;
}

void Auxiliary::calculateAndPrintScores(int userPlayerNumber, int dealerPlayerNumber) const {
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

void Auxiliary::printAllHands(int userPlayerNumber, int dealerPlayerNumber) const {
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

int Auxiliary::restrictedRandom(int lower, int upper) {
    if (lower > upper) {
        throw std::invalid_argument("Lower bound must not exceed upper bound.");
    }
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(lower, upper);
    return dist(gen);
}
