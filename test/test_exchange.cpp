// test_exchange.cpp
#include "gtest/gtest.h"
#include "Exchange.hpp"

class ExchangeTest : public ::testing::Test {
protected:
  Exchange exchange;
  void SetUp() override {
    return;
  }

  void TearDown() override {
    return;
  }
};


TEST_F(ExchangeTest, DefaultInitialization) {
  EXPECT_EQ(exchange.get_starting_price(), 100);
}