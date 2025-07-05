// test_order_book.cpp
// Tests for order book

#include <gtest/gtest.h>
#include "OrderBook.hpp"
#include "Order.hpp"
#include "Trader.hpp"

using Duration = std::chrono::nanoseconds;
using Clock = std::chrono::steady_clock;
using Time = std::chrono::time_point<std::chrono::steady_clock>;

const float fair_price{100};
const int default_abs_vol{100};
const Time base_time = std::chrono::time_point<Clock>(Duration(10000));

class OrderBookTest : public ::testing::Test {
protected:
  Trader *maker1;
  Trader *maker2;
  Trader *taker1;
  Trader *taker2;
  OrderBook book;

  void SetUp() override {
    maker1 = new MMakerTrader("1");
    maker2 = new MMakerTrader("2");
    taker1 = new MTakerTrader("1");
    taker2 = new MTakerTrader("2");
    book = OrderBook();
  }

  void TearDown() override {
    delete maker1;
    delete maker2;
    delete taker1;
    delete taker2;
  }
};


TEST_F(OrderBookTest, BuyInsertion) {
  Order buy_1(fair_price+1, 100, maker1, base_time);
  Order buy_2(fair_price+0.5, 100, maker1, base_time);
  Order buy_3(fair_price+1.5, 10, maker1, base_time);
  Order buy_4(fair_price+1.5, 100, maker1, base_time - Duration(10));
  Order buy_5(fair_price+1.5, 100, maker1, base_time + Duration(10));

  book.insert(buy_1);
  EXPECT_EQ(book.get_buy_orders().size(), 1);
  EXPECT_EQ(*book.get_buy_orders().top(), buy_1);
  book.insert(buy_2);
  EXPECT_EQ(book.get_buy_orders().size(), 2);
  EXPECT_EQ(*book.get_buy_orders().top(), buy_1);
  book.insert(buy_3);
  EXPECT_EQ(book.get_buy_orders().size(), 3);
  EXPECT_EQ(*book.get_buy_orders().top(), buy_3);
  book.insert(buy_4);
  EXPECT_EQ(book.get_buy_orders().size(), 4);
  EXPECT_EQ(*book.get_buy_orders().top(), buy_4);
  book.insert(buy_5);
  EXPECT_EQ(book.get_buy_orders().size(), 5);
  EXPECT_EQ(*book.get_buy_orders().top(), buy_4);
}

TEST_F(OrderBookTest, SellInsertion) {
  Order sell_1(fair_price-1, -100, maker1, base_time);
  Order sell_2(fair_price-0.5, -100, maker1, base_time);
  Order sell_3(fair_price-1.5, -10, maker1, base_time);
  Order sell_4(fair_price-1.5, -100, maker1, base_time - Duration(10));
  Order sell_5(fair_price-1.5, -100, maker1, base_time + Duration(10));

  book.insert(sell_1);
  EXPECT_EQ(book.get_sell_orders().size(), 1);
  EXPECT_EQ(*book.get_sell_orders().top(), sell_1);
  book.insert(sell_2);
  EXPECT_EQ(book.get_sell_orders().size(), 2);
  EXPECT_EQ(*book.get_sell_orders().top(), sell_1);
  book.insert(sell_3);
  EXPECT_EQ(book.get_sell_orders().size(), 3);
  EXPECT_EQ(*book.get_sell_orders().top(), sell_3);
  book.insert(sell_4);
  EXPECT_EQ(book.get_sell_orders().size(), 4);
  EXPECT_EQ(*book.get_sell_orders().top(), sell_4);
  book.insert(sell_5);
  EXPECT_EQ(book.get_sell_orders().size(), 5);
  EXPECT_EQ(*book.get_sell_orders().top(), sell_4);
}

