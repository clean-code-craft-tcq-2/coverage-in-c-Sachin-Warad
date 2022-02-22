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
  
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -20, parameterLimits) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 36, parameterLimits) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 44, parameterLimits) == TOO_HIGH);
}

TEST_CASE("infers alert notification") {
    BatteryCharacter batteryChar;
    AlertTarget alertTarget;
  
    alertTarget = TO_CONTROLLER;
    batteryChar.coolingType = PASSIVE_COOLING;
    checkAndAlert(alertTarget, batteryChar, 36);
    assert(microcontrollerAlertCount == 1);
    assert(emailAlertCount == 0);
  
    alertTarget = TO_CONTROLLER;
    batteryChar.coolingType = PASSIVE_COOLING;
    checkAndAlert(alertTarget, batteryChar, -3);
    assert(microcontrollerAlertCount == 2);
    assert(emailAlertCount == 0);
  
    alertTarget = TO_CONTROLLER;
    batteryChar.coolingType = PASSIVE_COOLING;
    checkAndAlert(alertTarget, batteryChar, 20);
    assert(microcontrollerAlertCount == 2);
    assert(emailAlertCount == 0);
  
    alertTarget = TO_EMAIL;
    batteryChar.coolingType = PASSIVE_COOLING;
    checkAndAlert(alertTarget, batteryChar, 36);
    assert(microcontrollerAlertCount == 2);
    assert(emailAlertCount == 1);
  
    alertTarget = TO_EMAIL;
    batteryChar.coolingType = PASSIVE_COOLING;
    checkAndAlert(alertTarget, batteryChar, -3);
    assert(microcontrollerAlertCount == 2);
    assert(emailAlertCount == 2);
  
    alertTarget = TO_EMAIL;
    batteryChar.coolingType = PASSIVE_COOLING;
    checkAndAlert(alertTarget, batteryChar, 20);
    assert(microcontrollerAlertCount == 2);
    assert(emailAlertCount == 2);
  
    alertTarget = TO_CONTROLLER;
    batteryChar.coolingType = HI_ACTIVE_COOLING;
    checkAndAlert(alertTarget, batteryChar, 46);
    assert(microcontrollerAlertCount == 3);
    assert(emailAlertCount == 2);
  
    alertTarget = TO_CONTROLLER;
    batteryChar.coolingType = HI_ACTIVE_COOLING;
    checkAndAlert(alertTarget, batteryChar, -3);
    assert(microcontrollerAlertCount == 4);
    assert(emailAlertCount == 2);
  
    alertTarget = TO_CONTROLLER;
    batteryChar.coolingType = HI_ACTIVE_COOLING;
    checkAndAlert(alertTarget, batteryChar, 20);
    assert(microcontrollerAlertCount == 4);
    assert(emailAlertCount == 2);
  
    alertTarget = TO_EMAIL;
    batteryChar.coolingType = HI_ACTIVE_COOLING;
    checkAndAlert(alertTarget, batteryChar, 46);
    assert(microcontrollerAlertCount == 4);
    assert(emailAlertCount == 3);
  
    alertTarget = TO_EMAIL;
    batteryChar.coolingType = HI_ACTIVE_COOLING;
    checkAndAlert(alertTarget, batteryChar, -3);
    assert(microcontrollerAlertCount == 4);
    assert(emailAlertCount == 4);
  
    alertTarget = TO_EMAIL;
    batteryChar.coolingType = HI_ACTIVE_COOLING;
    checkAndAlert(alertTarget, batteryChar, 20);
    assert(microcontrollerAlertCount == 4);
    assert(emailAlertCount == 4);
  
    alertTarget = TO_CONTROLLER;
    batteryChar.coolingType = MED_ACTIVE_COOLING;
    checkAndAlert(alertTarget, batteryChar, 41);
    assert(microcontrollerAlertCount == 5);
    assert(emailAlertCount == 4);
  
    alertTarget = TO_CONTROLLER;
    batteryChar.coolingType = MED_ACTIVE_COOLING;
    checkAndAlert(alertTarget, batteryChar, -3);
    assert(microcontrollerAlertCount == 6);
    assert(emailAlertCount == 4);
  
    alertTarget = TO_CONTROLLER;
    batteryChar.coolingType = MED_ACTIVE_COOLING;
    checkAndAlert(alertTarget, batteryChar, 20);
    assert(microcontrollerAlertCount == 6);
    assert(emailAlertCount == 4);
  
    alertTarget = TO_EMAIL;
    batteryChar.coolingType = MED_ACTIVE_COOLING;
    checkAndAlert(alertTarget, batteryChar, 41);
    assert(microcontrollerAlertCount == 6);
    assert(emailAlertCount == 5);
  
    alertTarget = TO_EMAIL;
    batteryChar.coolingType = MED_ACTIVE_COOLING;
    checkAndAlert(alertTarget, batteryChar, -3);
    assert(microcontrollerAlertCount == 6);
    assert(emailAlertCount == 6);
  
    alertTarget = TO_EMAIL;
    batteryChar.coolingType = MED_ACTIVE_COOLING;
    checkAndAlert(alertTarget, batteryChar, 20);
    assert(microcontrollerAlertCount == 6);
    assert(emailAlertCount == 6);
}
