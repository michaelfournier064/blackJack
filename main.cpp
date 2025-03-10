#include "helperFunctions/assistingFunctions.h"
#include "majorComponents/gameStart.h"
#include "majorComponents/cardDrawing.h"

#include <iostream>

int main() {
    std::cout << "=====================================\n";
    std::cout << "        Welcome to Blackjack!        \n";
    std::cout << "=====================================\n\n";

    Auxiliary auxiliary;
    GameStart newGame(auxiliary);
    Card dealerCard;

    // Initialize bankrolls
    int initialBankroll = 100;
    auxiliary.initializeBankroll(1, initialBankroll); // User is player 1
    auxiliary.initializeBankroll(2, initialBankroll); // Dealer is player 2

    // Initialize the game
    int userPlayerNumber = 1;
    int dealerPlayerNumber = 2;

    bool keepPlaying = true;
    while (keepPlaying) {
        std::cout << "\n=====================================\n";
        std::cout << "           Starting a New Game       \n";
        std::cout << "=====================================\n";

        // Reset hands and scores for a new game
        auxiliary.resetPlayerHands();

        // Game initialization
        newGame.gameInitialization();
        newGame.playerAssignment();

        // Check bankroll
        if (auxiliary.getBankroll(userPlayerNumber) <= 0) {
            std::cout << "You have no money left. Game over!\n";
            break;
        }


        // Betting phase
        int userBet = newGame.placeBet(userPlayerNumber);

        // Dealing phase
        newGame.initialDealing();

        // Player's turn
        bool userTurn = true;
        while (userTurn) {
            std::cout << "\n=====================================\n";
            std::cout << "           Your Current Hand         \n";
            std::cout << "=====================================\n";
            auxiliary.printAllHands(userPlayerNumber, dealerPlayerNumber);

            std::cout << "\n-------------------------------------\n";
            if (newGame.userHitOrStand()) {
                dealerCard.generateCard();
                std::string cardValue = dealerCard.getCardValue();
                std::string cardType = dealerCard.getCardType();
                auxiliary.addCardToPlayer(userPlayerNumber, cardValue, cardType);

                std::cout << ">> You drew: " << cardValue << " of " << cardType << "\n";

                auto scores = auxiliary.calculatePlayerScores();
                if (scores[userPlayerNumber] > 21) {
                    std::cout << ">> Oh no! You busted! Your score: " << scores[userPlayerNumber] << "\n";
                    userTurn = false;
                }
            } else {
                std::cout << ">> You chose to stand.\n";
                userTurn = false;
            }
        }

        // Dealer's turn
        std::cout << "\n=====================================\n";
        std::cout << "           Dealer's Turn             \n";
        std::cout << "=====================================\n";
        dealerCard.dealerForcedDraw(dealerPlayerNumber, auxiliary);

        // Print final hands and scores
        std::cout << "\n=====================================\n";
        std::cout << "             Final Hands             \n";
        std::cout << "=====================================\n";
        auxiliary.printAllHands(userPlayerNumber, dealerPlayerNumber);

        std::cout << "\n=====================================\n";
        std::cout << "             Final Scores            \n";
        std::cout << "=====================================\n";
        auxiliary.calculateAndPrintScores(userPlayerNumber, dealerPlayerNumber);

        // Determine and announce results
        auto scores = auxiliary.calculatePlayerScores();
        int userScore = scores[userPlayerNumber];
        int dealerScore = scores[dealerPlayerNumber];

        if (userScore > 21 || (dealerScore <= 21 && dealerScore > userScore)) {
            std::cout << "\n>> You lost your bet of " << userBet << " units.\n";
            auxiliary.adjustBankroll(userPlayerNumber, -userBet);
        } else if (dealerScore > 21 || userScore > dealerScore) {
            std::cout << "\n>> You won " << userBet << " units!\n";
            auxiliary.adjustBankroll(userPlayerNumber, userBet);
        } else {
            std::cout << "\n>> It's a tie. Your bet of " << userBet << " units is returned.\n";
        }


        // Display updated bankroll
        std::cout << "\n=====================================\n";
        std::cout << "          Player Bankrolls           \n";
        std::cout << "=====================================\n";
        auxiliary.printBankrolls();

        // Ask if the user wants to play again
        keepPlaying = newGame.playAgain();

        if (!keepPlaying) {
            std::cout << "\n=====================================\n";
            std::cout << "         Thank You for Playing!      \n";
            std::cout << "=====================================\n";
        }
    }

    return 0;
}

