/*  Village Card Test
Should: Draw 1 additional card to players hand
        Give player 2 additional actions
        Discard itself from hand
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEST_NAME "VILLAGE CARD"
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
    state.hand[0][0] = village;

    // For Village we only care about number of cards in hand, deck, actions and discarded
    assertTrue(state.handCount[0] == 5, "PRE: Hand count");
    assertTrue(state.deckCount[0] == 5, "PRE: Deck count");
    assertTrue(state.numActions == 1, "PRE: Action count");
    assertTrue(state.discardCount[0] == 0, "PRE: Discard count");

    // Test the Village card
    cardEffect(village, -1, -1, -1, &state, 0, 0);

    if (debug) {
        printf("Hand count: %d\n", state.handCount[0]);
        printf("Deck count %d\n", state.deckCount[0]);
        printf("Played card count: %d\n", state.playedCardCount);
        printf("Action count: %d\n", state.numActions);
    }

    // POST
    // Check post-conditions in hand (5 in hand, minus Village card, plus 1 drawn)
    assertTrue(state.handCount[0] == 5, "Player draws one additional card");
    // Check deck, discard, actions (+2), and that the Village card was played
    assertTrue(state.deckCount[0] == 4, "Deck size decreased for one drawn card");
    assertTrue(state.playedCards[0] == village, "Village card played");
    assertTrue(state.playedCardCount == 1, "Only one card played");
    assertTrue(state.numActions == 3, "Player gets two additional actions");

    if (!ERROR_STATUS) {
        printf("%s TESTS SUCCESSFULLY COMPLETED\n", TEST_NAME);
    }
    return 0;
}