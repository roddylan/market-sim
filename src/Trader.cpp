// Trader.cpp
#include "Trader.hpp"
#include <string>
#include <tuple>

Trader::Trader(const Trader &other) : name{other.name} {}

Trader::Trader(const std::string &_name) : name{_name} {}

Trader &Trader::operator=(const Trader &rhs) {
  if (this == &rhs) { return *this; }
  name = rhs.name;
  return *this;
}

std::tuple<float, int> Trader::trade() {
  return std::make_tuple(0., 0);
}