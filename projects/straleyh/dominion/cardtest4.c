#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void testSmithyCard() 
{
    int i;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int player=0;
	struct gameState post, pre;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, 
		smithy, village, baron, great_hall};
	int stateCount = 0;
	int testCount = 0;

	// initialize a game post and player cards
	initializeGame(numPlayers, k, seed, &post);

	printf("\n-- Card test 4: Testing SMITHY -- \n");

	// copy the game post to a pre case
	memcpy(&pre, &post, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &post, handpos, &bonus);

	player = whoseTurn(&pre);
	
	
	//Check the player hands count
	printf("  Expected result: hand count = %d\n", pre.handCount[player] - 1);
	if(pre.handCount[player]-1 == post.handCount[player])
		printf("   - PASSED -\n");
	else
		printf("   - FAILED -\n");
	
	//Check players hand
	printf("  Expected result: smithy card successfully added to player's hand\n");
	if(post.hand[player][pre.handCount[player]] != -1)
		printf("   - PASSED -\n");
	else 
		printf("   - FAILED -\n");
	
	//Check if player played Smithy card
	printf("  Expected result: player played Smithy card\n");
	if(pre.playedCardCount+2 == post.playedCardCount)
		printf("   - PASSED -\n");
	else
		printf("   - FAILED -\n");
	
	//Count smithy cards in hand
	for (i = 0; i < post.handCount[0]; i++) {
        if(post.hand[0][i] == smithy)
			stateCount++;
	}
		
	for (i = 0; i < pre.handCount[0]; i++) {
        if(pre.hand[0][i] == smithy)
			testCount++;
	}
	
	printf("  Expected result: card count = %d\n", testCount - 1);
	if(stateCount == testCount - 1)
		printf("   - PASSED -\n");
	else
		printf("   - FAILED -\n");
	
	//Check if card was discarded
	printf("  Expected result: player discarded Smithy card\n");
	if(pre.discardCount[player] == post.discardCount[player])
		printf("   - PASSED -\n");	
	else
		printf("   - FAILED -\n");
	
	return;
}

int main() {
	testSmithyCard();
	return 0;
}