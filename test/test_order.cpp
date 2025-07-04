// test_order.cpp
// test orders 
#include <gtest/gtest.h>
#include "Order.hpp"
#include "Trader.hpp"

class OrderTest : public ::testing::Test {
  void SetUp() override {
    MMakerTrader maker("test");
    MTakerTrader taker("test");
    Order buy_order(49.5, 100, maker);
    Order sell_order(50.5, -100, maker);
  }
};