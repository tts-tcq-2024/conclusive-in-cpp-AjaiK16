#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
    if (value < lowerLimit) {
        return TOO_LOW;
    }
    if (value > upperLimit) {
        return TOO_HIGH;
    }
    return NORMAL;
}

int getUpperLimit(CoolingType coolingType) {
    switch (coolingType) {
        case PASSIVE_COOLING: return 35;
        case HI_ACTIVE_COOLING: return 45;
        case MED_ACTIVE_COOLING: return 40;
        default: return 0; // This should never happen
    }
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    return inferBreach(temperatureInC, 0, getUpperLimit(coolingType));
}

void alertViaController(BreachType breachType) {
    const unsigned short header = 0xfeed;
    printf("%x : %x\n", header, breachType);
}

void alertViaEmail(BreachType breachType) {
    const char* recepient = "a.b@c.com";
    if (breachType == TOO_LOW) {
        printf("To: %s\nHi, the temperature is too low\n", recepient);
    } else if (breachType == TOO_HIGH) {
        printf("To: %s\nHi, the temperature is too high\n", recepient);
    }
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

    if (alertTarget == TO_CONTROLLER) {
        alertViaController(breachType);
    } else if (alertTarget == TO_EMAIL) {
        alertViaEmail(breachType);
    }
}
