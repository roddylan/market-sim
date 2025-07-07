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
}

void Exchange::add_taker(const Trader &taker) {
  makers.push_back(std::make_shared<Trader>(taker));
}

const OrderBook &Exchange::get_book() const { return *book; }

const MarketData &Exchange::get_market_data() const { return *market_data; }

float Exchange::get_starting_price() const { return starting_price; }


void Exchange::run() {
  for (const auto maker : makers) {
    maker->fair_price(this);
  }
}