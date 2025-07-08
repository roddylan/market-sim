// main.cpp
#include "Order.hpp"
#include "OrderBook.hpp"
#include "Exchange.hpp"
#include "Trader.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
  Exchange exchange;
  exchange.add_maker<MMakerTrader>();
  exchange.add_maker<MMakerTrader>();
  exchange.add_maker<MMakerTrader>();
  exchange.add_taker<MTakerTrader>();
  exchange.add_taker<MTakerTrader>();
  exchange.add_taker<MTakerTrader>();

  const size_t n_it = 100;

  for (size_t i = 0; i < n_it; ++i) {
    exchange.run();
  }
  
  std::ofstream file("output.csv");
  if (!file.is_open()) {
    std::cerr << "Failed to open file for writing\n";
    return 1;
  }
  size_t i = 0;
  for (const auto &price : exchange.get_market_data().get_prices()) {
    std::cout << price << "\n";
    if (i < (exchange.get_market_data().get_prices().size() - 1)){
      file << price << ",";
    }
    ++i;
  }
  file.close();
  std::cout << "done" << std::endl;

}