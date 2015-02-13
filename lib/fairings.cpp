#include "fairings.hpp"

#include "utils/json_helper.hpp"

using nlohmann::json;

Fairings Fairings::fromJson(const json& js)
{
	if(js.type() != json::value_t::object)
		throw std::runtime_error("invalid json object, invalid fairings");

	return {utils::json_helper::getAndCheckNumber<double>(js, "length"),
			utils::json_helper::getAndCheckNumber<double>(js, "diameter")};
}
