// test_trade.cpp
#include <gtest/gtest.h>
#include "Trade.hpp"
#include "Trader.hpp"

class TestTrade : public ::testing::Test {
protected:
  Trader maker;
  Trader taker;
  void SetUp() override {
    maker = MMakerTrader("test");
    taker = MTakerTrader("test");
  }

  void TearDown() override {

  }
};

TEST_F(TestTrade, PointerConstructor) {
  auto ptr_maker = &maker;
  auto ptr_taker = &taker;

  Trade trade(maker, taker, 100);
  

}