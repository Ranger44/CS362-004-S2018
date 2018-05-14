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

void checkVillageCard(int p, struct gameState *post) {
    int r,s,t,u,v;
    struct gameState pre;
    int bonus = 0;

	memcpy(&pre,post,sizeof(struct gameState));
	
	//call VillageEffect() on post
	r = villageEffect(p, post, 0);
	//int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
    //r = cardEffect(village,0,0,0,post,0,&bonus);

	//simulate villageEffect() on pre 
	//**draw 3 cards
    s = drawCard(p,&pre);
	//**add 2 actions
	pre.numActions = pre.numActions + 2;
	//**discard current card
    t = discardCard(0, p, &pre, 0); //formerly v

	//check for failures in the above processes
    //**drawcard
    if (s == -1 && pre.deckCount[p] != 0) {
        FAIL_3++;
    }
    //**discard
    if (!(r == 0 && t == 0)) {
        if (r) {
            FAIL_1++;
        }
        if (t) {
            FAIL_2++;
        }
    }
    //**matching decks
    if (!(post->handCount[p] == pre.handCount[p] && post->deckCount[p] == pre.deckCount[p])) {
        FAIL_4++;
    }
}

int main () {
    printf("-------------------- Testing Card: Village ------------------\n");

    int numTests = 10000;
    int i, n, player;
    struct gameState G;
    srand(time(NULL));

    // randomly initialized the game state
    for (n = 0; n < numTests; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        // randomly select appropriate values
        player = floor(Random() * MAX_PLAYERS);
        G.deckCount[player] = floor(Random() * MAX_DECK);
        G.discardCount[player] = floor(Random() * MAX_DECK);
        G.handCount[player] = floor(Random() * MAX_HAND);
        G.playedCardCount = floor(Random() * (MAX_DECK-1));
        G.whoseTurn = player;
        // call the check function
        checkVillageCard(player,&G);
    }
    int totalFails = FAIL_1 + FAIL_2 +
                        FAIL_3 + FAIL_4;
	printf("\n------------------------ RESULTS -------------------------\n");
    printf("PASSED TESTS: %d\n",numTests - totalFails);
    printf("FAILED TESTS: %d\n",totalFails);

    if (totalFails == 0) {
        printf ("----------------- PASSED ALL RANDOM TESTS -----------------\n\n");
    }
    else {
        printf("\n--------------------- FAILURE REPORT ---------------------\n");
        printf("cardEffect() failed: %d\n",FAIL_1);
        printf("discardCard() failed: %d\n",FAIL_2);
		printf("drawCard() failed: %d\n",FAIL_3);
        printf("Hand/Deck mismatch: %d\n",FAIL_4);
		printf("\n----------------------------------------------------------\n");
    }
    return 0;
}
