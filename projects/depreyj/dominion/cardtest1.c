/*  Adventurer Card Test
Should: Reveal cards from players hand until 2 treasure cards drawn
        Put those treasure cards in players hand
        Discard non-treasure cards that were revealed
        Discard played cards (and itself) from hand
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEST_NAME "ADVENTURER CARD"
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
    state.hand[0][0] = adventurer;
    assertTrue(state.handCount[0] == 5, "PRE: Hand count");
    assertTrue(state.deckCount[0] == 5, "PRE: Deck count");
    assertTrue(state.discardCount[0] == 0, "PRE: Discard count");

    // Test the adventurer card
    cardEffect(adventurer, -1, -1, -1, &state, 0, 0);


    if (debug) {
        printf("Hand count: %d\n", state.handCount[0]);
        printf("Deck count %d\n", state.deckCount[0]);
        printf("Played card count: %d\n", state.playedCardCount);
        printf("Action count: %d\n", state.numActions);
    }
    // POST
    // Check that hand count increased by 1 (5 minus 1 Adventurer card plus 2 treasure)
    assertTrue(state.handCount[0] == 6, "Player draws two treasures");
    // Check that deck has been decremented by at least 2 for the treasure cards (and others) drawn
    assertTrue(state.deckCount[0] <= 3, "Deck size decreased by at least two treasures");
    // Check that newly treasure cards are in players hand in the top two positions
    assertTrue((state.hand[0][4] == gold ||
                state.hand[0][4] == silver ||
                state.hand[0][4] == copper) &&
                (state.hand[0][3] == gold ||
                state.hand[0][3] == silver ||
                state.hand[0][3] == copper), "Cards added to hand are treasure cards");
    // Check that only non-treasure cards were discarded
    if (state.discardCount > 0) {
        int i;
        for (i = 0; i < state.discardCount[0]; ++i) {
            assertTrue((state.discard[0][i] != gold ||
                        state.discard[0][i] != silver ||
                        state.discard[0][i] != copper), "Only non-treasure cards discarded");
        }
    }
    assertTrue(state.playedCards[0] == adventurer, "Adventurer card played");
    assertTrue(state.playedCardCount == 1, "One card played");

    if (!ERROR_STATUS) {
        printf("%s TESTS SUCCESSFULLY COMPLETED\n", TEST_NAME);
    }
    return 0;
}