// Exchange.cpp
#include "Exchange.hpp"
#include "MarketData.hpp"
#include "OrderBook.hpp"
#include "Trader.hpp"
#include <memory>

Exchange::Exchange(float _starting_price)
    : book(std::make_unique<OrderBook>()),
      market_data(std::make_unique<MarketData>()),
      starting_price(_starting_price) {}

void Exchange::add_maker(const Trader &maker) {
  makers.push_back(std::make_shared<Trader>(maker));
  ++maker_counter;
}

void Exchange::add_taker(const Trader &taker) {
  takers.push_back(std::make_shared<Trader>(taker));
  ++taker_counter;
}

const OrderBook &Exchange::get_book() const { return *book; }

const MarketData &Exchange::get_market_data() const { return *market_data; }

float Exchange::get_starting_price() const { return starting_price; }

void Exchange::run() {
  for (const auto maker : makers) {
    float price = maker->fair_price(this);
    book->insert(maker->make_order(price, true));
    book->insert(maker->make_order(price, false));
  }

  for (const auto taker : takers) {
    if (book->get_buy_orders().empty() && book->get_sell_orders().empty()) {
      break;
    }
    float price = taker->fair_price(this);
    Order order = taker->make_order(price);

    float vwap = book->match(order); // TODO: make match (and other stuff that
                                     // uses taker orders) use universal ref
    if (vwap == 0) {
      break;
    } // TODO: parallelize, continue instead of break. Kinda bad sim for
      // backtesting if takers have same priority
    // TODO: get maker for better trade history
    market_data->add_trade(*taker, *taker, vwap);
  }
}