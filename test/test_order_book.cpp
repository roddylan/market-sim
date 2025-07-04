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
  Order buy_1(fair_price+0.5, 100, maker1);
}