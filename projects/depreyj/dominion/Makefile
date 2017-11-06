CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

randomtestcard1: dominion.o randomtestcard1.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o randomtestcard1.o rngs.o -o randomtestcard1 -lm -g

randomtestcard2: dominion.o randomtestcard2.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o randomtestcard2.o rngs.o -o randomtestcard2 -lm -g

randomtestadventurer: dominion.o randomtestadventurer.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o randomtestadventurer.o rngs.o -o randomtestadventurer -lm -g

test1: randomtestcard1 dominion.o
	./randomtestcard1 >> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

test2: randomtestcard2 dominion.o
	./randomtestcard2 >> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

testadventurer: randomtestadventurer dominion.o
	./randomtestadventurer >> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe randomtestcard1 randomtestcard2 randomtestadventurer  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe