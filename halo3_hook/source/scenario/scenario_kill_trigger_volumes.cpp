
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#include <main/main.h>
#include <scenario/scenario_kill_trigger_volumes.h>

/* ---------- globals */

static bool g_kill_triggers_enabled = true;

/* ---------- prototypes */

static __int64 __fastcall scenario_kill_trigger_volume_test_object(__int64 object_index, bool *safe_position);
static decltype(scenario_kill_trigger_volume_test_object) *scenario_kill_trigger_volume_test_object__original = nullptr;

/* ---------- public code */

void scenario_kill_trigger_volume_hooks_initialize()
{
	scenario_kill_trigger_volume_test_object__original = main_get_module_offset<decltype(scenario_kill_trigger_volume_test_object__original)>(0x383110);

	DetourAttach((PVOID *)&scenario_kill_trigger_volume_test_object__original, scenario_kill_trigger_volume_test_object);
}

void scenario_kill_trigger_volume_hooks_dispose()
{
	DetourDetach((PVOID *)&scenario_kill_trigger_volume_test_object__original, scenario_kill_trigger_volume_test_object);
}

bool scenario_kill_triggers_enabled()
{
	return g_kill_triggers_enabled;
}

void scenario_kill_triggers_set_enabled(bool value)
{
	g_kill_triggers_enabled = value;
}

/* ---------- private code */

static __int64 __fastcall scenario_kill_trigger_volume_test_object(__int64 object_index, bool *safe_position)
{
	if (!g_kill_triggers_enabled)
	{
		if (safe_position)
		{
			*safe_position = true;
		}

		return false;
	}

	return scenario_kill_trigger_volume_test_object__original(object_index, safe_position);
}
