// test_order.cpp
// test orders 
#include <gtest/gtest.h>
#include "Order.hpp"
#include "Trader.hpp"

class OrderTest : public ::testing::Test {
protected:
  Trader *maker;
  Trader *taker;
  Order *test_buy_order_m;
  Order *test_sell_order_m;
  
  void SetUp() override {
    maker = new MMakerTrader("test");
    taker = new MTakerTrader("test");
    test_buy_order_m = new Order(49.5, 100, maker);
    test_sell_order_m = new Order(50.5, -100, maker);
  }

  void TearDown() override {
    delete maker;
    delete taker;

    delete test_buy_order_m;
    delete test_sell_order_m;
  }
};


TEST_F(OrderTest, OrderGettersTest) {
  
}