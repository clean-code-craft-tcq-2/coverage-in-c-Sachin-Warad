#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(31, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
}

TEST_CASE("infers breach based on cooling type") {
  Limits parameterLimits[MAX_COOLINGTYPE] = {
    {PASSIVE_COOLING_MinLimit,PASSIVE_COOLING_MaxLimit},
    {HI_ACTIVE_COOLING_MixLimit,HI_ACTIVE_COOLING_MaxLimit},
    {MED_ACTIVE_COOLING_MinLimit,MED_ACTIVE_COOLING_MaxLimit}
  };
  
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -1, parameterLimits) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 20, parameterLimits) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 40, parameterLimits) == TOO_HIGH);
  
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -10, parameterLimits) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 36, parameterLimits) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50, parameterLimits) == TOO_HIGH);
  
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -10, parameterLimits) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 43, parameterLimits) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 44, parameterLimits) == TOO_HIGH);
}
