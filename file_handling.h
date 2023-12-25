#pragma once
#include "game_definitions.h"

void leaderboard(void (*whatToPrint)(Player *, short));
void addPlayerToScoreboard(Player *player);
Player findPlayer(char *playerName);