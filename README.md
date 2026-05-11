
# Cryptopals

This repository contains solutions to the [Cryptopals Crypto Challenges](https://www.cryptopals.com/) written in C++. I used this project to learn the C++ language and to practice lower level programming.

# Build and Requirements

The following are required to build:

-   g++
-   make

To build, navigate to the repository root directory and run `make`. The `cryptopals` binary will be created in the repository root.

# Usage

To run a challenge solution, pass a set number and challenge number as an argument to the `cryptopals` binary.

For example,

```
./cryptopals 1-01
```

Many challenges can also take alternative arguments. See the individual challenge source files for supported arguments. For example,

```
./cryptopals 1-01 deadbeef
```

# License

Solutions are licensed under a GPL-3.0 license. The data files under resources and any embedded data strings are included for completeness and reproducibility, and are under the copyrights of their respective owner.
