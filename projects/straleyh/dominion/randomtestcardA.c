#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include<time.h>

int main() {
	srand(time(NULL));

    int i, j, m, a;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    //int seed = 1000;
    //int numPlayers = 2;
    int player=0;
	struct gameState state, test;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
	int count1 = 0;
	int count2 = 0;
	
	for(a = 0; a < 50; a++) {
		int numPlayers = (rand() % 50);
		int seed = (rand() % 5000);

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &state);

		printf("\n----------Testing Adventurer Card Pass %d/50----------\n", a+1);

		// copy the game state to a test case
		memcpy(&test, &state, sizeof(struct gameState));
		cardEffect(adventurer, choice1, choice2, choice3, &state, handpos, &bonus);

		player = whoseTurn(&test);
		
		
		//Deck Count
		if(test.deckCount[player]-1 == state.deckCount[player])
			printf("Passed where deck count is correct\n");
		else
			printf("Failed where deck count is not correct\n");
		
		
		//Check the player hands count
		if(test.handCount[player]-1 == state.handCount[player])
			printf("Passed where hand count is correct\n");
		else
			printf("Failed where hand count is not correct\n");
		
		
		//Check players hand
		if(state.hand[player][test.handCount[player]] != -1)
			printf("Passed where Adventurer card was added to the players hand\n");
		else
			printf("Failed where Adventurer card was not added to the players hand\n");

		
		//Check if player played a card
		if(test.playedCardCount+2 == state.playedCardCount)
			printf("Passed where player played Adventurer card\n");
		else
			printf("Failed where player did not play Adventurer card\n");
		
		
		//Count Adventurer cards in hand
		for (i = 0; i < state.handCount[0]; i++)
			if(state.hand[0][i] = adventurer) {
				count1++;
			}
		for (i = 0; i < test.handCount[0]; i++)
			if(test.hand[0][i] = adventurer) {
				count2++;
			}
		if(count1 == count2-1)
			printf("Passed where there is no variance in Adventurer cards\n");
		else
			printf("Failed where there is a variance in Adventurer cards\n");
		
		
		//Discard Test: Check if card was discarded
		if(test.discardCount[player] == state.discardCount[player])
			printf("Passed where the Adventurer was discarded\n");	
		else
			printf("Failed where the Adventurer was not discarded.\n");
		
		
		//Action Test: Check if the +1 Action was added
		if(test.numActions+2 == state.numActions)
			printf("Passed where two extra action was added\n");
		else
			printf("Failed where two extra action was not added\n");
	
	}
	printf("----------End Testing Adventurer Card----------\n");
	
	return 0;
}