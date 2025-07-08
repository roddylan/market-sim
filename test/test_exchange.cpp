// test_exchange.cpp
#include "gtest/gtest.h"
#include "Exchange.hpp"
#include "Trader.hpp"

class ExchangeTest : public ::testing::Test {
protected:
  Exchange *exchange;
  void SetUp() override {
    exchange = new Exchange();
    return;
  }

  void TearDown() override {
    delete exchange;
    return;
  }
};


TEST_F(ExchangeTest, DefaultInitialization) {
  EXPECT_FLOAT_EQ(exchange->get_starting_price(), 100);
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
  EXPECT_FLOAT_EQ(exchange->get_starting_price(), 100);
  exchange->set_starting_price(1000);
  EXPECT_FLOAT_EQ(exchange->get_starting_price(), 1000);
  EXPECT_DEATH(exchange->set_starting_price(0), ".*");
  EXPECT_DEATH(exchange->set_starting_price(-1), ".*");
}

TEST_F(ExchangeTest, AddTraderParam) {
  EXPECT_TRUE(exchange->get_makers().empty());
  EXPECT_TRUE(exchange->get_takers().empty());
  auto maker = MMakerTrader("test");
  exchange->add_maker(maker);
  EXPECT_EQ(exchange->get_makers().size(), 1);
  EXPECT_TRUE(exchange->get_takers().empty());
  auto taker = MTakerTrader("test");
  exchange->add_taker(taker);
  EXPECT_EQ(exchange->get_makers().size(), 1);
  EXPECT_EQ(exchange->get_takers().size(), 1);
  
  EXPECT_EQ(*exchange->get_makers().back(), maker);
  EXPECT_EQ(*exchange->get_takers().back(), taker);

}

TEST_F(ExchangeTest, AddTrader) {
  EXPECT_TRUE(exchange->get_makers().empty());
  EXPECT_TRUE(exchange->get_takers().empty());
  exchange->add_maker<MMakerTrader>();
  EXPECT_EQ(exchange->get_makers().size(), 1);
  EXPECT_TRUE(exchange->get_takers().empty());
  exchange->add_taker<MTakerTrader>();
  EXPECT_EQ(exchange->get_makers().size(), 1);
  EXPECT_EQ(exchange->get_takers().size(), 1);
  
  EXPECT_EQ(exchange->get_makers().back()->get_name(), "maker_1");
  EXPECT_EQ(exchange->get_takers().back()->get_name(), "taker_1");
  
  exchange->add_maker<MMakerTrader>();
  exchange->add_taker<MTakerTrader>();
  EXPECT_EQ(exchange->get_makers().size(), 2);
  EXPECT_EQ(exchange->get_takers().size(), 2);
  EXPECT_EQ(exchange->get_makers().back()->get_name(), "maker_2");
  EXPECT_EQ(exchange->get_takers().back()->get_name(), "taker_2");
  exchange->add_maker<MMakerTrader>();
  exchange->add_taker<MTakerTrader>();
  EXPECT_EQ(exchange->get_makers().size(), 3);
  EXPECT_EQ(exchange->get_takers().size(), 3);
  EXPECT_EQ(exchange->get_makers().back()->get_name(), "maker_3");
  EXPECT_EQ(exchange->get_takers().back()->get_name(), "taker_3");
  exchange->add_maker<MMakerTrader>();
  exchange->add_taker<MTakerTrader>();
  EXPECT_EQ(exchange->get_makers().size(), 4);
  EXPECT_EQ(exchange->get_takers().size(), 4);
  EXPECT_EQ(exchange->get_makers().back()->get_name(), "maker_4");
  EXPECT_EQ(exchange->get_takers().back()->get_name(), "taker_4");
}

TEST_F(ExchangeTest, RunTest) {
  exchange->add_maker<MMakerTrader>();
  exchange->add_taker<MTakerTrader>();
  exchange->run();
  EXPECT_TRUE(!exchange->get_book().get_buy_orders().empty() || !exchange->get_book().get_sell_orders().empty());
  if (exchange->get_market_data().get_trade_history().empty()) {
    EXPECT_EQ(exchange->get_book().get_buy_orders().size(), 1);
    EXPECT_EQ(exchange->get_book().get_sell_orders().size(), 1);
  } else {
    float price = exchange->get_market_data().get_last_price();
    float trade_price = exchange->get_market_data().get_last_trade()->price;
    EXPECT_FLOAT_EQ(price, trade_price);
  }

  const size_t n_it = 50;
  for (size_t i = 0; i < n_it; ++i) {
    exchange->run();
  }

}