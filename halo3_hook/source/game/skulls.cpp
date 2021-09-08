#include <game/skulls.h>
#include <main/main.h>
#include <bitset>

/// <summary>
/// Byte values for each skull
/// </summary>

enum MCC_Skulls_Primary
{
    Envy = 0x2,
    Anger = 0x40,
    Bandana = 0x80
};

enum MCC_Skulls_Secondary
{
    Bonded_Pair = 0x1,
    Boom = 0x4,
    Eye_Patch = 0x8,
    Feather = 0x10,
    Foreign = 0x20,
    Ghost = 0x40,
    Grunt_Funeral = 0x80
};

enum MCC_Skulls_Tertiary
{
    Jacked = 0x1,
    Malfunction = 0x2,
    Masterblaster = 0x4,
    Pinata = 0x8,
    Prophet_Birthday_Party = 0x10,
    Recession = 0x20,
    Scarab = 0x40,
    So_Angry = 0x80
};

enum MCC_Skulls_Quaternary
{
    Sputnik = 0x1,
    Streaking = 0x2,
    Swarm = 0x4,
    Thats_Just_Wrong = 0x8,
    They_Come_Back = 0x10,
    Acrophobia = 0x20
};

enum Halo3_Skulls_Primary
{
    Iron = 0x1,
    Blackeye = 0x2,
    Tough_Luck = 0x4,
    Catch = 0x8,
    Fog = 1 << 0x10,
    Famine = 1 << 0x20,
    Thunderstorm = 1 << 0x40,
    Tilt = 1 << 0x80
};

enum Halo3_Skulls_Secondary
{
    Assassins = 0x1,
    Blind = 0x2,
    Cowbell = 0x4,
    Grunt_Birthday_Party = 0x8,
    IWHBYD = 0x10
};

/// <summary>
/// Offsets from the game header in memory
/// </summary>

enum Skull_Offsets
{
    MCC_Primary = 0x10536,
    MCC_Secondary = 0x10537,
    MCC_Tertiary = 0x10538,
    MCC_Quaternary = 0x10539,

    Halo3_Primary = 0x1053C,
    Halo3_Secondary = 0x10540
};

void __fastcall set_acrophobia(bool enabled)
{
    byte* skulls = *main_get_typed_module_address<byte**>(0x1CB15C8);
    if (enabled)
    {

        skulls[MCC_Quaternary] = skulls[MCC_Quaternary] | Acrophobia;
    }
    else
    {
        skulls[MCC_Quaternary] = skulls[MCC_Quaternary] ^ Acrophobia;
    }

}