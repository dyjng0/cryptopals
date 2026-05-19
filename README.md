# Cryptopals

This repository contains solutions to the [Cryptopals Crypto Challenges](https://www.cryptopals.com/) written in C++. I used this project as an opportunity to learn C++ and practice lower level programming. Some of the formatting and code structure is inspired by [garyg1](https://github.com/garyg1/cryptopals) and [davidscholberg](https://github.com/davidscholberg/cryptopals-cpp/tree/master).

# Build and Requirements

The following are required to build:

-   g++
-   make

Navigate to the repository root directory and run `make`. The `cryptopals` binary will be created in the repository root.

# Usage

To run a challenge solution, pass a set number and challenge number as an argument to the `cryptopals` binary.

For example,

```
./cryptopals 1-01
```

Challenges can also take alternative arguments. See the individual challenge source files for supported arguments. For example,

```
./cryptopals 1-01 deadbeef
```

# License

Solutions are licensed under a GPL-3.0 license. The data files under resources and any embedded data strings are included for completeness and reproducibility, and are under the copyrights of their respective owner.
