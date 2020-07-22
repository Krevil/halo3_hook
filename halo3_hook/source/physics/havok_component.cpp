
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#include <cache/cache_files.h>
#include <main/main.h>
#include <objects/objects.h>
#include <physics/havok_component.h>
#include <tag_files/tag_groups.h>

/* ---------- globals */

static bool g_climbable_checks_enabled = false;

/* ---------- prototypes */

static bool __fastcall c_havok_contact_point__is_climbable_surface(void *contact_point);
static decltype(c_havok_contact_point__is_climbable_surface) *c_havok_contact_point__is_climbable_surface__original = nullptr;

/* ---------- public code */

void havok_component_hooks_initialize()
{
	c_havok_contact_point__is_climbable_surface__original = main_get_module_pointer_at_offset<decltype(c_havok_contact_point__is_climbable_surface__original)>(0x334070);

	DetourAttach((PVOID *)&c_havok_contact_point__is_climbable_surface__original, c_havok_contact_point__is_climbable_surface);
}

void havok_component_hooks_dispose()
{
	DetourDetach((PVOID *)&c_havok_contact_point__is_climbable_surface__original, c_havok_contact_point__is_climbable_surface);
}

bool havok_component_climbable_checks_enabled()
{
	return g_climbable_checks_enabled;
}

void havok_component_set_climbable_checks_enabled(bool enabled)
{
	g_climbable_checks_enabled = enabled;
}

/* ---------- private code */

static bool __fastcall c_havok_contact_point__is_climbable_surface(void *contact_point)
{
	if (!g_climbable_checks_enabled)
	{
		return true;
	}

	long object_index = *(long *)((char *)contact_point + 0x14);
	void *object_datum = object_try_and_get_and_verify_type(object_index, (dword)NONE);

	if (object_datum)
	{
		void *object_definition = tag_get('obje', *(long *)object_datum);

		if (object_definition)
		{
			s_tag_block *multiplayer_object_block = (s_tag_block *)((char *)object_definition + 0xEC);
			void *multiplayer_object_definition = tag_block_get_element_with_size(multiplayer_object_block, 0, 0xC4);

			if (multiplayer_object_definition)
			{
				word multiplayer_flags = *(word *)((char *)multiplayer_object_definition + 0x4);
				constexpr const word k_climbable_bit = 12U;

				if ((multiplayer_flags & (1U << k_climbable_bit)) != 0)
				{
					return true;
				}
			}
		}
	}

	return c_havok_contact_point__is_climbable_surface__original(contact_point);
}
