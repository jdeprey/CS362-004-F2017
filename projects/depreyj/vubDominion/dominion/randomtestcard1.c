// Random test for smithy card
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define TEST_NAME "SMITHY CARD"
int ERROR_STATUS = 0;
int NUM_TESTS = 250;
int MAX_ACTIONS = 10;
// MAX_HAND = 10 (defined in dominion.h)
// MAX_DECK (defined in dominion.h)

int main (int argc, char** argv) {
    struct gameState *state;
    struct gameState *original;
    int numPlayers, randomSeed, result, currentPlayer, i;
    int failCount = 0;

    int kingdomCards[10] = {adventurer, smithy, great_hall, village, council_room,
                            feast, gardens, mine, minion, outpost};
    srand(time(NULL));
    // Main Testing Loop
    for (i = 0; i < NUM_TESTS; i++) {
        // printf("Random %s test: Round %d\n", TEST_NAME, i);
        // Seed must be positive
        randomSeed = rand() % 100 + 1;
        // Number of players from 2 to 4
        numPlayers = rand() % 3 + 2;
        state = malloc(sizeof(struct gameState));
        original = malloc(sizeof(struct gameState));
        // Initialize game and randomize pre-conditions
        initializeGame(numPlayers, kingdomCards, randomSeed, state);
        // Randomize player and state
        currentPlayer = rand() % numPlayers;
        state->whoseTurn = currentPlayer;
        state->deckCount[currentPlayer] = rand() % MAX_DECK;
        state->handCount[currentPlayer] = rand() % MAX_HAND;
        state->discardCount[currentPlayer] = rand() % MAX_DECK;
        state->hand[currentPlayer][0] = smithy;
        state->numActions = rand() % MAX_ACTIONS;
        // Compare state before and after card played
        memcpy(original, state, sizeof(struct gameState));

        // Test the smithy card
        result = cardEffect(smithy, -1, -1, -1, state, 0, 0);
        if (result != 0) {
            failCount++;
        }
        // Check that hand count increased by 1 (1 discard, 2 drawn)
        if (state->handCount[currentPlayer] != original->handCount[currentPlayer] + 2) {
            failCount++;
        }
        // Check that deck has been decremented by 3 for the cards drawn
        if (state->deckCount[currentPlayer] == original->deckCount[currentPlayer] - 3) {
            failCount++;
        }
        free(state);
        free(original);
    }

    printf("%s Tests complete with %d errors found.\n", TEST_NAME, failCount);
    return 0;
}