
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#include <game/game.h>
#include <game/game_globals.h>
#include <game/players.h>
#include <main/main.h>

/* ---------- globals */

static bool g_force_multiplayer_customization = false;

/* ---------- prototypes */

static e_player_character_type __fastcall player_get_character_type(long player_index);
static decltype(player_get_character_type) *player_get_character_type__original = nullptr;

static bool __fastcall player_spawn(
    long player_index,
    const real_point3d *optional_desired_spawn_location,
    const real *optional_desired_facing);
static decltype(player_spawn) *player_spawn__original = nullptr;

/* ---------- public code */

void player_hooks_initialize()
{
    player_get_character_type__original = main_get_typed_module_address<decltype(player_get_character_type__original)>(0x2AAF60);
    player_spawn__original = main_get_typed_module_address<decltype(player_spawn__original)>(0x2ACD40);

    DetourAttach((PVOID *)&player_get_character_type__original, player_get_character_type);
    DetourAttach((PVOID *)&player_spawn__original, player_spawn);
}

void player_hooks_dispose()
{
    DetourDetach((PVOID *)&player_spawn__original, player_spawn);
    DetourDetach((PVOID *)&player_get_character_type__original, player_get_character_type);
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

e_player_character_type __fastcall player_get_character_type(
    long player_index)
{
    byte *campaign_check_instruction = main_get_typed_module_address<byte *>(0x2AAFB0);

    if (g_force_multiplayer_customization && game_is_campaign())
    {
        // flip campaign check for player character type
        campaign_check_instruction[0] = 0x75;
    }

    e_player_character_type result = player_get_character_type__original(player_index);

    if (g_force_multiplayer_customization && game_is_campaign())
    {
        // restore campaign check for player character type
        campaign_check_instruction[0] = 0x74;
    }

    return result;
}

bool __fastcall player_spawn(
    long player_index,
    const real_point3d *optional_desired_spawn_location,
    const real *optional_desired_facing)
{
    byte *campaign_check_instruction = main_get_typed_module_address<byte *>(0x2AD0EC);

    if (g_force_multiplayer_customization)
    {
        // disable campaign check for multiplayer customization
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
