# Halo 3 Hooks
This project is a DLL wrapper for Halo 3 in the Master Chief Collection on PC. The DLL wrapper contains a collection of patches which are used to either fix bugs or extend the functionality of the game with new features.

# Special Thanks
Originally a fork of Camden's Halo 3 Hook, this remains in its absence.

This project would not be possible without the innovations made by the various people who contributed to ElDewrito, OpenSauce and Project Cartographer. While there are too many to list here, all the people from throughout the years who have provided pre-release builds of Halo, source code, user-made tools, laboriously-procured research and troubleshooting help have all helped directly shape the modern state of Halo modding for the community.

Thank you, all of you!

# Instructions

### Compiling:
* Open `halo3_hook.sln` with Visual Studio 2019 and build the solution

### Installing:
1. Seek to `C:\Program Files (x86)\Steam\steamapps\common\Halo The Master Chief Collection\halo3` and rename `halo3.dll` to `halo3_original.dll`
2. Copy `halo3.dll` from `halo3_hook\x64\Debug` or `halo3_hook\x64\Release` to `C:\Program Files (x86)\Steam\steamapps\common\Halo The Master Chief Collection\halo3`
3. Launch MCC and enjoy

# Shortcut Keys

```
numpad 1: enable safe zones
alt + numpad 1: disable safe zones
```
```
numpad 2: enable kill triggers
alt + numpad 2: disable kill triggers
```
```
numpad 3: enable soft ceilings
alt + numpad 3: disable soft ceilings
```
```
numpad 4: enable motion blur
alt + numpad 4: disable motion blur
```
```
numpad 5: enable climbable checks
alt + numpad 5: disable climbable checks
```
```
numpad 6: enable forced mp customization
alt + numpad 6: disable forced mp customization
```
