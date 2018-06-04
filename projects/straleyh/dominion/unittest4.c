#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
	printf("\n-- Unittest 4: Testing getCost() -- \n");
    int i = 0;
	int j, r, l;
	struct gameState testGame;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, 
		smithy, village, baron, great_hall};
	int seed = 1000;
	int numPlayers = 3;
    int cardCosts[10] = {6, 5, 4, 4, 5, 4, 4, 3, 4, 3};

    for (i = 1; i <= numPlayers; i++) {
        for (j = 0; j < 10; j++) {            
            memset(&testGame, 23, sizeof(struct gameState));   // clear the game state
            r = initializeGame(numPlayers, k, seed, &testGame); // initialize a new game
            assert(r != -1); //check if initializeGame success
            testGame.handCount[i] = j;                 // set the number of cards on hand
            memcpy(testGame.hand[i], k, sizeof(int) * j); // set all the cards to non-treasure card
           
            l = getCost(k[j]);
			printf("  Expected result : %d == %d\n", l, cardCosts[j]);
            assert(l == cardCosts[j]);
            printf("   - PASSED -\n");
        }
    }

    printf(" ALL TESTS PASSED\n");

    return 0;
}

/*
int getCost(int cardNumber)
{
  switch( cardNumber ) 
    {
    case curse:
      return 0;
    case estate:
      return 2;
    case duchy:
      return 5;
    case province:
      return 8;
    case copper:
      return 0;
    case silver:
      return 3;
    case gold:
      return 6;
    case adventurer:
      return 6;
    case council_room:
      return 5;
    case feast:
      return 4;
    case gardens:
      return 4;
    case mine:
      return 5;
    case remodel:
      return 4;
    case smithy:
      return 4;
    case village:
      return 3;
    case baron:
      return 4;
    case great_hall:
      return 3;
    case minion:
      return 5;
    case steward:
      return 3;
    case tribute:
      return 5;
    case ambassador:
      return 3;
    case cutpurse:
      return 4;
    case embargo: 
      return 2;
    case outpost:
      return 5;
    case salvager:
      return 4;
    case sea_hag:
      return 4;
    case treasure_map:
      return 4;
    }
	
  return -1;
}
*/