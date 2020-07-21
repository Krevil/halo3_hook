
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#include <game/game.h>
#include <game/game_engine_sandbox.h>
#include <input/input.h>
#include <interface/chud/chud_messaging.h>
#include <main/main.h>
#include <scenario/scenario_map_variant.h>
#include <simulation/simulation_history.h>

/* ---------- constants */

enum
{
	k_map_variant_data_size = 0xE090
};

/* ---------- globals */

static c_simulation_history_manager g_history_manager;

/* ---------- prototypes */

static bool __fastcall c_sandbox_engine__initialize_for_new_map(void *engine, void *);
static decltype(c_sandbox_engine__initialize_for_new_map) *c_sandbox_engine__initialize_for_new_map__original = nullptr;

static void __fastcall c_sandbox_engine__update(void *engine, void *);
static decltype(c_sandbox_engine__update) *c_sandbox_engine__update__original = nullptr;

static void __fastcall game_engine_sandbox_start_editing_object(long player_index, long map_variant_index);
static decltype(game_engine_sandbox_start_editing_object) *game_engine_sandbox_start_editing_object__original = nullptr;

/* ---------- public code */

void game_engine_sandbox_hooks_initialize()
{
	c_sandbox_engine__initialize_for_new_map__original = main_get_from_module_offset<decltype(c_sandbox_engine__initialize_for_new_map__original)>(0x2BCA10);
	c_sandbox_engine__update__original = main_get_from_module_offset<decltype(c_sandbox_engine__update__original)>(0x2BD020);
	game_engine_sandbox_start_editing_object__original = main_get_from_module_offset<decltype(game_engine_sandbox_start_editing_object__original)>(0x2C04D0);

	DetourAttach((PVOID *)&c_sandbox_engine__update__original, c_sandbox_engine__update);
	DetourAttach((PVOID *)&c_sandbox_engine__initialize_for_new_map__original, c_sandbox_engine__initialize_for_new_map);
	DetourAttach((PVOID *)&game_engine_sandbox_start_editing_object__original, game_engine_sandbox_start_editing_object);
}

void game_engine_sandbox_hooks_dispose()
{
	DetourAttach((PVOID *)&game_engine_sandbox_start_editing_object__original, game_engine_sandbox_start_editing_object);
	DetourDetach((PVOID *)&c_sandbox_engine__initialize_for_new_map__original, c_sandbox_engine__initialize_for_new_map);
	DetourDetach((PVOID *)&c_sandbox_engine__update__original, c_sandbox_engine__update);
}

/* ---------- private code */

static bool __fastcall c_sandbox_engine__initialize_for_new_map(void *engine, void *address)
{
	if (!c_sandbox_engine__initialize_for_new_map__original(engine, address))
	{
		return false;
	}

	g_history_manager.clear();
	g_history_manager.start_recording();

	return true;
}

static void __fastcall c_sandbox_engine__update(void *engine, void *address)
{
	c_sandbox_engine__update__original(engine, address);

	static void (*undo)() = []()
	{
		if (!g_history_manager.can_undo())
		{
			chud_messaging_post(0, L"Nothing to undo!", 0);
			return;
		}

		s_simulation_history_action &action = g_history_manager.get_undo_top();

		wchar_t message[256];
		swprintf_s(message, L"Undo %s", action.description);
		chud_messaging_post(0, message, 0);

		g_history_manager.request_undo();
	};

	static void (*redo)() = []()
	{
		if (!g_history_manager.can_redo())
		{
			chud_messaging_post(0, L"Nothing to redo!", 0);
			return;
		}

		s_simulation_history_action &action = g_history_manager.get_redo_top();

		wchar_t message[256];
		swprintf_s(message, L"Redo %s", action.description);
		chud_messaging_post(0, message, 0);

		g_history_manager.request_redo();
	};

	if (input_key_frames_down(_key_control))
	{
		if (input_key_frames_down(_key_shift) && input_key_frames_down(_key_z) == 1)
		{
			redo();
		}
		else if (input_key_frames_down(_key_z) == 1)
		{
			undo();
		}
		else if (input_key_frames_down(_key_y) == 1)
		{
			redo();
		}
	}

	g_history_manager.update();
}

void simulation_history_action_undo(void *data)
{
	assert(data);
}

void __fastcall game_engine_sandbox_start_editing_object(long player_index, long map_variant_index)
{
	if (game_is_authoritative() && g_history_manager.is_recording())
	{
		g_history_manager.push(L"object grabbed", game_engine_get_runtime_map_variant(), simulation_history_action_undo);
	}

	game_engine_sandbox_start_editing_object__original(player_index, map_variant_index);
}
