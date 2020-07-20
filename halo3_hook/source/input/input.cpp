
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#include <input/input.h>
#include <interface/chud/chud_messaging.h>
#include <main/main.h>
#include <objects/lights.h>
#include <render/render_objects.h>
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
	bool result = input_update__original();

	byte key_frames[NUMBER_OF_KEYS];

	for (short i = 0; i < NUMBER_OF_KEYS; i++)
	{
		key_frames[i] = input_key_frames_down(i);
	}

	if (key_frames[_key_control] && key_frames[_keypad_1] && (key_frames[_key_control] == 1 || key_frames[_keypad_1] == 1))
	{
		render_objects_motion_blur_set_enabled(false);
		chud_messaging_post(0, L"Motion blur disabled.", 0);
	}
	else if (key_frames[_key_control] && key_frames[_keypad_2] && (key_frames[_key_control] == 1 || key_frames[_keypad_2] == 1))
	{
		render_objects_motion_blur_set_enabled(true);
		chud_messaging_post(0, L"Motion blur enabled.", 0);
	}
	else if (key_frames[_keypad_1] == 1)
	{
		scenario_kill_triggers_set_enabled(true);
		chud_messaging_post(0, L"Kill triggers enabled.", 0);
	}
	else if (key_frames[_keypad_2] == 1)
	{
		scenario_kill_triggers_set_enabled(false);
		chud_messaging_post(0, L"Kill triggers disabled.", 0);
	}
	else if (key_frames[_keypad_4] == 1)
	{
		lights_set_forced_color(true, 1.0f, 0.0f, 0.0f);
		chud_messaging_post(0, L"Forced light color: Red", 0);
	}
	else if (key_frames[_keypad_5] == 1)
	{
		lights_set_forced_color(true, 0.0f, 1.0f, 0.0f);
		chud_messaging_post(0, L"Forced light color: Green", 0);
	}
	else if (key_frames[_keypad_6] == 1)
	{
		lights_set_forced_color(true, 0.0f, 0.0f, 1.0f);
		chud_messaging_post(0, L"Forced light color: Blue", 0);
	}
	else if (key_frames[_keypad_7] == 1)
	{
		lights_set_forced_color(false);
		chud_messaging_post(0, L"Forced light color: None", 0);
	}

	return result;
}
