// benchmark_order_book.cpp
// multiset vs priority queue
#include "OrderBook.hpp"
#include "OrderBookPQ.hpp"
#include "Order.hpp"
#include "Trader.hpp"
#include <chrono>
#include <exception>
#include <vector>
#include <string> 
#include <iostream>

int main(int argc, char* argv[]) {
  Trader *maker = new MMakerTrader("bench");
  Trader *taker = new MTakerTrader("bench");

  std::vector<Order> orders;
  size_t n_orders = 10000;

  if (argc > 0) {
    try {
      n_orders = std::stoul(argv[0]);
    } catch (...) {
      std::cerr << "Error: bad args" << std::endl;
      return 1;
    }
  }

  
  
}