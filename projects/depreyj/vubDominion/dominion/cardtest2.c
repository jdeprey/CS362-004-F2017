/*  Smithy Card Test
Should: Draw 3 additional cards for player
        Discard itself from hand
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEST_NAME "SMITHY CARD"
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
    int numPlayers, randomSeed;
    int kingdomCards[10] = {adventurer, smithy, great_hall, village, council_room,
                            feast, gardens, mine, minion, outpost};
    numPlayers = 2;
    randomSeed = rand() % 100;

    int debug = 0;

    // Initialize game and pre-conditions
    initializeGame(numPlayers, kingdomCards, randomSeed, &state);

    // PRE
    state.hand[0][0] = smithy;

    // For Smithy we only care about number of cards in hand, deck and discarded
    assertTrue(state.handCount[0] == 5, "PRE: Hand count");
    assertTrue(state.deckCount[0] == 5, "PRE: Deck count");
    assertTrue(state.discardCount[0] == 0, "PRE: Discard count");

    // Test the Smithy card
    cardEffect(smithy, -1, -1, -1, &state, 0, 0);

    if (debug) {
        printf("Hand count: %d\n", state.handCount[0]);
        printf("Deck count %d\n", state.deckCount[0]);
        printf("Played card count: %d\n", state.playedCardCount);
        printf("Action count: %d\n", state.numActions);
    }

    // POST
    // Check post-conditions in hand (5 cards minus 1 Smithy card plus 3 drawn)
    assertTrue(state.handCount[0] == 7, "Player draws three additional cards");
    // Check deck, discard, and that the Smithy card was played
    assertTrue(state.deckCount[0] == 2, "Deck size decreased by three drawn cards");
    assertTrue(state.playedCards[0] == smithy, "Smithy card played");
    assertTrue(state.playedCardCount == 1, "Only one card played");

    if (!ERROR_STATUS) {
        printf("%s TESTS SUCCESSFULLY COMPLETED\n", TEST_NAME);
    }
    return 0;
}