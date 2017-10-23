/*  numHandCards() Function Test
    Should: Return the correct number of cards in current player's hand
*/
#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#define TEST_NAME "NUM HANDS FUNCTION"
int ERROR_STATUS = 0;

void assertTrue(int testValue, char* errorMessage) {
    if (testValue != 1) {
        printf("%s %s test has failed :(\n", TEST_NAME, errorMessage);
        ERROR_STATUS = 1;
    }
    return;
}

int main (int argc, char** argv) {
    struct gameState state;
    int numPlayers, randomSeed, i;
    int kingdomCards[10] = {adventurer, smithy, great_hall, village, council_room,
                            feast, gardens, mine, minion, outpost};
    numPlayers = 4;
    randomSeed = rand() % 100;
    // Initialize game and pre-conditions
    initializeGame(numPlayers, kingdomCards, randomSeed, &state);

    for (i = 0; i < numPlayers; i++) {
        state.whoseTurn = i;
        randomSeed = rand() % 5;
        state.handCount[i] = randomSeed;
        assertTrue(numHandCards(&state) == randomSeed, "Hand count for current player");
    }

    if (!ERROR_STATUS) {
        printf("%s TESTS SUCCESSFULLY COMPLETED\n", TEST_NAME);
    }
    return 0;
}