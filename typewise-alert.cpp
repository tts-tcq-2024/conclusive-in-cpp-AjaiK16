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

void sendAlert(AlertTarget alertTarget, BreachType breachType) {
    switch (alertTarget) {
        case TO_CONTROLLER:
            alertViaController(breachType);
            break;
        case TO_EMAIL:
            alertViaEmail(breachType);
            break;
    }
}

void alertViaController(BreachType breachType) {
    const unsigned short header = 0xfeed;
    printf("%x : %x\n", header, breachType);
}

void alertViaEmail(BreachType breachType) {
    const char* recepient = "a.b@c.com";
    const char* message = breachType == TOO_LOW ? 
                          "Hi, the temperature is too low\n" : 
                          "Hi, the temperature is too high\n";
    printf("To: %s\n%s", recepient, message);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
    sendAlert(alertTarget, breachType);
}
