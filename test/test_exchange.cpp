// test_exchange.cpp
#include "gtest/gtest.h"
#include "Exchange.hpp"

class ExchangeTest : public ::testing::Test {
protected:
  Exchange exchange;
  void SetUp() override {
    return;
  }

  void TearDown() override {
    return;
  }
};


TEST_F(ExchangeTest, DefaultInitialization) {
  EXPECT_FLOAT_EQ(exchange.get_starting_price(), 100);
  Exchange ex1;
  EXPECT_FLOAT_EQ(ex1.get_starting_price(), 100);
  EXPECT_EQ(ex1.get_book().get_buy_orders().size(), 0);
  EXPECT_EQ(ex1.get_book().get_sell_orders().size(), 0);
}

TEST_F(ExchangeTest, ValueInitialization) {
  Exchange ex1(150);
  EXPECT_FLOAT_EQ(ex1.get_starting_price(), 150);
  EXPECT_EQ(ex1.get_book().get_buy_orders().size(), 0);
  EXPECT_EQ(ex1.get_book().get_sell_orders().size(), 0);

  EXPECT_DEATH(Exchange(0), ".*");
  EXPECT_DEATH(Exchange(-1), ".*");
}

TEST_F(ExchangeTest, StartingPrice) {
  EXPECT_FLOAT_EQ(exchange.get_starting_price(), 100);
  exchange.set_starting_price(1000);
  EXPECT_FLOAT_EQ(exchange.get_starting_price(), 1000);
  EXPECT_DEATH(exchange.set_starting_price(0), ".*");
  EXPECT_DEATH(exchange.set_starting_price(-1), ".*");
}

