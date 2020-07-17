
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#include <main/main.h>
#include <objects/object_hooks.h>
#include <physics/havok_component_hooks.h>

/* ---------- prototypes */

static bool __fastcall c_havok_contact_point__is_climbable_surface(void *contact_point);
static decltype(c_havok_contact_point__is_climbable_surface) *c_havok_contact_point__is_climbable_surface__original = nullptr;

/* ---------- public code */

void havok_component_hooks_initialize()
{
	c_havok_contact_point__is_climbable_surface__original = main_get_module_offset<decltype(c_havok_contact_point__is_climbable_surface__original)>(0x334070);

	DetourAttach((PVOID *)&c_havok_contact_point__is_climbable_surface__original, c_havok_contact_point__is_climbable_surface);
}

void havok_component_hooks_dispose()
{
	DetourDetach((PVOID *)&c_havok_contact_point__is_climbable_surface__original, c_havok_contact_point__is_climbable_surface);
}

/* ---------- private code */

static bool __fastcall c_havok_contact_point__is_climbable_surface(void *contact_point)
{
	long contact_point_object_index = *(long *)((char *)contact_point + 0x14);
	unsigned char surface_flags = *(unsigned char *)((char *)contact_point + 0x40);
	void *multiplayer_properties = object_try_and_get_multiplayer(contact_point_object_index);

	if (multiplayer_properties)
	{
		unsigned short multiplayer_flags = *(unsigned short *)multiplayer_properties;
		constexpr const unsigned short k_climbable_bit = 12U;

		if ((multiplayer_flags & (1U << k_climbable_bit)) != 0)
		{
			return true;
		}
	}

	return c_havok_contact_point__is_climbable_surface__original(contact_point);
}
