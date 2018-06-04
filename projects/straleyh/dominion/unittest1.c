 #include "dominion.h"
 #include "dominion_helpers.h"
 #include <string.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <assert.h>
 #include "rngs.h"
  
void testIsGameOver() {
	printf("\n-- Unittest 1: Testing isGameOver() -- \n");
	int i = 0;
	int j, r;
	struct gameState testGame;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, 
		smithy, village, baron, great_hall};
	int seed = 1000;
	int numPlayers = 3;
	
    for (i = 0; i <= 3; i++) {
        memset(&testGame, 23, sizeof(struct gameState));   
        r = initializeGame(numPlayers, k, seed, &testGame);
        assert(r != -1); 
        memcpy(testGame.hand[i], k, sizeof(int) * 10); 
        
        testGame.supplyCount[province] = i;
        testGame.supplyCount[i] = 0; 

        if( i == 0 ){
            printf("  Expected result : game over\n");
            r = 1;
        }
        else if( i == 3 ){
            printf("  Expected result : game over\n");
            r = 1;
        }
        else{
            printf("  Expected result : game not over\n");
            r = 0;
        }
        j = isGameOver(&testGame);
        assert(j == r);
        printf("   - PASSED -\n");
    }
	printf(" ALL TESTS PASSED\n");

	return;
}

int main() {
	testIsGameOver();
return 0;
}	
