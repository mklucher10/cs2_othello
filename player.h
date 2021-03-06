#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Player {
	
private:
	Board *board;
	Side side;
	
	Move *doHeuristic(Board *newboard, Side nextside);
	Move *doMiniMax2(Move *opponentsMove, int msLeft);

public:
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
