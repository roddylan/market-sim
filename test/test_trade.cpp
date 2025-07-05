// test_trade.cpp
#include <gtest/gtest.h>
#include "Trade.hpp"
#include "Trader.hpp"

class TestTrade : public ::testing::Test {
  Trader maker;
  Trader taker;
  void SetUp() override {
    maker = MMakerTrader("test");
    taker = MTakerTrader("test");
  }

  void TearDown() override {

  }
};

