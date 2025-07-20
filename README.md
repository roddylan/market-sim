# market-sim
C++ market simulator 

Basic order book simulator.

# How to use
To run this program, run the following commands:
```bash
cmake -B build
```

```bash
cd build && make sim
```

```bash
./sim
```

(unfortunately, I haven't added any CLI args so if you want to play around with certain aspects you'll have to go in `src/main.cpp`)

(you can also use your own taker/makers by inheriting from the `Trader` class and overriding `make_order`, `fair_price`)

Sim price results will be found in your build folder (`build` in given commands) as `output.csv`, this can be visualized in the notebook found [here](./py_data_analysis).

# Documentation
The full [documentation](https://roddylan.github.io/market-sim/) is generated using [Doxygen](https://www.doxygen.nl/).  
To build it locally:

```bash
doxygen Doxyfile
```

# Planned Features
Future features:
- Multi level quoting from market makers + option to disable book filling (all takers auto filled)
- Better support for 'backtesting' (tracking pnl, etc.)
- Options sim + multiple trades

