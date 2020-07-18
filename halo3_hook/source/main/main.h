/*
main.h
	common declarations for the DLL wrapper
*/

#pragma once

/* ---------- prototypes/main.cpp */

bool main_initialize(void *base_address);
void main_dispose();

bool main_initialized();
void *main_get_base_address();
void *main_get_module_address();
void *main_get_tls_address();

/* ---------- inline code */

template <typename t_type>
inline t_type main_get_module_offset(unsigned __int64 offset = 0)
{
	auto address = main_get_module_address();
	return (t_type)((char *)address + offset);
}

template <typename t_type>
inline t_type main_get_tls_offset(unsigned __int64 offset = 0)
{
	auto address = main_get_tls_address();
	return (t_type)((char *)address + offset);
}
