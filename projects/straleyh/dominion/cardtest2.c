#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void testVillageCard(){
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int player=0;
	struct gameState state, test;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &state);

	printf("\n-- Card test 2: Testing VILLAGE -- \n");

	// copy the game state to a test case
	memcpy(&test, &state, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &state, handpos, &bonus);

	player = whoseTurn(&test);
	
	//Check players hand
	printf("  Expected result: Village card added to hand\n");
	if(state.hand[player][test.handCount[player]-1] != -1)
		printf("   - PASSED -\n");
	else
		printf("   - FAILED -\n");

	
	//Check if player played Village card
	printf("  Expected result: player played Village card\n");
	if(test.playedCardCount + 1 == state.playedCardCount)
		printf("   - PASSED -\n");
	else
		printf("   - FAILED -\n");
		
		
	//Discard Test: Check if card was discarded
	printf("  Expected result: Village card discarded\n");
	if(test.discardCount[player] == state.discardCount[player])
		printf("   - PASSED -\n");
	else
		printf("   - FAILED -\n");
	
	
	//Action Test: Check if the +1 Action was added
	printf("  Expected result: Two actions added\n");
	if(test.numActions + 2 == state.numActions)
		printf("   - PASSED -\n");
	else
		printf("   - FAILED -\n");
	
	return;
}

int main() {
	testVillageCard();
	return 0;
}

//cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)

/*Layout of Village in Dominion
    case village:
      //+1 Card
      drawCard(currentPlayer, state);
			
      //+2 Actions
      state->numActions = state->numActions + 2;
			
      //discard played card from hand
      discardCard(handPos, currentPlayer, state, 0);
      return 0;
*/