
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#include <main/main.h>
#include <math/real_math.h>
#include <scenario/scenario.h>

/* ---------- prototypes */

static bool g_safe_zones_enabled = true;

/* ---------- prototypes */

static bool __fastcall scenario_position_inside_safe_zone(const real_point3d *position);
static decltype(scenario_position_inside_safe_zone) *scenario_position_inside_safe_zone__original = nullptr;

/* ---------- public code */

void scenario_hooks_initialize()
{
	scenario_position_inside_safe_zone__original = main_get_module_offset<decltype(scenario_position_inside_safe_zone__original)>(0x246150);

	DetourAttach((PVOID *)&scenario_position_inside_safe_zone__original, scenario_position_inside_safe_zone);
}

void scenario_hooks_dispose()
{
}

bool scenario_safe_zones_enabled()
{
	return g_safe_zones_enabled;
}

void scenario_set_safe_zones_enabled(bool enabled)
{
	g_safe_zones_enabled = enabled;
}

/* ---------- private code */

bool __fastcall scenario_position_inside_safe_zone(const real_point3d *position)
{
	if (!g_safe_zones_enabled)
	{
		return true;
	}

	return scenario_position_inside_safe_zone__original(position);
}
