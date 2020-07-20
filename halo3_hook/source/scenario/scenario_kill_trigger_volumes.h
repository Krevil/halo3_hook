#pragma once

#include <cseries/cseries.h>

/* ---------- prototypes/scenario_kill_trigger_volumes.cpp */

void scenario_kill_trigger_volume_hooks_initialize();
void scenario_kill_trigger_volume_hooks_dispose();

bool scenario_kill_triggers_enabled();
void scenario_kill_triggers_set_enabled(bool value);
