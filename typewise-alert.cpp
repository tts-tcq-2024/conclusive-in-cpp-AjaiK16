#include "typewise-alert.h"
#include <stdio.h>
#include <map>

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
    static const std::map<CoolingType, int> coolingLimits = {
        {PASSIVE_COOLING, 35},
        {HI_ACTIVE_COOLING, 45},
        {MED_ACTIVE_COOLING, 40}
    };
    
    auto it = coolingLimits.find(coolingType);
    if (it != coolingLimits.end()) {
        return it->second;
    }
    return 0; // Default case, should never happen
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
