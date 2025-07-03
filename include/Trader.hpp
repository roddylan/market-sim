// Trader.hpp
#ifndef _TRADER_HPP
#define _TRADER_HPP
#include <string>
class Trader {
public:
  Trader();
  ~Trader();

  Trader(const Trader &);
  Trader &operator=(const Trader &);
private:
  std::string name;
  
};



#endif