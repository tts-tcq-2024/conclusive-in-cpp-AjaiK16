#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, InfersBreachCorrectly) {
    EXPECT_EQ(inferBreach(25, 20, 30), NORMAL);
    EXPECT_EQ(inferBreach(10, 20, 30), TOO_LOW);
    EXPECT_EQ(inferBreach(35, 20, 30), TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureBreachCorrectly) {
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 40), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 30), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 45), TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite, AlertsControllerCorrectly) {
    // Mock or check the console output
}

TEST(TypeWiseAlertTestSuite, AlertsEmailCorrectly) {
    // Mock or check the console output
}

TEST(TypeWiseAlertTestSuite, SendAlertViaController) {
    // Test sendAlert with TO_CONTROLLER
}

TEST(TypeWiseAlertTestSuite, SendAlertViaEmail) {
    // Test sendAlert with TO_EMAIL
}
