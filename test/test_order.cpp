// test_order.cpp
// test orders 
#include <gtest/gtest.h>
#include "Order.hpp"
#include "Trader.hpp"
#include "OrderUtils.hpp"
#include <memory>
#include <chrono>
#include "MarketUtils.hpp"

using Duration = MarketUtils::Duration;
using Clock = MarketUtils::Clock;
using Time = MarketUtils::Time;

const float f_price = 100;
const int abs_vol = 100;
const Time base_time = std::chrono::time_point<Clock>(Duration(10000));
const Time early_time = base_time - Duration(100);
const Time late_time = base_time + Duration(100);

class OrderTest : public ::testing::Test {
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
  }
};

// test getters 
TEST_F(OrderTest, OrderGettersTest) {
  Order buy_order_maker(f_price, abs_vol, maker);
  Order sell_order_maker(f_price, -abs_vol, maker);

  EXPECT_EQ(buy_order_maker.get_trader().get_name(), std::string("maker_test"));
  EXPECT_EQ(sell_order_maker.get_trader().get_name(), std::string("maker_test"));

  EXPECT_EQ(buy_order_maker.get_price(), f_price);
  EXPECT_EQ(sell_order_maker.get_price(), f_price);

  EXPECT_TRUE(buy_order_maker.get_volume() > 0);
  EXPECT_TRUE(sell_order_maker.get_volume() < 0);
  EXPECT_EQ(buy_order_maker.get_volume(), abs_vol);
  EXPECT_EQ(sell_order_maker.get_volume(), -abs_vol);
}

TEST_F(OrderTest, OrderVolumeUpdateTest) {
  Order buy_order_maker(f_price, abs_vol, maker);
  Order sell_order_maker(f_price, -abs_vol, maker);

  buy_order_maker.update_volume(100);
  sell_order_maker.update_volume(100);
  EXPECT_EQ(buy_order_maker.get_volume(), abs_vol + 100);
  EXPECT_EQ(sell_order_maker.get_volume(), -abs_vol + 100);

}

TEST_F(OrderTest, BuyOrderComparisonTestPQ) {
  // true if need to swap
  OrderUtils::BuyOrderComparePQ buy_compare; // buy -> best bid (highest), earliest time
  auto current_time = std::chrono::steady_clock::now();
  auto later_time = std::chrono::time_point<Clock>(Duration(10000));
  auto earlier_time = std::chrono::time_point<Clock>(Duration(9000));

  float high_price{f_price+1}, low_price{f_price-1};
  int high_vol{abs_vol+50}, vol{abs_vol};

  // buy comparisons
  auto high_buy = std::make_shared<Order>(high_price, vol, maker, later_time);
  auto low_buy = std::make_shared<Order>(low_price, high_vol, maker, earlier_time);
  
  // different prices, but best comes later
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


TEST_F(OrderTest, SellOrderComparisonTestPQ) {
  // true if need to swap
  OrderUtils::SellOrderComparePQ sell_compare; // sell -> best ask (lowest), earliest time
  auto current_time = std::chrono::steady_clock::now();
  auto later_time = std::chrono::time_point<Clock>(Duration(10000));
  auto earlier_time = std::chrono::time_point<Clock>(Duration(9000));

  float high_price{f_price+1}, low_price{f_price-1};
  int high_vol{-abs_vol - 50}, vol{-abs_vol};

  // buy comparisons
  auto high_sell = std::make_shared<Order>(high_price, vol, maker, earlier_time);
  auto low_sell = std::make_shared<Order>(low_price, high_vol, maker, later_time);
  
  // different prices, but best comes later
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

TEST_F(OrderTest, BuyOrderComparisonTest) {
  // false if need to swap, true if ordering correct
  OrderUtils::BuyOrderCompare buy_compare; // buy -> best bid (highest), earliest time
  auto current_time = std::chrono::steady_clock::now();
  auto later_time = std::chrono::time_point<Clock>(Duration(10000));
  auto earlier_time = std::chrono::time_point<Clock>(Duration(9000));

  float high_price{f_price+1}, low_price{f_price-1};
  int high_vol{abs_vol+50}, vol{abs_vol};

  // buy comparisons
  auto high_buy = std::make_shared<Order>(high_price, vol, maker, later_time);
  auto low_buy = std::make_shared<Order>(low_price, high_vol, maker, earlier_time);
  
  // different prices, but best comes later
  EXPECT_TRUE(buy_compare(high_buy, low_buy));
  EXPECT_FALSE(buy_compare(low_buy, high_buy));
  EXPECT_TRUE(buy_compare(high_buy, high_buy));
  EXPECT_TRUE(buy_compare(low_buy, low_buy));

  // equal prices, different time
  auto buy_early = std::make_shared<Order>(f_price, vol, maker, earlier_time);
  auto buy_late = std::make_shared<Order>(f_price, high_vol, maker, later_time);
  EXPECT_TRUE(buy_compare(buy_early, buy_late));
  EXPECT_FALSE(buy_compare(buy_late, buy_early));

  // equal prices, equal time, diff vol
  auto same_buy1 = std::make_shared<Order>(f_price, vol, maker, current_time);
  auto same_buy2 = std::make_shared<Order>(f_price, high_vol, maker, current_time);
  EXPECT_TRUE(buy_compare(same_buy1, same_buy2));
  EXPECT_TRUE(buy_compare(same_buy2, same_buy1));

}


TEST_F(OrderTest, SellOrderComparisonTest) {
  // false if need to swap, true if ordering correct
  OrderUtils::SellOrderCompare sell_compare; // sell -> best ask (lowest), earliest time
  auto current_time = std::chrono::steady_clock::now();
  auto later_time = std::chrono::time_point<Clock>(Duration(10000));
  auto earlier_time = std::chrono::time_point<Clock>(Duration(9000));

  float high_price{f_price+1}, low_price{f_price-1};
  int high_vol{-abs_vol - 50}, vol{-abs_vol};

  // buy comparisons
  auto high_sell = std::make_shared<Order>(high_price, vol, maker, earlier_time);
  auto low_sell = std::make_shared<Order>(low_price, high_vol, maker, later_time);
  
  // different prices, but best comes later
  EXPECT_TRUE(sell_compare(low_sell, high_sell));
  EXPECT_FALSE(sell_compare(high_sell, low_sell));
  EXPECT_TRUE(sell_compare(high_sell, high_sell));
  EXPECT_TRUE(sell_compare(low_sell, low_sell));

  // equal prices, different time
  auto sell_early = std::make_shared<Order>(f_price, vol, maker, earlier_time);
  auto sell_late = std::make_shared<Order>(f_price, high_vol, maker, later_time);
  EXPECT_TRUE(sell_compare(sell_early, sell_late));
  EXPECT_FALSE(sell_compare(sell_late, sell_early));

  // equal prices, equal time, diff vol
  auto same_sell1 = std::make_shared<Order>(f_price, vol, maker, current_time);
  auto same_sell2 = std::make_shared<Order>(f_price, high_vol, maker, current_time);
  EXPECT_TRUE(sell_compare(same_sell1, same_sell2));
  EXPECT_TRUE(sell_compare(same_sell2, same_sell1));

}

TEST_F(OrderTest, EqualityTest) {
  // identical orders
  Order order1(f_price, abs_vol, maker, base_time);
  Order order2(f_price, abs_vol, maker, base_time);

  EXPECT_EQ(order1, Order(order1));

  EXPECT_EQ(order1, order2);
  EXPECT_EQ(order1, order1);
  EXPECT_EQ(order2, order2);

  // different time only
  Order order3(f_price, abs_vol, maker);
  EXPECT_NE(order1, order3);

  // different trader only
  Order order4(f_price, abs_vol, taker, base_time);
  EXPECT_NE(order1, order4);

  // different volume only (sell vs buy)
  Order order5(f_price, -abs_vol, maker, base_time);
  EXPECT_NE(order1, order5);

  // different price only
  Order order6(f_price+1, abs_vol, maker, base_time);
  EXPECT_NE(order1, order6);

  // different everything
  Order order7(f_price+100, abs_vol+10, taker);
  EXPECT_NE(order1, order7);
}

