// test_order_book.cpp
// Tests for order book

#include <gtest/gtest.h>
#include "OrderBook.hpp"
#include "Order.hpp"
#include "Trader.hpp"


class OrderBookTest : public ::testing::Test {
protected:
  Trader *maker1;
  Trader *maker2;
  Trader *taker1;
  Trader *taker2;
  void SetUp() override {
    maker1 = new MMakerTrader("1");
    maker2 = new MMakerTrader("2");
    taker1 = new MTakerTrader("1");
    taker2 = new MTakerTrader("2");
  }

  void TearDown() override {
    delete maker1;
    delete maker2;
    delete taker1;
    delete taker2;
  }
};