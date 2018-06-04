CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
cardtest1: cardtest1.c dominion.o rngs.o  
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
	./cardtest1 > unittestresults.out
	
cardtest2: cardtest2.c dominion.o rngs.o  
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardtest2 > unittestresults.out
	
cardtest3: cardtest3.c dominion.o rngs.o  
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardtest3 > unittestresults.out
	
cardtest4: cardtest4.c dominion.o rngs.o  
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardtest4 > unittestresults.out

unittest1:  unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	./unittest1 > unittestresults.out
	
unittest2:  unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2 > unittestresults.out
	
unittest3:  unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3 > unittestresults.out
	
unittest4:  unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4 > unittestresults.out
	
unittest: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)
	
testBuyCard: testBuyCard.c dominion.o rngs.o
	gcc -o testBuyCard -g  testBuyCard.c dominion.o rngs.o $(CFLAGS)
	
testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.c
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.c $(CFLAGS)
	./randomtestadventurer > randomtestadventurer.out
	
randomtestcard1: randomtestcard1.c dominion.o rngs.c
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.c $(CFLAGS)
	./randomtestcard1 > randomtestcard1.out
	
randomtestcard2: randomtestcard2.c dominion.o rngs.c
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.c $(CFLAGS)
	./randomtestcard2 > randomtestcard2.out
	
randomtestcardA: randomtestcardA.c dominion.o rngs.o
	gcc -o randomtestcardA -g  randomtestcardA.c dominion.o rngs.o $(CFLAGS)
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	
runtests: testDrawCard testBuyCard unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard1 randomtestcard2 
	./testDrawCard >> testresults.out
	./testBuyCard >> testresults.out
	./unittest1 >> testresults.out
	./unittest2 >> testresults.out
	./unittest3 >> testresults.out
	./unittest4 >> testresults.out
	./cardtest1 >> testresults.out
	./cardtest2 >> testresults.out
	./cardtest3 >> testresults.out
	./cardtest4 >> testresults.out
	./randomtestcard1 >> testresults.out
	./randomtestcard2 >> testresults.out
	gcov dominion.c >> testresults.out
	cat dominion.c.gcov >> testresults.out

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
