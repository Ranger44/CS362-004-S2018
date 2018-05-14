#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int FAIL_1 = 0;
int FAIL_2 = 0;
int FAIL_3 = 0;
int FAIL_4 = 0;
int FAIL_5 = 0;

// function to check the adventurerCard
void checkAdventurerCard(int p, struct gameState *post) {
    int postTreasureCount = 0;
    int PreTreasureCount = 0;
    int tmp[MAX_HAND];
    int drawntreasure = 0;
    // game state variable to manually act on the functions actions
    struct gameState pre;
    int cardDrawn, card;
    int i, r, s, t, z;
	z = 0;
    memcpy(&pre,post,sizeof(struct gameState));

    // call adeventurerEffect using post
	r = adventurerEffect(drawntreasure, post, p);

    //simulate adventurerEffect() on pre
    while(drawntreasure < 2) {
		if (pre.deckCount[p] < 1) {//if the deck is empty we need to shuffle discard and add to deck
			s = shuffle(p, &pre);
			// check if shuffle failed
			if (s == -1 && pre.deckCount[p] >= 1) {
			  FAIL_2++;
			}
		}
		t = drawCard(p, &pre);
		// check if drawcard failed
		if (t == -1 && pre.deckCount[p] != 0) {
			FAIL_3++;
		}
		cardDrawn = pre.hand[p][pre.handCount[p] - 1];//top card of hand is most recently drawn card.
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
			drawntreasure++;
		else{
			tmp[z] = cardDrawn;
			pre.handCount[p]--; //this should just remove the top card (the most recently drawn one).
			z++;
		}
    }
    while(z - 1 >= 0) {
            pre.discard[p][pre.discardCount[p]++] = tmp[z - 1]; // discard all cards in play that have been drawn
            z = z - 1;
    }
    //increment postTreasureCount
    for (i = 0; i < post->handCount[p]; i++) {
        card = post->hand[p][i];
        if (card == copper || card == silver || card == gold) {
            postTreasureCount++;
        }
    }
    // get the PretreasureCount
    for (i = 0; i < pre.handCount[p]; i++) {
        card = pre.hand[p][i];
        if (card == copper || card == silver || card == gold) {
            PreTreasureCount++;
        }
    }
	// check if cardeffect failed
    if (r) {
        FAIL_1++;
    }
    // check if treasures match
    if (postTreasureCount != PreTreasureCount) {
      FAIL_5++;
    }
    // check if the hand and deck counts match
    if (!(post->handCount[p] == pre.handCount[p] 
		&& post->deckCount[p] == pre.deckCount[p] 
		&& post->discardCount == pre.discardCount)) {
			FAIL_4++;
    }
}

int main () {
    printf("-------------------- Testing Card: Adventurer ------------------\n");
    int numTests = 200000;
    int treasures[] = {copper,silver,gold};
    int numTreasures;
    int i, n, player;
    struct gameState G;

    int min = 1;
    srand(time(NULL));

    // randomly initialize the game state
    for (n = 0; n < numTests; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		// randomly select appropriate values
		player = floor(Random() * MAX_PLAYERS);
		G.deckCount[player] = floor(Random() * ((MAX_DECK - min) + 1) + min);
		numTreasures = floor(Random() * ((G.deckCount[player] - min) + 1) + min);

		// put treasure cards in deck
		for (i = 0; i < numTreasures; i++) {
			G.deck[player][i] = treasures[rand() % 3];
		}
		G.discardCount[player] = 0;
		G.handCount[player] = floor(Random() * ((MAX_HAND - min) + 1) + min);
		G.whoseTurn = player;

		// call the checkAdventurerCard function
		checkAdventurerCard(player, &G);
    }
    int totalFails = FAIL_1 + FAIL_3 + FAIL_2 + FAIL_4 + FAIL_5;

    if (numTests - totalFails <= 0) {
	printf("\n------------------------ RESULTS -------------------------\n");
      printf("PASSED TESTS: %d\n",0);
      printf("FAILED TESTS: %d\n",numTests);
    }
    else {
	printf("\n------------------------ RESULTS -------------------------\n");
      printf("PASSED TESTS: %d\n",numTests - totalFails);
      printf("FAILED TESTS: %d\n",totalFails);
    }

    if (totalFails == 0) {
        printf ("----------------- PASSED ALL RANDOM TESTS -----------------\n\n");
    }
    else {
        printf("\n--------------------- FAILURE REPORT ---------------------\n");
        printf("shuffle() failed: %d\n",FAIL_2);
        printf("drawCard() failed: %d\n",FAIL_3);
        printf("cardEffect() failed: %d\n",FAIL_1);
        printf("Treasure Count mismatch: %d\n",FAIL_5);
        printf("Hand/Deck mismatch: %d\n",FAIL_4);
		printf("\n----------------------------------------------------------\n");
    }
	
    return 0;
}