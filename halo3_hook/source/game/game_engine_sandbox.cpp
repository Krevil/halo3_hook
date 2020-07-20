
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#include <game/game_engine_sandbox.h>
#include <input/input.h>
#include <main/main.h>

/* ---------- prototypes */

static void __fastcall c_sandbox_engine__update(void *engine, void *);
static decltype(c_sandbox_engine__update) *c_sandbox_engine__update__original = nullptr;

/* ---------- public code */

void game_engine_sandbox_hooks_initialize()
{
	c_sandbox_engine__update__original = main_get_module_offset<decltype(c_sandbox_engine__update__original)>(0x2BD020);

	DetourAttach((PVOID *)&c_sandbox_engine__update__original, c_sandbox_engine__update);
}

void game_engine_sandbox_hooks_dispose()
{
	DetourDetach((PVOID *)&c_sandbox_engine__update__original, c_sandbox_engine__update);
}

/* ---------- private code */

static void __fastcall c_sandbox_engine__update(void *engine, void *address)
{
	c_sandbox_engine__update__original(engine, address);

	if (input_key_frames_down(_key_control))
	{
		if (input_key_frames_down(_key_z))
		{
			if (input_key_frames_down(_key_shift))
			{
				// TODO: redo
			}
			else
			{
				// TODO: undo
			}
		}
		else if (input_key_frames_down(_key_y))
		{
			// TODO: redo
		}
	}
}
