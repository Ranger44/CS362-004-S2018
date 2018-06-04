
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void testAdventurerCard() 
{
    int i;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int player=0;
	struct gameState post, pre;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int count1 = 0;
	int count2 = 0;

	// initialize a game post and player cards
	initializeGame(numPlayers, k, seed, &post);

	printf("\n-- Card test 1: Testing ADVENTURER -- \n");

	// copy the game post to a test case
	memcpy(&pre, &post, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &post, handpos, &bonus);

	player = whoseTurn(&pre);

	//Deck Count
	printf("  Expected result: deck count correct\n");
	if(pre.deckCount[player]-1 == post.deckCount[player])
		printf("   - PASSED -\n");
	else
		printf("   - FAILED -\n");
	
	
	//Check the player hands count
	printf("  Expected result: hand count correct\n");
	if(pre.handCount[player]-1 == post.handCount[player])
		printf("   - PASSED -\n");
	else
		printf("   - FAILED -\n");
	
	
	//Check players hand
	printf("  Expected result: Adventurer card added to players hand\n");
	if(post.hand[player][pre.handCount[player]] != -1)
		printf("   - PASSED -\n");
	else
		printf("   - FAILED -\n");

	
	//Check if player played a card
	printf("  Expected result: Adventurer card played\n");
	if(pre.playedCardCount+2 == post.playedCardCount)
		printf("   - PASSED -\n");
	else
		printf("   - FAILED -\n");
	
	
	//Count Adventurer cards in hand
	for (i = 0; i < post.handCount[0]; i++){
        if(post.hand[0][i] == adventurer)
			count1++;
	}		
	for (i = 0; i < pre.handCount[0]; i++){
        if(pre.hand[0][i] == adventurer)
			count2++;
	}
	printf("  Expected result: Adventurer card count matches in pre and post\n");	
	if(count1 == count2 - 1)
		printf("   - PASSED -\n");
	else
		printf("   - FAILED -\n");
	
	
	//Discard Test: Check if card was discarded
	printf("  Expected result: Adventurer card discarded\n");
	if(pre.discardCount[player] == post.discardCount[player])
		printf("   - PASSED -\n");
	else
		printf("   - FAILED -\n");
	
	
	//Action Test: Check if the +1 Action was added
	printf("  Expected result: Two actions added\n");
	if(pre.numActions + 2 == post.numActions)
		printf("   - PASSED -\n");
	else
		printf("   - FAILED -\n");
	
	return;
}

int main() {
	testAdventurerCard();
	return 0;
}

/*
cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)

int adventurerRefactor(int drawntreasure, struct gameState *state, int currentPlayer, int cardDrawn, int temphand, int *z)
{
	while(drawntreasure<2){
	if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
	  shuffle(currentPlayer, state);
	}
	drawCard(currentPlayer, state);
	cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
	if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
	  drawntreasure++;
	else{
	  temphand[z]=cardDrawn;
	  state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
	  z=0;
	}
      }
      while(z-1>=0){
	state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
	z=z-1;
      }
      return 0;
}
*/