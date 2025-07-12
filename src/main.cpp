// main.cpp
#include "Exchange.hpp"
#include "Trader.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
  Exchange exchange;

  // makers=1 | takers=3 seems to be ideal
  // ratio of 1:3 makers*
  size_t n_makers{3}, n_takers{9};
  for (size_t i = 0; i < n_makers; ++i) {
    exchange.add_maker<MMakerTrader>();
  }
  for (size_t i = 0; i < n_takers; ++i) {
    exchange.add_taker<MTakerTrader>();
  }

  const size_t n_it = 100000;

  for (size_t i = 0; i < n_it; ++i) {
    exchange.run();
  }
  
  std::ofstream file("output.csv");
  if (!file.is_open()) {
    std::cerr << "Failed to open file for writing\n";
    return 1;
  }
  size_t i = 0;
  file << "price\n";
  for (const float &price : exchange.get_market_data().get_prices()) {
    if (i < (exchange.get_market_data().get_prices().size() - 1)){
      file << price << "\n";
    }
    ++i;
  }
  file.close();
  std::cout << "done" << std::endl;

}