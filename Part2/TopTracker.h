#pragma once

#include <deque>
#include <chrono>
#include <string>
#include <cstdint>

class TopTracker
{
public:
	struct Action
	{
		uint64_t player_id;
		std::string action_type;
		std::chrono::steady_clock::time_point timestamp;

		Action(uint64_t player_id, const std::string &action_type);
	};

	explicit TopTracker(size_t max_actions, std::chrono::seconds timeout);
	~TopTracker() = default;

	void add_action(uint64_t player_id, const std::string &action_type);
	void cleanup_expired();
	const std::deque<Action>& get_actions() const;

private:
	std::deque<Action> actions;
    // причины выбора:
    // - O(1) вставка и удаление
    // сохранения последовательности 

	size_t max_actions;
	std::chrono::seconds timeout;
};
