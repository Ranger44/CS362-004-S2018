#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void testUpdateCoins() {
	printf("\n-- Unittest 2: Testing updateCoins() -- \n");
	
	int i = 0;
	int j, l, r;
	struct gameState testGame;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, 
		smithy, village, baron, great_hall};
	int seed = 1000;
	int numPlayers = 3;
    int bonus = 10;
	int expected = 0;

	
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++) {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    for (i = 1; i <= numPlayers; i++) {
        for (j = 1; j <= 5; j++) {
            for (l = 0; l <= bonus; l++) {
                memset(&testGame, 23, sizeof(struct gameState));   
                r = initializeGame(numPlayers, k, seed, &testGame); 
                assert(r != -1); 
				//test for zero treasure cards
                testGame.handCount[i] = j;                 // set the number of k on hand
                memcpy(testGame.hand[i], k, sizeof(int) * j); // set all the cards to non-treasure card
                updateCoins(i, &testGame, l);
				expected = l;
                //printf("   Expected result: %d\n", expected);
				assert(testGame.coins == expected);
				//printf("   - PASSED - \n");
				//tests for > zero treasure cards
				//test all copper coins
                memcpy(testGame.hand[i], coppers, sizeof(int) * j);
                updateCoins(i, &testGame, l);
				expected = j * 1 + l;
               // printf("   Expected result: %d\n",  expected);
                assert(testGame.coins == expected);
				//printf("   - PASSED - \n");
				//test all silver coins
                memcpy(testGame.hand[i], silvers, sizeof(int) * j);
                updateCoins(i, &testGame, l);
				expected = j * 2 + l;
                //printf("   Expected result: %d\n", expected);
                assert(testGame.coins == expected); 
				//printf("   - PASSED - \n");
				//test all gold coins
                memcpy(testGame.hand[i], golds, sizeof(int) * j);
                updateCoins(i, &testGame, l);
				expected = j * 3 + l;
                //printf("   Expected result: %d\n", expected);
                assert(testGame.coins == expected);
				//printf("   - PASSED - \n");
            }
        }
    }

    printf(" ALL TESTS PASSED\n");

    return;
}

int main() {
	testUpdateCoins();
	return 0;
}

/*
int updateCoins(int player, struct gameState *state, int bonus)
{
  int i;
	
  //reset coin count
  state->coins = 0;

  //add coins for each Treasure card in player's hand
  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == copper)
	{
	  state->coins += 1;
	}
      else if (state->hand[player][i] == silver)
	{
	  state->coins += 2;
	}
      else if (state->hand[player][i] == gold)
	{
	  state->coins += 3;
	}	
    }	

  //add bonus
  state->coins += bonus;

  return 0;
}
*/