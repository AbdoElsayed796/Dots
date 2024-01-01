#pragma once
#include "game_definitions.h"

void printTop10(Player *players, short playersCount);
void printLeaderboard(Player *players, short playersCount);
void leaderboard(void (*whatToPrint)(Player *, short));
Player findPlayer(char *playerName);
void updatePlayerScore(Player *player, SmallNumber playerGameScore);