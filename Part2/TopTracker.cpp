#include "TopTracker.h"

TopTracker::Action::Action(uint64_t player_id, const std::string &action_type):
	player_id(player_id),
	action_type(action_type),
	timestamp(std::chrono::steady_clock::now())
{ }

TopTracker::TopTracker(size_t max_actions, std::chrono::seconds timeout):
	max_actions(max_actions),
	timeout(timeout)
{ }

void TopTracker::add_action(uint64_t player_id, const std::string &action_type)
{
	cleanup_expired();

	if (actions.size() >= max_actions)
	{
		actions.pop_front();
	}

	actions.emplace_back(player_id, action_type);
}

void TopTracker::cleanup_expired()
{
	auto now = std::chrono::steady_clock::now();

	while (!actions.empty())
	{
		const auto &oldest = actions.front();
		if (now - oldest.timestamp <= timeout)
        {
			break;
        }

		actions.pop_front();
	}
}

const std::deque<Action>& TopTracker::get_actions() const
{
	return actions;
}
