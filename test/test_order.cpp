// test_order.cpp
// test orders 
#include <gtest/gtest.h>
#include "Order.hpp"
#include "Trader.hpp"
#include "OrderUtils.hpp"
#include <memory>
#include <chrono>

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
  EXPECT_EQ(test_buy_order_m->get_trader().get_name(), std::string("maker_test"));
  EXPECT_EQ(test_sell_order_m->get_trader().get_name(), std::string("maker_test"));
}

TEST_F(OrderTest, OrderComparisonTest) {
  using Duration = std::chrono::nanoseconds;
  using Clock = std::chrono::steady_clock;
  
  OrderUtils::BuyOrderCompare buy_compare;
  OrderUtils::SellOrderCompare sell_compare;
  auto current_time = std::chrono::steady_clock::now();
  auto later_time = std::chrono::time_point<Clock>(Duration(10000));
  auto earlier_time = std::chrono::time_point<Clock>(Duration(9000));

  float high_price{101}, low_price{99}, f_price{100};
  int high_vol{150}, vol{100};

  // buy comparisons
  auto buy = std::make_shared<Order>(100., 100, maker, Duration(1000));
}