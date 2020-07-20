#pragma once

#include <cseries/cseries.h>

/* ---------- prototypes/game.cpp */

void game_hooks_initialize();
void game_hooks_dispose();

bool game_is_authoritative();
bool game_is_authoritative_playback();
bool game_is_available();
bool game_is_campaign();
bool game_is_cooperative();
bool game_is_distributed();
bool game_is_finished();
bool game_is_finished_immediate();
bool game_is_lost();
bool game_is_multiplayer();
bool game_is_networked();
bool game_is_or_was_cooperative();
bool game_is_playback();
bool game_is_playtest();
bool game_is_predicted();
bool game_is_server();
bool game_is_splitscreen_deterministic();
bool game_is_synchronous_networking();
bool game_is_ui_shell();
