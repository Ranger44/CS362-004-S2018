#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void testGreatHall() 
{
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int player=0;
	struct gameState state, test;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &state);

	printf("\n-- Card test 3: Testing GREAT HALL -- \n");

	// copy the game state to a test case
	memcpy(&test, &state, sizeof(struct gameState));
	cardEffect(great_hall, choice1, choice2, choice3, &state, handpos, &bonus);

	player = whoseTurn(&test);
		
	//Check players hand
	printf("  Expected result: hand count correct\n");
	if(state.hand[player][test.handCount[player]-1] != -1)
		printf("   - PASSED -\n");
	else
		printf("   - FAILED -\n");

	
	//Check if player played Great Hall card
	printf("  Expected result: player played Great Hall card\n");
	if(test.playedCardCount + 1 == state.playedCardCount)
		printf("   - PASSED -\n");
	else
		printf("   - FAILED -\n");
		
		
	//Discard Test: Check if card was discarded
	printf("  Expected result: Great Hall card discarded\n");
	if(test.discardCount[player] == state.discardCount[player])
		printf("   - PASSED -\n");
	else
		printf("   - FAILED -\n");
	
	
	//Action Test: Check if the +1 Action was added
	printf("  Expected result: One action added\n");
	if(test.numActions + 1 == state.numActions)
		printf("   - PASSED -\n");
	else
		printf("   - FAILED -\n");

	return;
}
	
int main() {
	testGreatHall();
	return 0;
}

/*
cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
...
case great_hall:
	//+1 Card
	drawCard(currentPlayer, state);
		
	//+1 Actions
	state->numActions++;
		
	//discard card from hand
	discardCard(handPos, currentPlayer, state, 0);
	return 0;
*/