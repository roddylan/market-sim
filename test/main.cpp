#include "Order.hpp"
#include "OrderBook.hpp"
#include "Trader.hpp"
#include <gtest/gtest.h>
#include <iostream>

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

  Order taker_buy(5.0, 50, taker1);
  auto price_na = book.match(taker_buy);
  std::cout << price_na << std::endl;

  assert(book.get_buy_orders().size() == 2);
  assert(book.get_sell_orders().size() == 2);
}