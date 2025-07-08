// test_market_data.cpp
#include "gtest/gtest.h"
#include "MarketData.hpp"
#include "Trader.hpp"

class MarketDataTest : public ::testing::Test {
protected:
  MarketData data;
  Trader *maker;
  Trader *taker;
  void SetUp() override {
    maker = new MMakerTrader("test");
    taker = new MTakerTrader("test");
    return;
  }

  void TearDown() override {
    delete maker;
    delete taker;
    return;
  }
};

TEST_F(MarketDataTest, TestEmpty) {
  EXPECT_TRUE(data.get_trade_history().empty());
  EXPECT_FLOAT_EQ(data.get_last_price(), 0);
  EXPECT_EQ(data.get_last_trade(), nullptr);
}