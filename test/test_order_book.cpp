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

  // pointers to track orders, still copied during insertion
  Order *buy_1;
  Order *buy_2;
  Order *buy_3;
  Order *buy_4;
  Order *buy_5;

  Order *sell_1;
  Order *sell_2;
  Order *sell_3;
  Order *sell_4;
  Order *sell_5;

  void SetUp() override {
    maker1 = new MMakerTrader("1");
    maker2 = new MMakerTrader("2");
    taker1 = new MTakerTrader("1");
    taker2 = new MTakerTrader("2");
    book = OrderBook();
    

    // orderbook ordering
    sell_5 = new Order(fair_price+2, -100, maker1, base_time + Duration(10));
    sell_3 = new Order(fair_price+2, -10, maker2, base_time);
    sell_4 = new Order(fair_price+2, -100, maker1, base_time - Duration(10));
    sell_2 = new Order(fair_price+1, -100, maker2, base_time);
    sell_1 = new Order(fair_price+1, -100, maker2, base_time);
    // fairprice
    buy_1 = new Order(fair_price-1, 100, maker1, base_time);
    buy_2 = new Order(fair_price-1, 100, maker2, base_time);
    buy_4 = new Order(fair_price-2, 100, maker1, base_time - Duration(10));
    buy_3 = new Order(fair_price-2, 10, maker2, base_time);
    buy_5 = new Order(fair_price-2, 100, maker2, base_time + Duration(10));
    
    book.insert(*buy_1);
    book.insert(*buy_2);
    book.insert(*buy_3);
    book.insert(*buy_4);
    book.insert(*buy_5);

    book.insert(*sell_1);
    book.insert(*sell_2);
    book.insert(*sell_3);
    book.insert(*sell_4);
    book.insert(*sell_5);
  }

  void TearDown() override {
    delete maker1;
    delete maker2;
    delete taker1;
    delete taker2;

    delete buy_1;
    delete buy_2;
    delete buy_3;
    delete buy_4;
    delete buy_5;

    delete sell_1;
    delete sell_2;
    delete sell_3;
    delete sell_4;
    delete sell_5;
  }
};

TEST_F(OrderBookTest, BuyExecution) {
  EXPECT_EQ(book.get_buy_orders().size(), 5);
  EXPECT_EQ(book.get_sell_orders().size(), 5);
  
  EXPECT_FLOAT_EQ(book.get_buy_orders().top()->get_price(), buy_1->get_price());
  auto top = *book.get_buy_orders().top();
  EXPECT_TRUE(top == *buy_1 || top == *buy_2);
  
  Order taker_sell1(fair_price-2, -150, taker1);
  book.match(taker_sell1);
  EXPECT_EQ(book.get_buy_orders().size(), 4);
  EXPECT_EQ(book.get_sell_orders().size(), 5);
  EXPECT_EQ(book.get_buy_orders().top()->get_price(), buy_2->get_price());
  EXPECT_EQ(book.get_buy_orders().top()->get_volume(), 50);
  
  Order taker_sell2(fair_price-2, -100, taker1);
  book.match(taker_sell2);
  EXPECT_EQ(book.get_buy_orders().size(), 3);
  EXPECT_EQ(book.get_sell_orders().size(), 5);
  EXPECT_EQ(book.get_buy_orders().top()->get_price(), buy_4->get_price());
  EXPECT_EQ(book.get_buy_orders().top()->get_volume(), 50);
  EXPECT_EQ(book.get_buy_orders().top()->get_trader(), buy_4->get_trader());
  EXPECT_EQ(book.get_buy_orders().top()->get_time(), buy_4->get_time());
  
  Order taker_sell3(fair_price-2, -200, taker1);
  book.match(taker_sell3);
  EXPECT_EQ(book.get_buy_orders().size(), 0);
  EXPECT_EQ(book.get_sell_orders().size(), 5);
  




}
