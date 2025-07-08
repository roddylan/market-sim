// test_trader.cpp
// test trader 
#include <gtest/gtest.h>
#include "Trader.hpp"
#include <string>

class TraderTest : public ::testing::Test {
protected:
  Trader *trader;
  Trader *maker;
  Trader *taker;
  
  void SetUp() override {
    trader = new Trader("test");
    maker = new MMakerTrader("test");
    taker = new MTakerTrader("test");
  }

  void TearDown() override {
    delete trader;
    delete maker;
    delete taker;
  }
};


TEST_F(TraderTest, TraderNameTest) {
  EXPECT_EQ(trader->get_name(), std::string("test"));
  EXPECT_EQ(maker->get_name(), std::string("maker_test"));
  EXPECT_EQ(taker->get_name(), std::string("taker_test"));
  
  trader->set_name("test2");
  maker->set_name("test2");
  taker->set_name("test2");
  EXPECT_EQ(trader->get_name(), std::string("test2"));
  EXPECT_EQ(maker->get_name(), std::string("test2"));
  EXPECT_EQ(taker->get_name(), std::string("test2"));
}

// TODO: strategy
// TODO: tests for make_order, fair_price