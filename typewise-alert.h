#pragma once

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING,
  MAX_COOLINGTYPE
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH,
  MaxBreachType
} BreachType;

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL,
  MaxAlertTarget
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

typedef struct {
    double lowerLimit;
    double higherLimit;
} Limits;

#define PASSIVE_COOLING_MinLimit  0
#define PASSIVE_COOLING_MaxLimit  35
#define HI_ACTIVE_COOLING_MixLimit  0
#define HI_ACTIVE_COOLING_MaxLimit  45
#define MED_ACTIVE_COOLING_MinLimit 0
#define MED_ACTIVE_COOLING_MaxLimit 40

extern emailAlertCount;
extern microcontrollerAlertCount;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC, Limits parameterLimits[]);

void checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType breachType, void (*fn_ptrAlert)(const char[]));
void sendToEmail(BreachType breachType, void (*fn_ptrAlert)(const char[]));
void printOnConsole(const char msg[]);
