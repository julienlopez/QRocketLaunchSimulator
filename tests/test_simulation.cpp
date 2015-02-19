#include "body.hpp"
#include "engine.hpp"
#include "rocket.hpp"
#include "rocketmodel.hpp"

#include <external/json.h>

#include <boost/units/cmath.hpp>

#include <gtest/gtest.h>

using nlohmann::json;

using boost::units::si::kilograms;
using boost::units::si::meters;
using boost::units::si::newtons;
using boost::units::si::seconds;

struct TestSimulationBasicRocketMasslessBody : public ::testing::Test
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
	const Body body = {0 * kilograms, 6378 * meters};
	Engine engine = {rocket, body};
	const Engine::position_t expected_initial_position = {0, body.radius + rocket.totalLength(), 0};
};

TEST_F(TestSimulationBasicRocketMasslessBody, TestInitialConditions)
{
	EXPECT_NEAR(expected_initial_position.x().value(), engine.state().position.x().value(), 1E-6);
	EXPECT_NEAR(expected_initial_position.y().value(), engine.state().position.y().value(), 1E-6);
	EXPECT_NEAR(expected_initial_position.z().value(), engine.state().position.z().value(), 1E-6);
	EXPECT_NEAR(0, engine.state().velocity.norm2().value(), 1E-6);
	EXPECT_EQ(0 * newtons, rocket.currentThrust());
	EXPECT_EQ(1, rocket.stages().front().fillingRate());
	EXPECT_NEAR(rocket.totalLength().value(), engine.altitude().value(), 1E-3);
	EXPECT_EQ(model.stages.front().gross_mass, rocket.stages().front().currentMass());
}

TEST_F(TestSimulationBasicRocketMasslessBody, TestStateAtLaunch)
{
	rocket.fire();
	EXPECT_NEAR(expected_initial_position.x().value(), engine.state().position.x().value(), 1E-6);
	EXPECT_NEAR(expected_initial_position.y().value(), engine.state().position.y().value(), 1E-6);
	EXPECT_NEAR(expected_initial_position.z().value(), engine.state().position.z().value(), 1E-6);
	EXPECT_NEAR(0, engine.state().velocity.norm2().value(), 1E-6);
	EXPECT_EQ(model.stages.front().thrust, rocket.currentThrust());
	const utils::units::acceleration_vector expected_acceleration
		= {0, model.stages.front().thrust / rocket.currentMass(), 0};
	EXPECT_EQ(expected_acceleration, engine.currentAcceleration());
	EXPECT_EQ(1, rocket.stages().front().fillingRate());
	EXPECT_NEAR(rocket.totalLength().value(), engine.altitude().value(), 1E-3);
	EXPECT_EQ(model.stages.front().gross_mass, rocket.stages().front().currentMass());
}

TEST_F(TestSimulationBasicRocketMasslessBody, TestStateAfterLaunch)
{
	const auto step = .1 * seconds;
	rocket.fire();
	engine.tick(step);
	EXPECT_EQ(step, engine.currentTime());
	const auto expected = Engine::position_t{0, body.radius + rocket.totalLength(), 0};
	EXPECT_NEAR(expected.x().value(), engine.state().position.x().value(), 1E-6);
	EXPECT_NEAR(expected.y().value() + .237, engine.state().position.y().value(), 1E-3);
	EXPECT_NEAR(expected.z().value(), engine.state().position.z().value(), 1E-6);
	EXPECT_GT(engine.state().velocity.norm().value(), 0);
	EXPECT_LT(rocket.stages().front().fillingRate(), 1);
	EXPECT_LT(rocket.stages().front().currentMass(), model.stages.front().gross_mass);
	EXPECT_NEAR(rocket.totalLength().value() + .237, engine.altitude().value(), 1E-3);
}

TEST_F(TestSimulationBasicRocketMasslessBody, TestStateTillBurnout)
{
	const auto step = .1 * seconds;
	rocket.fire();

	while(engine.currentTime() <= model.stages.front().burn_time + step)
		engine.tick(step);

	ASSERT_GT(engine.currentTime(), model.stages.front().burn_time);
	EXPECT_EQ(0, rocket.stages().front().fillingRate());
	EXPECT_EQ(0 * newtons, rocket.currentThrust());
	EXPECT_EQ(model.stages.front().dry_mass, rocket.stages().front().currentMass());
}
