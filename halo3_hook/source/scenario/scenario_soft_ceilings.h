#pragma once

/* ---------- prototypes/scenario_soft_ceilings.cpp */

void scenario_soft_ceiling_hooks_initialize();
void scenario_soft_ceiling_hooks_dispose();

bool scenario_soft_ceilings_access();
bool scenario_soft_ceilings_enabled();
void scenario_soft_ceilings_set_enabled(bool enabled);
