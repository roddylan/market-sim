#include "Order.hpp"
#include "OrderBook.hpp"
#include "Trader.hpp"
#include <gtest/gtest.h>
#include <iostream>

void print_book(const OrderBook &book) {
  std::cout << "buy orders: \n";
  auto temp_buy_orders = book.get_buy_orders();
  auto temp_sell_orderes = book.get_sell_orders();
  while (!temp_buy_orders.empty()) {
    auto cur = temp_buy_orders.top();
    std::cout << "PRICE: " << cur->get_price()
              << " | VOLUME: " << cur->get_volume()
              << " | TRADER: " << cur->get_trader().get_name() << " | "
              << cur->get_time().time_since_epoch().count() << std::endl;
    temp_buy_orders.pop();
  }
  std::cout << "sell orders: \n";
  while (!temp_sell_orderes.empty()) {
    auto cur = temp_sell_orderes.top();
    std::cout << "PRICE: " << cur->get_price()
              << " | VOLUME: " << cur->get_volume()
              << " | TRADER: " << cur->get_trader().get_name() << " | "
              << cur->get_time().time_since_epoch().count() << std::endl;
    temp_sell_orderes.pop();
  }
}

int main() {
  // trader tests
  std::cout << "-----TRADER-----\n";
  Trader maker1 = MMakerTrader("1");
  Trader maker2 = MMakerTrader("2");
  Trader maker3 = MMakerTrader("3");

  Trader taker1 = MTakerTrader("1");
  Trader taker2 = MTakerTrader("2");
  Trader taker3 = MTakerTrader("3");

  Trader test_trader = MMakerTrader("TEST");

  std::cout << maker1.get_name() << std::endl;
  std::cout << maker2.get_name() << std::endl;
  std::cout << maker3.get_name() << std::endl;

  std::cout << taker1.get_name() << std::endl;
  std::cout << taker2.get_name() << std::endl;
  std::cout << taker3.get_name() << std::endl;

  std::cout << test_trader.get_name() << std::endl;
  
  // test_order
  std::cout << "-----ORDER TEST-----\n";
  Order test_buy(10.0, 100, test_trader);
  std::cout << test_buy.get_volume() << std::endl;
  test_buy.update_volume(-5);
  std::cout << test_buy.get_volume() << std::endl;
  
  
  std::cout << "-----ORDERBOOK-----\n";
  // order book
  // maker orders
  Order make_buy1(10.0, 100, maker1);
  Order make_sell1(11.0, -100, maker1);
  Order make_buy2(9.5, 100, maker1);
  Order make_sell2(10.5, -100, maker1);

  OrderBook book{};

  assert(book.get_buy_orders().size() == 0);
  assert(book.get_sell_orders().size() == 0);

  book.insert(make_buy1);
  assert(book.get_buy_orders().size() == 1);
  assert(book.get_sell_orders().size() == 0);

  book.insert(make_sell1);
  assert(book.get_buy_orders().size() == 1);
  assert(book.get_sell_orders().size() == 1);

  book.insert(make_sell2);
  assert(book.get_buy_orders().size() == 1);
  assert(book.get_sell_orders().size() == 2);

  book.insert(make_buy2);
  assert(book.get_buy_orders().size() == 2);
  assert(book.get_sell_orders().size() == 2);

  std::cout << "pass\n";
  print_book(book);
  
  
  Order taker_buy1(5.0, 50, taker1);
  auto price_na = book.match(taker_buy1);
  std::cout << price_na << std::endl << std::endl;
  
  assert(book.get_buy_orders().size() == 2);
  assert(book.get_sell_orders().size() == 2);
  print_book(book);
  

  std::cout << "--------REAL BUY-------\n";
  Order taker_buy2(11.0, 250, taker1);
  auto price_1 = book.match(taker_buy2);
  std::cout << price_1 << std::endl;
  print_book(book);
  
  assert(book.get_buy_orders().size() == 2);
  assert(book.get_sell_orders().size() == 2);
  
}