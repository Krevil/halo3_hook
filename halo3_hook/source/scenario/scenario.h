#pragma once

#include <cseries/cseries.h>

/* ---------- prototypes/scenario.cpp */

void scenario_hooks_initialize();
void scenario_hooks_dispose();

bool scenario_safe_zones_enabled();
void scenario_safe_zones_set_enabled(bool enabled);
