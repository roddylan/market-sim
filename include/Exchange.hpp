// Exchange.hpp
// Simulate exchange
#pragma once
#include "Trader.hpp"
#include <vector>
#include <memory>

class Exchange {
public:
private:
  std::vector<std::unique_ptr<Trader>> makers;
  std::vector<std::unique_ptr<Trader>> takers;

};