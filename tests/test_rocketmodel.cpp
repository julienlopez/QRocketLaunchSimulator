#include "rocketmodel.hpp"

#include <stdexcept>

#include <gtest/gtest.h>

TEST(TestRocketModel, TestParsingRocketWithNoStages)
{
	const std::string name = "test";
	std::stringstream ss;
	ss << R"({ "name": ")" + name + R"(", "stages": [] } ")";
	auto rocket = RocketModel::fromJson(ss);
	EXPECT_EQ(name, rocket.name);
	EXPECT_TRUE(rocket.stages.empty());
}

TEST(TestRocketModel, TestParsingRocketWithoutName)
{
	std::stringstream ss;
	ss << R"({ "stages": [] } ")";
	ASSERT_THROW(RocketModel::fromJson(ss), std::runtime_error);
}

TEST(TestRocketModel, TestParsingRocketInvalidName)
{
	std::stringstream ss;
	ss << R"({ "name": 2 , "stages": [] } ")";
	ASSERT_THROW(RocketModel::fromJson(ss), std::runtime_error);
}

TEST(TestRocketModel, TestParsingRocketWithoutStages)
{
	std::stringstream ss;
	ss << R"({ "name": "test" }")";
	ASSERT_THROW(RocketModel::fromJson(ss), std::runtime_error);
}

TEST(TestRocketModel, TestParsingRocketInvalidStages)
{
	std::stringstream ss;
	ss << R"({ "name": "test", "stages": "error" } ")";
	ASSERT_THROW(RocketModel::fromJson(ss), std::runtime_error);
}

TEST(TestRocketModel, TestParsingRocketWithTwoStages)
{
	const std::string name = "test";
	std::stringstream ss;
	ss << R"({ "name": ")" + name + R"(", "stages": [
                                {
                                    "name": "Z9",
                                    "length" : 4.12,
                                    "diameter" : 1.9,
                                    "dry_mass" : 1315,
                                    "gross_mass" : 11815,
                                    "thrust" : 260000,
                                    "isp" : 296,
                                    "burn_time" : 120,
                                    "fuel" : "solid"
                                },
                                {
                                    "name": "AVUM",
                                    "length" : 1.7,
                                    "diameter" : 2.31,
                                    "dry_mass" : 147,
                                    "gross_mass" : 697,
                                    "thrust" : 2420,
                                    "isp" : 315.5,
                                    "burn_time" : 6672,
                                    "fuel" : "UDMH/N204"
                                }] } ")";
	auto rocket = RocketModel::fromJson(ss);
	EXPECT_EQ(name, rocket.name);
	ASSERT_EQ(2, rocket.stages.size());

	const auto s1 = rocket.stages.front();
	EXPECT_EQ("Z9", s1.name);
	EXPECT_EQ(4.12, s1.length);
	EXPECT_EQ(1.9, s1.diameter);
	EXPECT_EQ(1315, s1.dry_mass);
	EXPECT_EQ(11815, s1.gross_mass);
	EXPECT_EQ(260000, s1.thrust);
	EXPECT_EQ(296, s1.isp);
	EXPECT_EQ(120, s1.burn_time);
	EXPECT_EQ("solid", s1.fuel);

	const auto s2 = rocket.stages.back();
	EXPECT_EQ("AVUM", s2.name);
	EXPECT_EQ(1.7, s2.length);
	EXPECT_EQ(2.31, s2.diameter);
	EXPECT_EQ(147, s2.dry_mass);
	EXPECT_EQ(697, s2.gross_mass);
	EXPECT_EQ(2420, s2.thrust);
	EXPECT_EQ(315.5, s2.isp);
	EXPECT_EQ(6672, s2.burn_time);
	EXPECT_EQ("UDMH/N204", s2.fuel);
}

TEST(TestRocketModel, TestParsingRocketStagesInvalidType)
{
	std::stringstream ss;
	ss << R"({ "name": "test", "stages": [ "error" ] } ")";
	ASSERT_THROW(RocketModel::fromJson(ss), std::runtime_error);
}

TEST(TestRocketModel, TestParsingRocketStagesNumberInvalidType)
{
	std::stringstream ss;
	ss << R"({ "name": "test", "stages": [ {
          "name": "AVUM",
          "length" : 1.7,
          "diameter" : 2.31,
          "dry_mass" : 147,
          "gross_mass" : "error",
          "thrust" : 2420,
          "isp" : 315.5,
          "burn_time" : 6672,
          "fuel" : "UDMH/N204"
      } ] } ")";
	ASSERT_THROW(RocketModel::fromJson(ss), std::runtime_error);
}

TEST(TestRocketModel, TestParsingRocketStagesNumberMissing)
{
	std::stringstream ss;
	ss << R"({ "name": "test", "stages": [ {
          "name": "AVUM",
          "length" : 1.7,
          "diameter" : 2.31,
          "dry_mass" : 147,
          "thrust" : 2420,
          "isp" : 315.5,
          "burn_time" : 6672,
          "fuel" : "UDMH/N204"
      } ] } ")";
	ASSERT_THROW(RocketModel::fromJson(ss), std::runtime_error);
}
