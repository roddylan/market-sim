// Trade.hpp
#pragma once
#include "Trader.hpp"
#include "MarketUtils.hpp"

/**
 * @class Trade
 * @brief Represents executed trade
 * 
 */
struct Trade {
  Trade() = delete;
  ~Trade() = default;

  /**
   * @brief Construct a new Trade object
   * 
   * @param _maker 
   * @param _taker 
   * @param _price 
   */
  Trade(const Trader *_maker, const Trader *_taker, float _price);
  
  /**
   * @brief Construct a new Trade object
   * 
   * @param _maker 
   * @param _taker 
   * @param _price 
   */
  Trade(Trader &_maker, Trader &_taker, float _price);
  
  /**
   * @brief Construct a new Trade object
   * 
   * @param other 
   */
  Trade(const Trade &other);
  
  /**
   * @brief Copy assignment for Trade
   * 
   * @return Trade& 
   */
  Trade &operator=(const Trade &) = delete;

  const Trader* const maker;
  const Trader* const taker;
  const float price;
  const MarketUtils::Timestamp timestamp;
};