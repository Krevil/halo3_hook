#pragma once

#include <cseries/cseries.h>

/* ---------- prototypes/players.cpp */

void player_hooks_initialize();
void player_hooks_dispose();

bool player_is_spawning();

bool players_force_multiplayer_customization_enabled();
void players_set_force_multiplayer_customization_enabled(bool enabled);
