#pragma once

#include <cseries/cseries.h>

/* ---------- prototypes/havok_component_hooks.cpp */

void havok_component_hooks_initialize();
void havok_component_hooks_dispose();

bool havok_component_climbable_checks_enabled();
void havok_component_set_climbable_checks_enabled(bool enabled);
