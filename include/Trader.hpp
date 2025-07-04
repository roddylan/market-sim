// Trader.hpp
#pragma once
#include <string>
#include <unordered_map>
#include <tuple>

using SYMBOL = std::string;

class Trader {
public:
  /**
   * @brief Construct a new Trader object
   * 
   */
  Trader() = default;
  /**
   * @brief Destroy the Trader object
   * 
   */
  ~Trader() = default;

  /**
   * @brief Construct a new Trader object
   * 
   * @param _name 
   */
  Trader(const std::string &_name);
  /**
   * @brief Construct a new Trader object
   * 
   * @param other 
   */
  Trader(const Trader &other);
  /**
   * @brief Assignment
   * 
   * @param rhs 
   * @return Trader& 
   */
  Trader &operator=(const Trader &rhs);

  /**
   * @brief Get the name object
   * 
   * @return const std::string& 
   */
  const std::string &get_name() const;
  
  /**
   * @brief Set the name object
   * 
   * @param _name 
   */
  void set_name(const std::string &_name);

  /**
   * @brief Let Trader make trade
   * 
   * @return std::tuple<float, int> 
   */
  virtual std::tuple<float, int> trade() const;
private:
  std::string name;
};

/**
 * @brief Market Maker
 * 
 */
class MMakerTrader : public Trader {
  /**
   * @brief Let Trader make trade
   * 
   * @return std::tuple<float, int> 
   */
  std::tuple<float, int> trade() const override;
};

/**
 * @brief Market Taker
 * 
 */
class MTakerTrader : public Trader {
  /**
   * @brief Let Trader make trade
   * 
   * @return std::tuple<float, int> 
   */
  std::tuple<float, int> trade() const override;
};


