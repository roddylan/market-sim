// test_trade.cpp
#include <gtest/gtest.h>
#include <stdexcept>
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

TEST_F(TestTrade, Constructor) {
  auto ptr_maker = &maker;
  auto ptr_taker = &taker;
  EXPECT_THROW(Trade(maker, taker, -10), std::invalid_argument);
  EXPECT_THROW(Trade(ptr_maker, ptr_taker, -10), std::invalid_argument);
  EXPECT_THROW(Trade(maker, taker, 0), std::invalid_argument);
  EXPECT_THROW(Trade(ptr_maker, ptr_taker, 0), std::invalid_argument);
  Trade ptr_construct(ptr_maker, ptr_taker, 100);
  Trade ref_construct(maker, taker, 100);
  Trade copy_ptr(ptr_construct);
  Trade copy_ref(ref_construct);

  EXPECT_EQ(ptr_construct.maker, copy_ptr.maker);
  EXPECT_EQ(ptr_construct.taker, copy_ptr.taker);
  EXPECT_EQ(ref_construct.maker, copy_ref.maker);
  EXPECT_EQ(ref_construct.taker, copy_ref.taker);
  
  EXPECT_EQ(ptr_construct.price, copy_ptr.price);
  EXPECT_EQ(ref_construct.price, copy_ref.price);
  

}