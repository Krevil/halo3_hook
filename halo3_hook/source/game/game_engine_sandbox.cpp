
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#include <game/game_engine_sandbox.h>
#include <input/input.h>
#include <interface/chud/chud_messaging.h>
#include <main/main.h>
#include <simulation/simulation_history.h>

/* ---------- globals */

static c_simulation_history_manager g_history_manager;

/* ---------- prototypes */

static bool __fastcall c_sandbox_engine__initialize_for_new_map(void *engine, void *);
static decltype(c_sandbox_engine__initialize_for_new_map) *c_sandbox_engine__initialize_for_new_map__original = nullptr;

static void __fastcall c_sandbox_engine__update(void *engine, void *);
static decltype(c_sandbox_engine__update) *c_sandbox_engine__update__original = nullptr;

/* ---------- public code */

void game_engine_sandbox_hooks_initialize()
{
	c_sandbox_engine__initialize_for_new_map__original = main_get_module_offset<decltype(c_sandbox_engine__initialize_for_new_map__original)>(0x2BCA10);
	c_sandbox_engine__update__original = main_get_module_offset<decltype(c_sandbox_engine__update__original)>(0x2BD020);

	DetourAttach((PVOID *)&c_sandbox_engine__update__original, c_sandbox_engine__update);
	DetourAttach((PVOID *)&c_sandbox_engine__initialize_for_new_map__original, c_sandbox_engine__initialize_for_new_map);
}

void game_engine_sandbox_hooks_dispose()
{
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

		g_history_manager.request_undo();
	};

	static void (*redo)() = []()
	{
		if (!g_history_manager.can_redo())
		{
			chud_messaging_post(0, L"Nothing to redo!", 0);
			return;
		}

		g_history_manager.request_redo();
	};

	if (input_key_frames_down(_key_control) == 1)
	{
		if (input_key_frames_down(_key_z) == 1)
		{
			if (input_key_frames_down(_key_shift) == 1)
			{
				redo();
			}
			else
			{
				undo();
			}
		}
		else if (input_key_frames_down(_key_y) == 1)
		{
			redo();
		}
	}
}
