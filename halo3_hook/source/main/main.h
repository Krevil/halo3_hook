#pragma once

#include <cseries/cseries.h>

/* ---------- prototypes/main.cpp */

bool main_initialize(void *base_address);
void main_dispose();

bool main_initialized();
void *main_get_base_address();
void *main_get_module_address();
void *main_get_tls_address();

/* ---------- inline code */

template <typename t_type>
inline t_type main_get_module_offset(qword offset = 0)
{
	auto address = main_get_module_address();
	return (t_type)((char *)address + offset);
}

template <typename t_type>
inline t_type main_get_tls_offset(qword offset = 0)
{
	auto address = main_get_tls_address();
	return (t_type)((char *)address + offset);
}
