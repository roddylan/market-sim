// Order.hpp
// Order object
#ifndef _ORDER_HPP
#define _ORDER_HPP
#include "Trader.hpp"
#include <memory>

/**
 * @class Order
 * @brief Represents Order
 *
 * Class stores order information, negative volume for short/sell and positive
 * volume for long/buy
 */
class Order {
public:
  /**
   * @brief Construct a new Order object (default)
   * 
   */
  Order() = default;
  /**
   * @brief Destroy the Order object (default)
   * 
   */
  ~Order() = default;
  
  /**
   * @brief Construct a new Order object
   * 
   * @param _price 
   * @param _volume 
   * @param _maker 
   */
  Order(float _price, int _volume, const std::shared_ptr<Trader> &_maker);

  /**
   * @brief Construct a new Order object
   * 
   */
  Order(const Order &);
  
  // deleted assignment operator
  Order &operator=(const Order &) = delete;
  
  // getters
  /**
   * @brief Get the bid/ask price of the order
   * 
   * @return float 
   */
  float get_price() const noexcept;
  
  /**
   * @brief Get the volume of the trade. < 0 if short/sell, > 0 if long/buy
   * 
   * @return int 
   */
  int get_volume() const noexcept;
  
  /**
   * @brief Get the maker object
   * 
   * @return Trader& 
   */
  Trader &get_maker() const noexcept;

  /**
   * @brief Execute order (partially or fully)
   * 
   * @return int volume traded
   */
  int make_trade();
private:
  float price;
  int volume;
  const std::shared_ptr<Trader> maker;

};

#endif