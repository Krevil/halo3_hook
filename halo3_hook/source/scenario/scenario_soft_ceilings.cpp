
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#include <main/main.h>
#include <scenario/scenario_soft_ceilings.h>

/* ---------- globals */

static bool g_soft_ceilings_enabled = true;
static bool g_soft_ceilings_access = false;

/* ---------- prototypes */

static __int64 __fastcall scenario_soft_ceilings_get_features(void *features, const real_point3d *position, real radius, real height, real width);
static decltype(scenario_soft_ceilings_get_features) *scenario_soft_ceilings_get_features__original = nullptr;

static __int64 __fastcall scenario_soft_ceilings_object_is_on_kill_surface(word object_index);
static decltype(scenario_soft_ceilings_object_is_on_kill_surface) *scenario_soft_ceilings_object_is_on_kill_surface__original = nullptr;

static bool __fastcall scenario_soft_ceilings_pin_camera_position(real_point3d *position, real camera_radius, const real k_ceiling_search_radius);
static decltype(scenario_soft_ceilings_pin_camera_position) *scenario_soft_ceilings_pin_camera_position__original = nullptr;

static __int64 __fastcall scenario_soft_ceilings_update_object(
    void *soft_ceiling_contact,
    dword *ceiling_penetrated,
    const long ultimate_parent_object_type,
    const bool ultimate_parent_is_huge_vehicle,
    const real ultimate_parent_bounding_sphere_radius,
    const real_point3d *origin,
    const real_point3d *center,
    const bool biped_on_ground,
    const real ceiling_search_radius);
static decltype(scenario_soft_ceilings_update_object) *scenario_soft_ceilings_update_object__original = nullptr;

/* ---------- public code */

void scenario_soft_ceiling_hooks_initialize()
{
    scenario_soft_ceilings_get_features__original = main_get_module_offset<decltype(scenario_soft_ceilings_get_features__original)>(0x389E80);
    scenario_soft_ceilings_object_is_on_kill_surface__original = main_get_module_offset<decltype(scenario_soft_ceilings_object_is_on_kill_surface__original)>(0x38A410);
    scenario_soft_ceilings_pin_camera_position__original = main_get_module_offset<decltype(scenario_soft_ceilings_pin_camera_position__original)>(0x38A700);
    scenario_soft_ceilings_update_object__original = main_get_module_offset<decltype(scenario_soft_ceilings_update_object__original)>(0x38AC60);

    DetourAttach((PVOID *)&scenario_soft_ceilings_get_features__original, scenario_soft_ceilings_get_features);
    DetourAttach((PVOID *)&scenario_soft_ceilings_object_is_on_kill_surface__original, scenario_soft_ceilings_object_is_on_kill_surface);
    DetourAttach((PVOID *)&scenario_soft_ceilings_pin_camera_position__original, scenario_soft_ceilings_pin_camera_position);
    DetourAttach((PVOID *)&scenario_soft_ceilings_update_object__original, scenario_soft_ceilings_update_object);
}

void scenario_soft_ceiling_hooks_dispose()
{
    DetourDetach((PVOID *)&scenario_soft_ceilings_update_object__original, scenario_soft_ceilings_update_object);
    DetourDetach((PVOID *)&scenario_soft_ceilings_pin_camera_position__original, scenario_soft_ceilings_pin_camera_position);
    DetourDetach((PVOID *)&scenario_soft_ceilings_object_is_on_kill_surface__original, scenario_soft_ceilings_object_is_on_kill_surface);
    DetourDetach((PVOID *)&scenario_soft_ceilings_get_features__original, scenario_soft_ceilings_get_features);
}

bool scenario_soft_ceilings_access()
{
    return g_soft_ceilings_access;
}

bool scenario_soft_ceilings_enabled()
{
    return g_soft_ceilings_enabled;
}

void scenario_soft_ceilings_set_enabled(bool enabled)
{
    g_soft_ceilings_enabled = enabled;
}

/* ---------- private code */

static __int64 __fastcall scenario_soft_ceilings_get_features(
    void *features,
    const real_point3d *position,
    real radius,
    real height,
    real width)
{
    g_soft_ceilings_access = true;

    auto result = scenario_soft_ceilings_get_features__original(
        features,
        position,
        radius,
        height,
        width);

    g_soft_ceilings_access = false;

    return result;
}

static __int64 __fastcall scenario_soft_ceilings_object_is_on_kill_surface(
    word object_index)
{
    g_soft_ceilings_access = true;

    auto result = scenario_soft_ceilings_object_is_on_kill_surface__original(
        object_index);

    g_soft_ceilings_access = false;

    return result;
}

static bool __fastcall scenario_soft_ceilings_pin_camera_position(
    real_point3d *position,
    real camera_radius,
    const real k_ceiling_search_radius)
{
    g_soft_ceilings_access = true;

    auto result = scenario_soft_ceilings_pin_camera_position__original(
        position,
        camera_radius,
        k_ceiling_search_radius);

    g_soft_ceilings_access = false;

    return result;
}

static __int64 __fastcall scenario_soft_ceilings_update_object(
    void *soft_ceiling_contact,
    dword *ceiling_penetrated,
    const long ultimate_parent_object_type,
    const bool ultimate_parent_is_huge_vehicle,
    const real ultimate_parent_bounding_sphere_radius,
    const real_point3d *origin,
    const real_point3d *center,
    const bool biped_on_ground,
    const real ceiling_search_radius)
{
    g_soft_ceilings_access = true;

    auto result = scenario_soft_ceilings_update_object__original(
        soft_ceiling_contact,
        ceiling_penetrated,
        ultimate_parent_object_type,
        ultimate_parent_is_huge_vehicle,
        ultimate_parent_bounding_sphere_radius,
        origin,
        center,
        biped_on_ground,
        ceiling_search_radius);

    g_soft_ceilings_access = false;

    return result;
}
