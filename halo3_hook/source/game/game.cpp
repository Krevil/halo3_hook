
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#include <game/game.h>
#include <main/main.h>

/* ---------- prototypes */

static __int64 __fastcall game_update(int tick_count, real *game_seconds_elapsed);
static decltype(game_update) *game_update__original = nullptr;

/* ---------- public code */

void game_hooks_initialize()
{
	game_update__original = main_get_typed_module_address<decltype(game_update__original)>(0x29F7C0);

	DetourAttach((PVOID *)&game_update__original, game_update);
}

void game_hooks_dispose()
{
	DetourDetach((PVOID *)&game_update__original, game_update);
}

bool game_is_authoritative()
{
	// TODO: requires manual implementation, function has been inlined
	exit(NONE);
	return false;
}

bool game_is_authoritative_playback()
{
	return main_get_typed_module_address<decltype(&game_is_authoritative_playback)>(0x11555C)();
}

bool game_is_available()
{
	return main_get_typed_module_address<decltype(&game_is_available)>(0x29D310)();
}

bool game_is_campaign()
{
	return main_get_typed_module_address<decltype(&game_is_campaign)>(0x29D350)();
}

bool game_is_cooperative()
{
	return main_get_typed_module_address<decltype(&game_is_cooperative)>(0x29D380)();
}

bool game_is_distributed()
{
	return main_get_typed_module_address<decltype(&game_is_distributed)>(0x29D3C0)();
}

bool game_is_finished()
{
	return main_get_typed_module_address<decltype(&game_is_finished)>(0x29D400)();
}

bool game_is_finished_immediate()
{
	return main_get_typed_module_address<decltype(&game_is_finished_immediate)>(0x29D430)();
}

bool game_is_lost()
{
	return main_get_typed_module_address<decltype(&game_is_lost)>(0x29D470)();
}

bool game_is_multiplayer()
{
	return main_get_typed_module_address<decltype(&game_is_multiplayer)>(0x29D4A0)();
}

bool game_is_networked()
{
	return main_get_typed_module_address<decltype(&game_is_networked)>(0x29D4D0)();
}

bool game_is_or_was_cooperative()
{
	return main_get_typed_module_address<decltype(&game_is_or_was_cooperative)>(0x29D510)();
}

bool game_is_playback()
{
	return main_get_typed_module_address<decltype(&game_is_playback)>(0x29D6B0)();
}

bool game_is_playtest()
{
	return main_get_typed_module_address<decltype(&game_is_playtest)>(0x29D6F0)();
}

bool game_is_predicted()
{
	return main_get_typed_module_address<decltype(&game_is_predicted)>(0x29D720)();
}

bool game_is_server()
{
	return main_get_typed_module_address<decltype(&game_is_server)>(0x29D750)();
}

bool game_is_splitscreen_deterministic()
{
	return main_get_typed_module_address<decltype(&game_is_splitscreen_deterministic)>(0x29D790)();
}

bool game_is_synchronous_networking()
{
	return main_get_typed_module_address<decltype(&game_is_synchronous_networking)>(0x29D7F0)();
}

bool game_is_ui_shell()
{
	return main_get_typed_module_address<decltype(&game_is_ui_shell)>(0x29D830)();
}

/* ---------- private code */

__int64 __fastcall game_update(int tick_count, real *game_seconds_elapsed)
{
	// TODO: any pre-update logic here

	auto result = game_update__original(tick_count, game_seconds_elapsed);

	// TODO: any post-update logic here

	return result;
}
