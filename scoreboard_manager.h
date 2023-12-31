#pragma once
#include "game_definitions.h"

void printTop10(Player *players, short playersCount);
void printLeaderboard(Player *players, short playersCount);
void leaderboard(void (*whatToPrint)(Player *, short));
void addPlayerToScoreboard(Player *player);
Player findPlayer(char *playerName);