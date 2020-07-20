
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#include <input/input.h>
#include <main/main.h>
#include <objects/lights.h>
#include <scenario/scenario_kill_trigger_volumes.h>

/* ---------- prototypes */

static decltype(input_update) *input_update__original = nullptr;

/* ---------- public code */

void input_hooks_initialize()
{
	input_update__original = main_get_module_offset<decltype(input_update__original)>(0x255360);

	DetourAttach((PVOID *)&input_update__original, input_update);
}

void input_hooks_dispose()
{
	DetourDetach((PVOID *)&input_update__original, input_update);
}

byte __fastcall input_key_frames_down(short key_code)
{
	return main_get_module_offset<decltype(&input_key_frames_down)>(0x254B20)(key_code);
}

byte __fastcall input_mouse_button_frames_down(short button_index)
{
	return main_get_module_offset<decltype(&input_mouse_button_frames_down)>(0x254CD0)(button_index);
}

bool input_update()
{
	if (input_key_frames_down(_keypad_1))
	{
		scenario_kill_triggers_set_enabled(true);
	}
	else if (input_key_frames_down(_keypad_2))
	{
		scenario_kill_triggers_set_enabled(false);
	}
	else if (input_key_frames_down(_keypad_4))
	{
		lights_set_forced_color(true, 1.0f, 0.0f, 0.0f);
	}
	else if (input_key_frames_down(_keypad_5))
	{
		lights_set_forced_color(true, 0.0f, 1.0f, 0.0f);
	}
	else if (input_key_frames_down(_keypad_6))
	{
		lights_set_forced_color(true, 0.0f, 0.0f, 1.0f);
	}
	else if (input_key_frames_down(_keypad_7))
	{
		lights_set_forced_color(false);
	}

	return input_update__original();
}
