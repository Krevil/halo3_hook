
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#include <game/game.h>
#include <game/players.h>
#include <main/main.h>

/* ---------- globals */

static bool g_force_multiplayer_customization = false;

/* ---------- prototypes */

static bool __fastcall player_spawn(
    long player_index,
    const real_point3d *optional_desired_spawn_location,
    const real *optional_desired_facing);

static decltype(player_spawn) *player_spawn__original = nullptr;

/* ---------- public code */

void player_hooks_initialize()
{
    player_spawn__original = main_get_from_module_offset<decltype(player_spawn__original)>(0x2ACD40);

    DetourAttach((PVOID *)&player_spawn__original, player_spawn);
}

void player_hooks_dispose()
{
    DetourDetach((PVOID *)&player_spawn__original, player_spawn);
}

bool players_force_multiplayer_customization_enabled()
{
    return g_force_multiplayer_customization;
}

void players_set_force_multiplayer_customization_enabled(bool enabled)
{
    g_force_multiplayer_customization = enabled;
}

/* ---------- private code */

bool __fastcall player_spawn(
    long player_index,
    const real_point3d *optional_desired_spawn_location,
    const real *optional_desired_facing)
{
    byte *campaign_check_instruction = main_get_from_module_offset<byte *>(0x2AD0EC);

    if (g_force_multiplayer_customization)
    {
        // nop campaign check for multiplayer customization
        campaign_check_instruction[0] = 0x90;
        campaign_check_instruction[1] = 0x90;
    }

    bool result = player_spawn__original(
        player_index,
        optional_desired_spawn_location,
        optional_desired_facing);

    if (g_force_multiplayer_customization)
    {
        // restore campaign check for multiplayer customization
        campaign_check_instruction[0] = 0x75;
        campaign_check_instruction[1] = 0x0D;
    }

    return result;
}
