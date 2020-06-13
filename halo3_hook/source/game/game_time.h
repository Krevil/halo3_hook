/*
game_time.h
	common game time declarations
*/

#pragma once

/* ---------- prototypes */

bool game_time_initialize(void);
void game_time_dispose(void);

long long __fastcall game_seconds_to_ticks_round(float seconds);
