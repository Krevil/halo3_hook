#pragma once

/* ---------- prototypes/scenario.cpp */

void scenario_hooks_initialize();
void scenario_hooks_dispose();

bool scenario_safe_zones_enabled();
void scenario_set_safe_zones_enabled(bool enabled);
