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

(you can also use your own taker/makers by inheriting from the Trader class)

# Documentation
The full API documentation is generated using [Doxygen](https://www.doxygen.nl/).  
To build it locally:

```bash
doxygen Doxyfile
```

# Planned Features
Future features:
- Multi level quoting from market makers + option to disable book filling (all takers auto filled)
- Better support for 'backtesting' (tracking pnl, etc.)
- Options sim + multiple trades

