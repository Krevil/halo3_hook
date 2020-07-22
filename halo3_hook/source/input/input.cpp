
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#include <game/players.h>
#include <input/input.h>
#include <interface/chud/chud_messaging.h>
#include <main/main.h>
#include <physics/havok_component.h>
#include <render/render_objects.h>
#include <scenario/scenario.h>
#include <scenario/scenario_kill_trigger_volumes.h>
#include <scenario/scenario_soft_ceilings.h>

/* ---------- prototypes */

static decltype(input_update) *input_update__original = nullptr;

/* ---------- public code */

void input_hooks_initialize()
{
	input_update__original = main_get_typed_module_address<decltype(input_update__original)>(0x255360);

	DetourAttach((PVOID *)&input_update__original, input_update);
}

void input_hooks_dispose()
{
	DetourDetach((PVOID *)&input_update__original, input_update);
}

byte __fastcall input_key_frames_down(short key_code)
{
	return main_get_typed_module_address<decltype(&input_key_frames_down)>(0x254B20)(key_code);
}

byte __fastcall input_mouse_button_frames_down(short button_index)
{
	return main_get_typed_module_address<decltype(&input_mouse_button_frames_down)>(0x254CD0)(button_index);
}

bool input_update()
{
	bool result = input_update__original();

	if (input_key_frames_down(_keypad_1) == 1)
	{
		if (input_key_frames_down(_key_alt))
		{
			scenario_set_safe_zones_enabled(false);
			chud_messaging_post(0, L"Safe zones disabled.", 0);
		}
		else
		{
			scenario_set_kill_triggers_enabled(true);
			chud_messaging_post(0, L"Safe zones enabled.", 0);
		}
	}
	else if (input_key_frames_down(_keypad_2) == 1)
	{
		if (input_key_frames_down(_key_alt))
		{
			scenario_set_kill_triggers_enabled(false);
			chud_messaging_post(0, L"Kill triggers disabled.", 0);
		}
		else
		{
			scenario_set_kill_triggers_enabled(true);
			chud_messaging_post(0, L"Kill triggers enabled.", 0);
		}
	}
	else if (input_key_frames_down(_keypad_3) == 1)
	{
		if (input_key_frames_down(_key_alt))
		{
			scenario_soft_ceilings_set_enabled(false);
			chud_messaging_post(0, L"Soft ceilings disabled.", 0);
		}
		else
		{
			scenario_soft_ceilings_set_enabled(true);
			chud_messaging_post(0, L"Soft ceilings enabled.", 0);
		}
	}
	else if (input_key_frames_down(_keypad_4) == 1)
	{
		if (input_key_frames_down(_key_alt))
		{
			render_objects_set_motion_blur_enabled(false);
			chud_messaging_post(0, L"Motion blur disabled.", 0);
		}
		else
		{
			render_objects_set_motion_blur_enabled(true);
			chud_messaging_post(0, L"Motion blur enabled.", 0);
		}
	}
	else if (input_key_frames_down(_keypad_5) == 1)
	{
		if (input_key_frames_down(_key_alt))
		{
			havok_component_set_climbable_checks_enabled(false);
			chud_messaging_post(0, L"Climbable checks disabled.", 0);
		}
		else
		{
			havok_component_set_climbable_checks_enabled(true);
			chud_messaging_post(0, L"Climbable checks enabled.", 0);
		}
	}
	else if (input_key_frames_down(_keypad_6) == 1)
	{
		if (input_key_frames_down(_key_alt))
		{
			players_set_force_multiplayer_customization_enabled(false);
			chud_messaging_post(0, L"Force multiplayer customization disabled.", 0);
		}
		else
		{
			players_set_force_multiplayer_customization_enabled(true);
			chud_messaging_post(0, L"Force multiplayer customization enabled.", 0);
		}
	}

	return result;
}
