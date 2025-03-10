#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <iostream>
#include <stdexcept>

class inputErrors {
public:
    bool playerAmountError(int playerAmount) {
        if (playerAmount >= 2 && playerAmount <= 7) {
            return true; // Valid input
        } else {
            std::cout << "Ensure that the number of players is between 2 and 7." << std::endl;
            return false; // Invalid input
        }
    }
};

#endif