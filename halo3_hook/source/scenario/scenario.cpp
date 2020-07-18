
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#include <main/main.h>
#include <math/real_math.h>
#include <scenario/scenario.h>
#include <scenario/scenario_soft_ceilings.h>

/* ---------- prototypes */

static bool g_safe_zones_enabled = true;

/* ---------- prototypes */

static void *__fastcall global_structure_design_get(long structure_bsp_index);
static decltype(global_structure_design_get) *global_structure_design_get__original = nullptr;

static bool __fastcall scenario_position_inside_safe_zone(const real_point3d *position);
static decltype(scenario_position_inside_safe_zone) *scenario_position_inside_safe_zone__original = nullptr;

/* ---------- public code */

void scenario_hooks_initialize()
{
	global_structure_design_get__original = main_get_module_offset<decltype(global_structure_design_get__original)>(0x244F40);
	scenario_position_inside_safe_zone__original = main_get_module_offset<decltype(scenario_position_inside_safe_zone__original)>(0x246150);

	DetourAttach((PVOID *)&global_structure_design_get__original, global_structure_design_get);
	DetourAttach((PVOID *)&scenario_position_inside_safe_zone__original, scenario_position_inside_safe_zone);
}

void scenario_hooks_dispose()
{
	DetourDetach((PVOID *)&scenario_position_inside_safe_zone__original, scenario_position_inside_safe_zone);
	DetourDetach((PVOID *)&global_structure_design_get__original, global_structure_design_get);
}

bool scenario_safe_zones_enabled()
{
	return g_safe_zones_enabled;
}

void scenario_safe_zones_set_enabled(bool enabled)
{
	g_safe_zones_enabled = enabled;
}

/* ---------- private code */

static void *__fastcall global_structure_design_get(long structure_bsp_index)
{
	if (scenario_soft_ceilings_access() && !scenario_soft_ceilings_enabled())
	{
		return nullptr;
	}

	return global_structure_design_get__original(structure_bsp_index);
}

static bool __fastcall scenario_position_inside_safe_zone(const real_point3d *position)
{
	if (!g_safe_zones_enabled)
	{
		return true;
	}

	return scenario_position_inside_safe_zone__original(position);
}
