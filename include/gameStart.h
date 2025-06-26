#ifndef GAME_START_H
#define GAME_START_H

#include "cardDrawing.h"
#include "errorHandler.h"
#include "assistingFunctions.h"

#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <algorithm>

class GameStart {
private:
    Auxiliary& auxiliary;
    inputErrors playerError;
    Card cardGenerator;
    int playerAmount{};

public:
    int dealerPlayerNumber{};
    int userPlayerNumber{};

    GameStart(Auxiliary& aux);
    int placeBet(int playerId);
    bool playAgain() const;
    void gameInitialization();
    void playerAssignment();
    void initialDealing();
    bool userHitOrStand();
};

#endif
