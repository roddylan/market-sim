// Trader.cpp
#include "Trader.hpp"
#include <string>
#include <tuple>
#include <random>
#include "Exchange.hpp"
#include "Order.hpp"

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


MMakerTrader::MMakerTrader(const std::string &_name) : Trader("maker_" + _name) {}
MTakerTrader::MTakerTrader(const std::string &_name) : Trader("taker_" + _name) {}

float MMakerTrader::fair_price(const Exchange &exchange) const {
  return 0;
}

float MTakerTrader::fair_price(const Exchange &exchange) const {
  return 0;
}


bool Trader::operator==(const Trader &other) const {
  if (this == &other) { return true; }
  return (this->name == other.name);
}