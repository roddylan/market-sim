// Trader.hpp
#pragma once
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

  /**
   * @brief Let Trader make trade
   * 
   * @return std::tuple<float, int> 
   */
  virtual std::tuple<float, int> trade();
private:
  std::string name;
};

