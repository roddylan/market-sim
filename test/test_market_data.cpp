// test_market_data.cpp
#include "gtest/gtest.h"
#include "MarketData.hpp"
#include "Trader.hpp"

class MarketDataTest : public ::testing::Test {
protected:
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
  MarketData data;
  EXPECT_TRUE(data.get_trade_history().empty());
  EXPECT_FLOAT_EQ(data.get_last_price(), 0);
  EXPECT_EQ(data.get_last_trade(), nullptr);
  EXPECT_TRUE(data.get_prices().empty());
}

TEST_F(MarketDataTest, TestAddTrade) {
  MarketData data;
  EXPECT_TRUE(data.get_trade_history().empty());
  EXPECT_FLOAT_EQ(data.get_last_price(), 0);
  EXPECT_EQ(data.get_last_trade(), nullptr);
  EXPECT_TRUE(data.get_prices().empty());
  
  data.add_trade(*maker, *taker, 150);
  EXPECT_EQ(data.get_trade_history().size(), 1);
  EXPECT_FLOAT_EQ(data.get_last_price(), 150);
  EXPECT_NE(data.get_last_trade(), nullptr);
  EXPECT_EQ(data.get_prices().size(), 1);

  EXPECT_FLOAT_EQ(data.get_last_trade()->price, 150);
  EXPECT_FLOAT_EQ(data.get_last_trade()->price, data.get_last_price());
  EXPECT_EQ(data.get_last_trade()->maker, maker);
  EXPECT_EQ(data.get_last_trade()->taker, taker);
  
  EXPECT_DEATH(data.add_trade(*maker, *taker, 0), ".*");
  EXPECT_DEATH(data.add_trade(*maker, *taker, -1), ".*");

}
TEST_F(MarketDataTest, TestAddTrades) {
  MarketData data;
  EXPECT_TRUE(data.get_trade_history().empty());
  EXPECT_FLOAT_EQ(data.get_last_price(), 0);
  EXPECT_EQ(data.get_last_trade(), nullptr);
  EXPECT_TRUE(data.get_prices().empty());
  
  size_t n_it = 10;
  for (size_t i = 0; i < n_it; ++i) {
    data.add_trade(*maker, *taker, 150 + i);
    EXPECT_EQ(data.get_trade_history().size(), i + 1);
    EXPECT_EQ(data.get_prices().size(), i + 1);
    EXPECT_FLOAT_EQ(data.get_last_trade()->price, 150 + i);
    EXPECT_FLOAT_EQ(data.get_last_price(), 150 + i);
    EXPECT_FLOAT_EQ(data.get_last_trade()->price, data.get_last_price());
  }
}