// benchmark_order_book.cpp
// multiset vs priority queue
// benchmark insertion and matching
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

  std::vector<Order> buy_orders;
  std::vector<Order> sell_orders;
  size_t n_orders = 10000;

  if (argc > 1) {
    try {
      n_orders = std::stoul(argv[0]);
    } catch (...) {
      std::cerr << "Error: bad args" << std::endl;
      return 1;
    }
  }
  // setup
  float price = 10 * n_orders;
  size_t abs_vol = 100;

  for (int i = 0; i < n_orders; ++i) {
    buy_orders.push_back(
      Order(price-i, abs_vol, maker)
    );
    sell_orders.push_back(
      Order(price+i, -abs_vol, maker)
    );
  }

  std::vector<Order> taker_buy, taker_sell;

  for (int i = 0; i < n_orders; ++i) {
    taker_buy.push_back(
      Order(price+i+1, abs_vol + 30, taker)
    );
    taker_sell.push_back(
      Order(price-i-1, -abs_vol - 30, taker)
    );
  }
  using Clock = std::chrono::high_resolution_clock;

  // pq
  auto start_pq = Clock::now();
  OrderBookPQ book_pq;
  for (const Order &order : buy_orders) {
    book_pq.insert(order);
  }
  for (const Order &order : sell_orders) {
    book_pq.insert(order);
  }
  for (Order &order : taker_buy) {
    book_pq.match(order);
  }
  for (Order &order : taker_sell) {
    book_pq.match(order);
  }
  auto end_pq = Clock::now();

  auto duration_pq = std::chrono::duration_cast<std::chrono::microseconds>(end_pq-start_pq);

  std::cout << "ORDER_BOOK (PQ) | ELAPSED TIME = " << duration_pq.count() << " µs" << std::endl;

  // pq
  auto start_ms = Clock::now();
  OrderBookPQ book_ms;
  for (const Order &order : buy_orders) {
    book_ms.insert(order);
  }
  for (const Order &order : sell_orders) {
    book_ms.insert(order);
  }
  for (Order &order : taker_buy) {
    book_ms.match(order);
  }
  for (Order &order : taker_sell) {
    book_ms.match(order);
  }
  auto end_ms = Clock::now();

  auto duration_ms = std::chrono::duration_cast<std::chrono::microseconds>(end_pq-start_pq);

  std::cout << "ORDER_BOOK (MS) | ELAPSED TIME = " << duration_ms.count() << " µs" << std::endl;
  

  
  
}