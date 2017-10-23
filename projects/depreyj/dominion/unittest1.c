/*  getCost Function Test
    Should: Return the correct cost for desired card
*/
#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#define TEST_NAME "GET COST FUNCTION"
int ERROR_STATUS = 0;

void assertTrue(int testValue, char* errorMessage) {
    if (testValue != 1) {
        printf("%s %s test has failed :(\n", TEST_NAME, errorMessage);
        ERROR_STATUS = 1;
    }
    return;
}

int main (int argc, char** argv) {

    // Correct card costs
    int curse_true_cost = 0;
    int estate_true_cost = 2;
    int duchy_true_cost = 5;
    int province_true_cost = 8;
    int copper_true_cost = 0;
    int silver_true_cost = 3;
    int gold_true_cost = 6;
    int adventurer_true_cost = 6;
    int council_room_true_cost = 5;
    int feast_true_cost = 4;
    int gardens_true_cost = 4;
    int mine_true_cost = 5;
    int remodel_true_cost = 4;
    int smithy_true_cost = 4;
    int village_true_cost = 3;
    int baron_true_cost = 4;
    int great_hall_true_cost = 3;
    int minion_true_cost = 5;
    int steward_true_cost = 3;
    int tribute_true_cost = 5;
    int ambassador_true_cost = 3;
    int cutpurse_true_cost = 4;
    int embargo_true_cost = 2;
    int outpost_true_cost = 5;
    int salvager_true_cost = 4;
    int sea_hag_true_cost = 4;
    int treasure_map_true_cost = 4;
    // Invalid input, getCost should return -1
    int invalid_input = -10;

    assertTrue(getCost(curse) == curse_true_cost, "curse cost");
    assertTrue(getCost(estate) == estate_true_cost, "estate cost");
    assertTrue(getCost(duchy) == duchy_true_cost, "duchy cost");
    assertTrue(getCost(province) == province_true_cost, "province cost");
    assertTrue(getCost(copper) == copper_true_cost, "copper cost");
    assertTrue(getCost(silver) == silver_true_cost, "silver cost");
    assertTrue(getCost(gold) == gold_true_cost, "gold cost");
    assertTrue(getCost(adventurer) == adventurer_true_cost, "adventurer cost");
    assertTrue(getCost(council_room) == council_room_true_cost, "council_room cost");
    assertTrue(getCost(feast) == feast_true_cost, "feast cost");
    assertTrue(getCost(gardens) == gardens_true_cost, "gardens cost");
    assertTrue(getCost(mine) == mine_true_cost, "mine cost");
    assertTrue(getCost(remodel) == remodel_true_cost, "remodel cost");
    assertTrue(getCost(smithy) == smithy_true_cost, "smithy cost");
    assertTrue(getCost(village) == village_true_cost, "village cost");
    assertTrue(getCost(baron) == baron_true_cost, "baron cost");
    assertTrue(getCost(great_hall) == great_hall_true_cost, "great_hall cost");
    assertTrue(getCost(minion) == minion_true_cost, "minion cost");
    assertTrue(getCost(steward) == steward_true_cost, "steward cost");
    assertTrue(getCost(tribute) == tribute_true_cost, "tribute cost");
    assertTrue(getCost(ambassador) == ambassador_true_cost, "ambassador cost");
    assertTrue(getCost(cutpurse) == cutpurse_true_cost, "cutpurse cost");
    assertTrue(getCost(embargo) == embargo_true_cost, "embargo cost");
    assertTrue(getCost(outpost) == outpost_true_cost, "outpost cost");
    assertTrue(getCost(salvager) == salvager_true_cost, "salvager cost");
    assertTrue(getCost(sea_hag) == sea_hag_true_cost, "sea_hag cost");
    assertTrue(getCost(treasure_map) == treasure_map_true_cost, "treasure_map cost");
    assertTrue(getCost(invalid_input) == -1, "Invalid input");

    if (!ERROR_STATUS) {
        printf("%s TESTS SUCCESSFULLY COMPLETED\n", TEST_NAME);
    }
    return 0;
}