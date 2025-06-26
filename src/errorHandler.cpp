#include "errorHandler.h"

bool inputErrors::playerAmountError(int playerAmount) {
    if (playerAmount >= 2 && playerAmount <= 7) {
        return true;
    } else {
        std::cout << "Ensure that the number of players is between 2 and 7." << std::endl;
        return false;
    }
}
