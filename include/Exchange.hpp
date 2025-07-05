// Exchange.hpp
// Simulate exchange
#pragma once
#include "Trader.hpp"
#include <vector>
#include <memory>

class Exchange {
public:
  Exchange();
  ~Exchange();

  void run();
private:
  std::vector<std::unique_ptr<Trader>> makers;
  std::vector<std::unique_ptr<Trader>> takers;

  
};