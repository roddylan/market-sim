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

TEST_F(OrderTest, BuyOrderComparisonTest) {
  using Duration = std::chrono::nanoseconds;
  using Clock = std::chrono::steady_clock;
  
  // true if need to swap
  OrderUtils::BuyOrderCompare buy_compare; // buy -> best bid (highest), earliest time
  auto current_time = std::chrono::steady_clock::now();
  auto later_time = std::chrono::time_point<Clock>(Duration(10000));
  auto earlier_time = std::chrono::time_point<Clock>(Duration(9000));

  float high_price{101}, low_price{99}, f_price{100};
  int high_vol{150}, vol{100};

  // buy comparisons
  auto high_buy = std::make_shared<Order>(high_price, vol, maker, later_time);
  auto low_buy = std::make_shared<Order>(low_price, high_vol, maker, earlier_time);
  
  // different prices
  EXPECT_FALSE(buy_compare(high_buy, low_buy));
  EXPECT_TRUE(buy_compare(low_buy, high_buy));
  EXPECT_FALSE(buy_compare(high_buy, high_buy));
  EXPECT_FALSE(buy_compare(low_buy, low_buy));

  // equal prices, different time
  auto buy_early = std::make_shared<Order>(f_price, vol, maker, earlier_time);
  auto buy_late = std::make_shared<Order>(f_price, high_vol, maker, later_time);
  EXPECT_FALSE(buy_compare(buy_early, buy_late));
  EXPECT_TRUE(buy_compare(buy_late, buy_early));

  // equal prices, equal time, diff vol
  auto same_buy1 = std::make_shared<Order>(f_price, vol, maker, current_time);
  auto same_buy2 = std::make_shared<Order>(f_price, high_vol, maker, current_time);
  EXPECT_FALSE(buy_compare(same_buy1, same_buy2));
  EXPECT_FALSE(buy_compare(same_buy2, same_buy1));

}


TEST_F(OrderTest, SellOrderComparisonTest) {
  using Duration = std::chrono::nanoseconds;
  using Clock = std::chrono::steady_clock;
  
  // true if need to swap
  OrderUtils::SellOrderCompare sell_compare; // sell -> best ask (lowest), earliest time
  auto current_time = std::chrono::steady_clock::now();
  auto later_time = std::chrono::time_point<Clock>(Duration(10000));
  auto earlier_time = std::chrono::time_point<Clock>(Duration(9000));

  float high_price{101}, low_price{99}, f_price{100};
  int high_vol{-150}, vol{-100};

  // buy comparisons
  auto high_sell = std::make_shared<Order>(high_price, vol, maker, later_time);
  auto low_sell = std::make_shared<Order>(low_price, high_vol, maker, earlier_time);
  
  // different prices
  EXPECT_FALSE(sell_compare(low_sell, high_sell));
  EXPECT_TRUE(sell_compare(high_sell, low_sell));
  EXPECT_FALSE(sell_compare(high_sell, high_sell));
  EXPECT_FALSE(sell_compare(low_sell, low_sell));

  // equal prices, different time
  auto sell_early = std::make_shared<Order>(f_price, vol, maker, earlier_time);
  auto sell_late = std::make_shared<Order>(f_price, high_vol, maker, later_time);
  EXPECT_FALSE(sell_compare(sell_early, sell_late));
  EXPECT_TRUE(sell_compare(sell_late, sell_early));

  // equal prices, equal time, diff vol
  auto same_sell1 = std::make_shared<Order>(f_price, vol, maker, current_time);
  auto same_sell2 = std::make_shared<Order>(f_price, high_vol, maker, current_time);
  EXPECT_FALSE(sell_compare(same_sell1, same_sell2));
  EXPECT_FALSE(sell_compare(same_sell2, same_sell1));

}

