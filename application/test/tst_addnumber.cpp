
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include "manager/AppManager.h"
using namespace testing;

TEST(AppManagerTest, AddNumber)
{
    AppManager testAdd;
    EXPECT_EQ(testAdd.addNumber(3,4), 5);
}
