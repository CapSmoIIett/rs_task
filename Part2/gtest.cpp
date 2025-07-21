#include "TopTracker.h"
#include <gtest/gtest.h>
#include <thread>
#include <chrono>

// Фикстура для тестирования TopTracker
class TopTrackerTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		this->tracker = new TopTracker(3, std::chrono::seconds(2));
	}

	void TearDown() override
	{
		delete this->tracker;
	}

	TopTracker *tracker;
};

TEST_F(TopTrackerTest, AddAction)
{
	this->tracker->add_action(1, "login");
	EXPECT_EQ(this->tracker->get_actions().size(), 1u);
	this->tracker->add_action(2, "buy");
	EXPECT_EQ(this->tracker->get_actions().size(), 2u);
}

TEST_F(TopTrackerTest, ExceedingMax)
{
	this->tracker->add_action(1, "a");
	this->tracker->add_action(2, "b");
	this->tracker->add_action(3, "c");
	this->tracker->add_action(4, "d"); // должен вытеснить первую
	EXPECT_EQ(this->tracker->get_actions().size(), 3u);
	EXPECT_EQ(this->tracker->get_actions().front().player_id, 2u);
}

TEST_F(TopTrackerTest, CleanupExpired)
{
	this->tracker->add_action(1, "a");
	std::this_thread::sleep_for(std::chrono::seconds(3));
	this->tracker->cleanup_expired();
	EXPECT_TRUE(this->tracker->get_actions().empty());
}

TEST_F(TopTrackerTest, GetActionsByPlayer)
{
	this->tracker->add_action(1, "a");
	this->tracker->add_action(2, "b");
	this->tracker->add_action(1, "c");

	auto count = 0u;
	for (const auto &action : this->tracker->get_actions())
	{
		if (action.player_id == 1)
			++count;
	}
	EXPECT_EQ(count, 2u);
}

TEST_F(TopTrackerTest, GetActionsByType)
{
	this->tracker->add_action(1, "x");
	this->tracker->add_action(2, "y");
	this->tracker->add_action(3, "x");

	auto count = 0u;
	for (const auto &action : this->tracker->get_actions())
	{
		if (action.action_type == "x")
			++count;
	}
	EXPECT_EQ(count, 2u);
}
