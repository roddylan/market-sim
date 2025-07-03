// Trader.hpp
#ifndef _TRADER_HPP
#define _TRADER_HPP
#include <string>
#include <unordered_map>
#include <tuple>

using SYMBOL = std::string;

class Trader {
public:
  Trader();
  ~Trader();

  Trader(const Trader &);
  Trader &operator=(const Trader &);
private:
  std::string name;
  std::unordered_map<SYMBOL, std::tuple<size_t, float>> positions;
};



#endif