// Trader.cpp
#include "Trader.hpp"
#include "Exchange.hpp"
#include "MarketData.hpp"
#include "Order.hpp"
#include <exception>
#include <random>
#include <string>

Trader::Trader(const Trader &other) : name{other.name}, gen{other.gen} {}

Trader::Trader(const std::string &_name) : name{_name}, gen{std::random_device{}()} {}

Trader &Trader::operator=(const Trader &rhs) {
  if (this == &rhs) {
    return *this;
  }
  name = rhs.name;
  return *this;
}

const std::string &Trader::get_name() const { return name; }

void Trader::set_name(const std::string &_name) { name = _name; }

void Trader::set_random(int seed) {
  gen = std::mt19937(seed);
}

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

float Trader::fair_price(const Exchange *exchange) const { return 0; }

Order Trader::make_order(float fair_price, bool is_long) const {
  return Order(fair_price, 100, this);
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
  return data.get_last_price();

  // if (!book.get_buy_orders().empty() && !book.get_sell_orders().empty()) {
  //   price = ((*book.get_buy_orders().begin())->get_price() +
  //            (*book.get_sell_orders().begin())->get_price()) /
  //           2;
  // } else if (!book.get_buy_orders().empty()) {
  //   price = (*book.get_buy_orders().begin())->get_price();
  // } else {
  //   price = (*book.get_sell_orders().begin())->get_price();
  // }
  // return price;
}

Order MMakerTrader::make_order(float fair_price, bool is_long) const {
  const size_t abs_vol = 100;
  const int sign = (is_long * 2) - 1;
  const int vol = abs_vol * sign;
  const float std = 0.01f;
  
  std::normal_distribution<float> distr(0.f, std);
  const float price_multiplier = std::abs(distr(gen));
  float price = fair_price;
  // TODO: symmetric pricing from makers
  if (is_long) {
    // buying, make offer <= fair
    price -= price_multiplier * fair_price;
  } else {
    // selling, make offer >= fair
    price += price_multiplier * fair_price;
  }
  return Order(price, vol, this);
  
}
Order MTakerTrader::make_order(float fair_price, bool is_long) const {
  const int sign = (is_long * 2) - 1;
  const size_t abs_vol = 100;
  const float std = 0.0125f;

  std::normal_distribution<float> distr(0.f, std);
  const float price_multiplier = std::abs(distr(gen));
  const int vol = abs_vol * sign;
  
  float price = fair_price;
  if (is_long) {
    // buying, make offer <= fair
    price -= price_multiplier * fair_price;
  } else {
    // selling, make offer >= fair
    price += price_multiplier * fair_price;
  }
  return Order(price, vol, this);
  
}