#include "engine.hpp"
#include "rocket.hpp"
#include "rocketmodel.hpp"

#include <external/json.h>

#include <gtest/gtest.h>

using nlohmann::json;

struct TestSimulationBasicRocket : public ::testing::Test
{
	static RocketModel createModel()
	{
		json js = {{"name", "rocket"}, {"stages", {{{"name", "P80"},
													{"length", 11.7},
													{"diameter", 3},
													{"dry_mass", 7330},
													{"gross_mass", 95695},
													{"thrust", 2261000},
													{"isp", 280},
													{"burn_time", 110},
													{"fuel", "solid"}}}},
				   {"fairings", {{"length", 7.88}, {"diameter", 2.6}}}};
		return RocketModel::fromJson(js);
	}

	const RocketModel model = createModel();
	const double payload_mass = 1E3;
	Rocket rocket = {model, payload_mass};
	const Engine::position_t initial_position = {0, 6378, 0};
	Engine engine = {rocket, initial_position};
	const Engine::position_t expected_initial_position
		= initial_position + Engine::position_t{0, rocket.totalLength(), 0};
};

TEST_F(TestSimulationBasicRocket, TestInitialConditions)
{
	EXPECT_NEAR(expected_initial_position.x(), engine.state().position.x(), 1E-6);
	EXPECT_NEAR(expected_initial_position.y(), engine.state().position.y(), 1E-6);
	EXPECT_NEAR(expected_initial_position.z(), engine.state().position.z(), 1E-6);
	EXPECT_EQ(0, rocket.currentThrust());
	EXPECT_NEAR(rocket.totalLength(), engine.altitude(), 1E-3);
}

TEST_F(TestSimulationBasicRocket, TestStateAtLaunch)
{
	rocket.fire();
	EXPECT_NEAR(expected_initial_position.x(), engine.state().position.x(), 1E-6);
	EXPECT_NEAR(expected_initial_position.y(), engine.state().position.y(), 1E-6);
	EXPECT_NEAR(expected_initial_position.z(), engine.state().position.z(), 1E-6);
	EXPECT_EQ(model.stages.front().thrust, rocket.currentThrust());
	EXPECT_NEAR(rocket.totalLength(), engine.altitude(), 1E-3);
}

TEST_F(TestSimulationBasicRocket, TestStateAfterLaunch)
{
	const double step = .1;
	rocket.fire();
	engine.tick(step);
	EXPECT_EQ(step, engine.currentTime());
	const auto expected = initial_position + Engine::position_t{0, rocket.totalLength(), 0};
	EXPECT_NEAR(expected.x(), engine.state().position.x(), 1E-6);
	EXPECT_NEAR(expected.y() + .237, engine.state().position.y(), 1E-3);
	EXPECT_NEAR(expected.z(), engine.state().position.z(), 1E-6);
	EXPECT_NEAR(rocket.totalLength() + .237, engine.altitude(), 1E-3);
}
