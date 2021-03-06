#include "rocket.hpp"
#include "rocketmodel.hpp"

#include <external/json.h>

#include <gtest/gtest.h>

using json = nlohmann::json;

using boost::units::si::meters;
using boost::units::si::newtons;

struct TestRocketOneStage : public ::testing::Test
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
};

TEST_F(TestRocketOneStage, TestConstruction)
{
	Rocket rocket(model, payload_mass);
	EXPECT_EQ(model.name, rocket.name);
	ASSERT_EQ(1, rocket.stages().size());
	const auto& stage = rocket.stages().front();
	EXPECT_EQ(model.stages.front().name, stage.model.name);
	EXPECT_EQ(model.stages.front().length, stage.model.length);
	EXPECT_EQ(model.stages.front().diameter, stage.model.diameter);
	EXPECT_EQ(model.stages.front().dry_mass, stage.model.dry_mass);
	EXPECT_EQ(model.stages.front().gross_mass, stage.model.gross_mass);
	EXPECT_EQ(model.stages.front().thrust, stage.model.thrust);
	EXPECT_EQ(model.stages.front().isp, stage.model.isp);
	EXPECT_EQ(model.stages.front().burn_time, stage.model.burn_time);
	EXPECT_EQ(model.stages.front().fuel, stage.model.fuel);
}

struct TestRocketTwoStages : public ::testing::Test
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
													{"fuel", "solid"}},
												   {{"name", "Z23"},
													{"length", 8.39},
													{"diameter", 1.9},
													{"dry_mass", 2850},
													{"gross_mass", 28850},
													{"thrust", 871000},
													{"isp", 287.5},
													{"burn_time", 77},
													{"fuel", "solid"}}}},
				   {"fairings", {{"length", 7.88}, {"diameter", 2.6}}}};
		return RocketModel::fromJson(js);
	}

	const RocketModel model = createModel();
	const double payload_mass = 1E3;
};

TEST_F(TestRocketTwoStages, TestDryMass)
{
	Rocket rocket(model, payload_mass);
	ASSERT_EQ(model.stages.front().dry_mass + model.stages.back().dry_mass, rocket.dryMass());
}

TEST_F(TestRocketTwoStages, TestGrossMass)
{
	Rocket rocket(model, payload_mass);
	ASSERT_EQ(model.stages.front().gross_mass + model.stages.back().gross_mass, rocket.grossMass());
}

TEST_F(TestRocketTwoStages, TestCurrentMassOnConstruction)
{
	Rocket rocket(model, payload_mass);
	ASSERT_EQ(model.stages.front().gross_mass + model.stages.back().gross_mass,
			  rocket.currentMass());
}

TEST_F(TestRocketTwoStages, TestCurrentThrustOnConstruction)
{
	Rocket rocket(model, payload_mass);
	ASSERT_EQ(0 * newtons, rocket.currentThrust());
}

TEST_F(TestRocketTwoStages, TestTotalHeightOnConstruction)
{
	Rocket rocket(model, payload_mass);
	ASSERT_EQ((11.7 + 8.39 + 7.88) * meters, rocket.totalLength());
}

TEST_F(TestRocketTwoStages, TestMaxDiameterOnConstruction)
{
	Rocket rocket(model, payload_mass);
	ASSERT_EQ(3 * meters, rocket.maximumDiameter());
}
