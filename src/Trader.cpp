// Trader.cpp
#include "Trader.hpp"
#include "Exchange.hpp"
#include "MarketData.hpp"
#include "Order.hpp"
#include <random>
#include <string>
#include <tuple>

Trader::Trader(const Trader &other) : name{other.name} {}

Trader::Trader(const std::string &_name) : name{_name} {}

Trader &Trader::operator=(const Trader &rhs) {
  if (this == &rhs) {
    return *this;
  }
  name = rhs.name;
  return *this;
}

const std::string &Trader::get_name() const { return name; }

void Trader::set_name(const std::string &_name) { name = _name; }

MMakerTrader::MMakerTrader(const std::string &_name)
    : Trader("maker_" + _name) {}
MTakerTrader::MTakerTrader(const std::string &_name)
    : Trader("taker_" + _name) {}

bool Trader::operator==(const Trader &other) const {
  if (this == &other) {
    return true;
  }
  return (this->name == other.name);
}


float MMakerTrader::fair_price(const Exchange *exchange) const {
  // mid price
  const OrderBook &book = exchange->get_book();
  const MarketData &data = exchange->get_market_data();
  float price = exchange->get_starting_price();

  if (data.get_last_price() == 0 ||
      (book.get_buy_orders().empty() && book.get_sell_orders().empty())) {
    return price;
  }

  if (!book.get_buy_orders().empty() && !book.get_sell_orders().empty()) {
    price = ((*book.get_buy_orders().begin())->get_price() +
             (*book.get_sell_orders().begin())->get_price()) /
            2;
  } else if (!book.get_buy_orders().empty()) {
    price = (*book.get_buy_orders().begin())->get_price();
  } else {
    price = (*book.get_sell_orders().begin())->get_price();
  }
  return price;
}

float MTakerTrader::fair_price(const Exchange *exchange) const {
  // mid price
  const OrderBook &book = exchange->get_book();
  const MarketData &data = exchange->get_market_data();
  float price = exchange->get_starting_price();

  if (data.get_last_price() == 0 ||
      (book.get_buy_orders().empty() && book.get_sell_orders().empty())) {
    return price;
  }

  if (!book.get_buy_orders().empty() && !book.get_sell_orders().empty()) {
    price = ((*book.get_buy_orders().begin())->get_price() +
             (*book.get_sell_orders().begin())->get_price()) /
            2;
  } else if (!book.get_buy_orders().empty()) {
    price = (*book.get_buy_orders().begin())->get_price();
  } else {
    price = (*book.get_sell_orders().begin())->get_price();
  }
  return price;
}

