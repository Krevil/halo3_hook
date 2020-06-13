/*
game_time.cpp
*/

#include <game/game_time.h>
#include <main/main.h>

#include <stddef.h>

/* ---------- code */

long long __fastcall game_seconds_to_ticks_round(
    float seconds)
{
    static auto game_seconds_to_ticks_round_original = reinterpret_cast<decltype(&game_seconds_to_ticks_round)>(
        reinterpret_cast<size_t>(g_main_globals.module_address) + 0x2ABD90);

    return game_seconds_to_ticks_round_original(seconds);
}
