CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -I.
TARGET = cryptopals
SRC = src
SRCS = $(SRC)/cryptopals.cpp $(wildcard $(SRC)/challenges/*.cpp) $(wildcard $(SRC)/lib/*.cpp)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
