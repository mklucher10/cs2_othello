#include "player.h"

/* Small change to player file for git commit tutorial -mklucher */

/* hello -bllin*/
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    board = new Board();
    this->side = side;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
	delete board;
}

	
/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */

Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* Inact opponent's move */
    board->doMove(opponentsMove, (side == BLACK) ? WHITE : BLACK);
    
    /* Find best heuristic move */
    //Move *nextMove = doHeuristic(board, side);
    Move *nextMove = doMiniMax2(opponentsMove, msLeft);
    
    /* Update the board with most recent move */
	board->doMove(nextMove, side);
	
	return nextMove;

}

/* Implements 2-depth minimax tree
 */
Move *Player::doMiniMax2(Move *opponentsMove, int msLeft)
{
	Board *temp;
	Move *nextMove;
	Move *nextnextMove;
	Move *bestMove = NULL;
	int minPoints = 65;
	int points;
	
	/* See if we have legal moves */
    if(!board->hasMoves(side)) return NULL;
	
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			temp = board->copy();
			nextMove = new Move(i, j);
			if(temp->checkMove(nextMove, side))
			{
				temp->doMove(nextMove, side);
				nextnextMove = doHeuristic(temp, (side == BLACK) ? WHITE : BLACK);
				temp->doMove(nextnextMove, (side == BLACK) ? WHITE : BLACK);
				points =  temp->count((side == BLACK) ? WHITE : BLACK) - temp->count(side);
				if (points < minPoints)
				{
					minPoints = points;
					bestMove = nextMove;
				}
			}
		}
	}
	return bestMove;	
}

/* Implements heuristic algorithm on a given board */
Move *Player::doHeuristic(Board *newboard, Side nextside)
{
/* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */ 
     Board *temp;
     Move *nextMove;
     Move *bestMove = NULL;
     int maxPoints = -97;
     int points;
         
    /* See if we have legal moves */
    if(!newboard->hasMoves(nextside)) return NULL;
    
    /* Check possible moves */
    temp = newboard->copy();
    
    for(int i = 0; i < 8; i++)
    {
		for(int j = 0; j < 8; j++)
		{
			temp = newboard->copy();
			nextMove = new Move(i, j);
			if(temp->checkMove(nextMove, nextside))
			{
				temp->doMove(nextMove, nextside);
				points = temp->count(nextside) - temp->count((nextside == BLACK) ? WHITE : BLACK);
				if((i == 0 || i == 7) && (j == 0 || j == 7))
				{
					points += 3;
				}
				if(((i == 1 || i == 6) && (j == 0 || j == 7)) ||
				((i == 0 || i == 7) && (j == 1 || j == 6)) ||
				((i == 1 || i == 6) && (j == 1 || j == 6)))
				{
					points -= 3;
				}
				if (points > maxPoints)
				{
					maxPoints = points;
					bestMove = nextMove;
				}
			}
		}
	}
    return bestMove;
}
