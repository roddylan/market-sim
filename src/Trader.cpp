// Trader.cpp
#include "Trader.hpp"
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

std::tuple<float, int> Trader::trade() const { return std::make_tuple(0., 0); }

std::tuple<float, int> MMakerTrader::trade() const {
  // TODO: placeholder
  return std::make_tuple(0., 0);
}

std::tuple<float, int> MTakerTrader::trade() const {
  // TODO: placeholder
  return std::make_tuple(0., 0);
}
