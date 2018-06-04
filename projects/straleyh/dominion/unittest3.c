#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


void testDiscardCard() {
	printf("\n-- Unittest 3: Testing discardCard() -- \n");
	
	int i = 0;
	int j, l, r;
	struct gameState testGame;
	struct gameState testGame2;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, 
		smithy, village, baron, great_hall};
	int seed = 1000;
	int numPlayers = 3;	
    int counter;   

    for (i = 1; i <= numPlayers; i++) {
        for (j = 1; j <= 5; j++) {            
            memset(&testGame, 23, sizeof(struct gameState));   
            r = initializeGame(numPlayers, k, seed, &testGame);
            assert(r != -1); 
			
			memset(&testGame2, 23, sizeof(struct gameState));
            r = initializeGame(numPlayers, k, seed, &testGame2);
            assert(r != -1); 
			
            for (l = 0; l < j; l++) {
                testGame.handCount[i] = j;                 // set the number of cards on hand
                memcpy(testGame.hand[i], k, sizeof(int) * j); // set all the cards to non-treasure card

                //printf("---------Test if the card is trashed for player %d, card position %d ------------\n",i, l);
                
                discardCard(l, i, &testGame, 1);
                //printf("  Expected result : %d == -1\n", testGame.hand[i][j - 1]);
                assert(testGame.hand[i][j - 1] == -1);
                //printf("   - PASSED -\n");
                //printf("  Expected result : %d == 0\n", testGame.playedCardCount);
                assert(testGame.playedCardCount == 0);
                //printf("   - PASSED -\n");
                //printf("  Expected result : %d == %d\n", testGame.handCount[i], j - 1);
                assert(testGame.handCount[i] == j - 1);
                //printf("   - PASSED -\n");

                testGame2.handCount[i] = j;                 // set the number of cards on hand
                memcpy(testGame2.hand[i], k, sizeof(int) * j); // set all the cards to non-treasure card
                counter = testGame2.playedCardCount;
                counter++;

                //printf("---------Test if the card is NOT trashed for player %d, card position %d ---------\n",i, j);            
                discardCard(l, i, &testGame2, 0);
               // printf("  Expected result :  %d == -1\n", testGame2.hand[i][j - 1]);
                assert(testGame2.hand[i][j - 1] == -1);
               // printf("   - PASSED -\n");
				//printf("  Expected result : %d == %d\n", testGame2.playedCardCount, counter);
                assert(testGame2.playedCardCount == counter);
               // printf("   - PASSED -\n");
				//printf("  Expected result : %d == %d\n", testGame2.handCount[i], j - 1);
                assert(testGame2.handCount[i] == j - 1 );
                //printf("   - PASSED -\n");
            }
        }
    }

    printf(" ALL TESTS PASSED\n");

    return;
}

int main() {
	testDiscardCard();
	return 0;
}

/*
int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
{
	
  //if card is not trashed, added to Played pile 
  if (trashFlag < 1)
    {
      //add card to played pile
      state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos]; 
      state->playedCardCount++;
    }
	
  //set played card to -1
  state->hand[currentPlayer][handPos] = -1;
	
  //remove card from player's hand
  if ( handPos == (state->handCount[currentPlayer] - 1) ) 	//last card in hand array is played
    {
      //reduce number of cards in hand
      state->handCount[currentPlayer]--;
    }
  else if ( state->handCount[currentPlayer] == 1 ) //only one card in hand
    {
      //reduce number of cards in hand
      state->handCount[currentPlayer]--;
    }
  else 	
    {
      //replace discarded card with last card in hand
      state->hand[currentPlayer][handPos] = state->hand[currentPlayer][ (state->handCount[currentPlayer] - 1)];
      //set last card to -1
      state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
      //reduce number of cards in hand
      state->handCount[currentPlayer]--;
    }
	
  return 0;
}
*/