#pragma once

#include <cseries/cseries.h>
#include <memory/static_arrays.h>

/* ---------- constants */

enum
{
	k_maximum_simulation_history_action_count = 16
};

enum e_simulation_history_flags
{
	_simulation_history_recording_state_bit,
	_simulation_history_requesting_undo_bit,
	_simulation_history_performing_undo_bit,
	_simulation_history_requesting_redo_bit,
	_simulation_history_performing_redo_bit,
	k_number_of_simulation_history_flags
};

/* ---------- classes */

struct s_simulation_history_action
{
	const wchar_t *description;
	void (*apply)(void *data);
	void *data;
};

class c_simulation_history_manager
{
public:
	c_simulation_history_manager();

	void clear();

	bool is_recording() const;
	void start_recording();
	void stop_recording();

	bool can_undo() const;
	bool is_performing_undo() const;
	void request_undo();
	void perform_undo();

	bool can_redo() const;
	bool is_performing_redo() const;
	void request_redo();
	void perform_redo();

	void push(const wchar_t *description, void *address, void(*apply)(void *));

	s_simulation_history_action &get_undo_top();
	s_simulation_history_action &get_redo_top();

	void update();

private:
	c_flags<e_simulation_history_flags, qword,
		k_number_of_simulation_history_flags> m_flags;

	c_static_stack<s_simulation_history_action,
		k_maximum_simulation_history_action_count> m_undo_stack;

	c_static_stack<s_simulation_history_action,
		k_maximum_simulation_history_action_count> m_redo_stack;
};
