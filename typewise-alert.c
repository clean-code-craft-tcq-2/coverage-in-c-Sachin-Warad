#include "typewise-alert.h"
#include <stdio.h>
#include <string.h>

Limits parameterLimits[MAX_COOLINGTYPE] = {
  {PASSIVE_COOLING_MinLimit,PASSIVE_COOLING_MaxLimit},
  {HI_ACTIVE_COOLING_MixLimit,HI_ACTIVE_COOLING_MaxLimit},
  {MED_ACTIVE_COOLING_MinLimit,MED_ACTIVE_COOLING_MaxLimit}
};

const char *msgInput[MaxBreachType] = {"","Hi, the temperature is too low","Hi, the temperature is too high"};

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

  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void printOnConsole(const char msg[]) {
    printf("%s",msg);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  void (*fn_ptrAlert)(const char[]);
  fn_ptrAlert = &printOnConsole;
  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC, parameterLimits
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType, fn_ptrAlert);
      break;
    case TO_EMAIL:
      sendToEmail(breachType, msgInput, fn_ptrAlert);
      break;
  }
}

void sendToController(BreachType breachType, void (*fn_ptrAlert)(const char[])) {
  const unsigned short header = 0xfeed;
//   printf("%x : %x\n", header, breachType);
  char buffer[25];
  sprintf(buffer,"%x : %x\n",header, breachType);
  fn_ptrAlert(buffer);
}

void sendToEmail(BreachType breachType, const char **msgInput, void (*fn_ptrAlert)(const char[])) {
  const char* recepient = "a.b@c.com";
  char recepientMsg[] = "To: ";
  char buffer[100];
  strcat(recepientMsg,recepient);
//   printf("To: %s\n", recepient);
  sprintf(buffer,"%s\n, %s\n",recepientMsg,msgInput[breachType]);
  fn_ptrAlert(buffer);
//   fn_ptrAlert(recepientMsg);
//   char alertMsg = msgInputEmail[breachType];
//   fn_ptrAlert(msgInput[breachType]);
//   switch(breachType) {
//     case TOO_LOW:
//       printf("To: %s\n", recepient);
//       printf("Hi, the temperature is too low\n");
//       break;
//     case TOO_HIGH:
//       printf("To: %s\n", recepient);
//       printf("Hi, the temperature is too high\n");
//       break;
//     case NORMAL:
//       break;
//   }
}
