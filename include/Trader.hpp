// Trader.hpp
#pragma once
#include <string>
#include <unordered_map>
#include <tuple>

using SYMBOL = std::string;

class Trader {
public:
  Trader() = default;
  ~Trader() = default;

  Trader(const std::string &_name);
  Trader(const Trader &other);
  Trader &operator=(const Trader &rhs);

  /**
   * @brief Let Trader make trade
   * 
   * @return std::tuple<float, int> 
   */
  virtual std::tuple<float, int> trade();
private:
  std::string name;
};

