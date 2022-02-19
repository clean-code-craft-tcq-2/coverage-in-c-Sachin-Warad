#include "typewise-alert.h"
#include <stdio.h>

Limits parameterLimits[MAX_COOLING] = {
  {0,35},
  {0,45},
  {0,40}
};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC, Limits parameterLimits[]) {
  int lowerLimit = parameterLimits[coolingType].lowerLimit;
  int upperLimit = parameterLimits[coolingType].higherLimit;
//   switch(coolingType) {
//     case PASSIVE_COOLING:
//       lowerLimit = 0;
//       upperLimit = 35;
//       break;
//     case HI_ACTIVE_COOLING:
//       lowerLimit = 0;
//       upperLimit = 45;
//       break;
//     case MED_ACTIVE_COOLING:
//       lowerLimit = 0;
//       upperLimit = 40;
//       break;
//   }
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC, parameterLimits
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
      break;
  }
}
