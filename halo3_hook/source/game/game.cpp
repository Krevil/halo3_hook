
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#include <main/main.h>
#include <game/game.h>

/* ---------- prototypes */

static __int64 __fastcall game_update(int tick_count, float *game_seconds_elapsed);
static decltype(game_update) *game_update__original = nullptr;

/* ---------- public code */

void game_hooks_initialize()
{
	game_update__original = main_get_module_offset<decltype(game_update__original)>(0x29F7C0);

	DetourAttach((PVOID *)&game_update__original, game_update);
}

void game_hooks_dispose()
{
	DetourDetach((PVOID *)&game_update__original, game_update);
}

/* ---------- private code */

__int64 __fastcall game_update(int tick_count, float *game_seconds_elapsed)
{
	// TODO: any pre-update logic here

	auto result = game_update__original(tick_count, game_seconds_elapsed);

	// TODO: any post-update logic here

	return result;
}
