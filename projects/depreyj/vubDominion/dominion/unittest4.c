/*  isGameOver() Function Test
    Should: Check number of provinces or if three supply piles are empty to
            determine if game is over
            Indicate if game is over or not
*/
#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#define TEST_NAME "IS GAME OVER FUNCTION"
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
    int i;

    // Fill supply piles (up to treasure_map, the final enum 26)
    for (i = 0; i < 27; i++) {
        state.supplyCount[i] = 10;
    }
    assertTrue(isGameOver(&state) == 0, "All supply piles non-empty");

    // When Province supply is 0 game should be over
    state.supplyCount[province] = 0;
    assertTrue(isGameOver(&state) == 1, "Province supply = 0");

    // When Province supply > 0 game continues
    state.supplyCount[province] = 10;
    assertTrue(isGameOver(&state) == 0, "Province supply > 0");

    // Check when three first supply piles are empty
    for (i = 0; i < 3; i++) {
        state.supplyCount[i] = 0;
    }
    assertTrue(isGameOver(&state) == 1, "Three first supply piles empty");
    // Refill supply piles
    for (i = 0; i < 3; i++) {
        state.supplyCount[i] = 1;
    }

    // Check when three middle supply piles are empty
    for (i = 10; i < 13; i++) {
        state.supplyCount[i] = 0;
    }
    assertTrue(isGameOver(&state) == 1, "Three middle supply piles empty");
    // Refill supply piles
    for (i = 10; i < 13; i++) {
        state.supplyCount[i] = 1;
    }

    // Check when three various supply piles are empty
    for (i = 24; i < 27; i++) {
        state.supplyCount[i] = 0;
    }
    assertTrue(isGameOver(&state) == 1, "Three final supply piles empty");
    // Refill supply piles
    for (i = 24; i < 27; i++) {
        state.supplyCount[i] = 1;
    }

    if (!ERROR_STATUS) {
        printf("%s TESTS SUCCESSFULLY COMPLETED\n", TEST_NAME);
    }
    return 0;
}