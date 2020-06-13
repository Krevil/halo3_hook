/*
game_time.cpp
*/

#include <game/game_time.h>
#include <main/main.h>

#include <stddef.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

/* ---------- private globals */

static decltype(game_seconds_to_ticks_round) *game_seconds_to_ticks_round_original = nullptr;

/* ---------- code */

bool game_time_initialize(
    void)
{
    game_seconds_to_ticks_round_original = reinterpret_cast<decltype(game_seconds_to_ticks_round_original)>(
        reinterpret_cast<size_t>(g_main_globals.module_address) + 0x2ABD90);

    DetourAttach(reinterpret_cast<void **>(&game_seconds_to_ticks_round_original), game_seconds_to_ticks_round);

    return true;
}

void game_time_dispose(
    void)
{
}

long long __fastcall game_seconds_to_ticks_round(
    float seconds)
{
    return game_seconds_to_ticks_round_original(seconds);
}
