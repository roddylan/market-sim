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

TEST_F(TestTrade, PointerRefConstructorTraders) {
  auto ptr_maker = &maker;
  auto ptr_taker = &taker;

  Trade ptr_construct(ptr_maker, ptr_taker, 100);
  Trade ref_construct(maker, taker, 100);

  EXPECT_EQ(ptr_construct.maker, ref_construct.maker);
  EXPECT_EQ(ptr_construct.taker, ref_construct.taker);



}