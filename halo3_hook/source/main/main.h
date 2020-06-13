/*
main.h
	common declarations for the DLL wrapper
*/

#pragma once

/* ---------- structures */

struct s_main_globals
{
	void *module_address;
};

/* ---------- globals */

extern s_main_globals g_main_globals;

/* ---------- prototypes */

bool main_initialize(void);
void main_dispose(void);
