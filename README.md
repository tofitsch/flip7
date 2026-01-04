This program allows to test out strategies for the game [flip7](https://theop.games/pages/flip-7-game?srsltid=AfmBOoq4EKyPi5u202h0PImaoWX13vw0Yvi-dnO3eXN92F-C9WuNPs95).

Strategies are defined as functions (explained further below) which can then be made to play against each other for a large number of games.

Statistics like number of games won, average score per round and per game etc are tracked throughout the process.

You can run it in this [binder](https://mybinder.org/v2/gh/tofitsch/flip7/master?urlpath=%2Flab%2Ftree%2Futil%2Fmain.cpp).

Or directly from the terminal:

```
cd build
cmake ..
make 
./x
```

Any changes to strategies and game setup should be made in `util/main.cpp` before re-compiling and re-running:

```
cd build
make
./x
```
