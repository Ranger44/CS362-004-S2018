 #include "dominion.h"
 #include "dominion_helpers.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include "rngs.h"
  
void testIsGameOver() {
	printf("Unittest 1: Testing isGameOver()\n");
	struct gameState testGame;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, 
		smithy, village, baron, great_hall};
	int randomSeed = rand() % 10;
	int testResult = 0;
	printf("Random seed: %d\n", randomSeed);
	testResult = initializeGame(2, k, randomSeed, &testGame);
	
	if(testResult != 0) {
		printf("Initialization failed, unable to test shuffle");
	}
	
	for(int i = 25; i >= 0; i--) {
		testGame.supplyCount[i] = i;
		result = isGameOver(&testGame);
		if((i != 0 && result == 1) || (i == 0 && result != 0)) {
			printf("Failed\n");
			return;
		}
	}
	
	printf("Passed\n");
	return;
}

int main() {
	testIsGameOver();
return 0;
}	