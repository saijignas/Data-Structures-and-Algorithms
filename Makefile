CXX ?= g++
CXXFLAGS = -std=c++14 -Wall -Wextra -Iinclude -O2
TEST_SRCS = $(wildcard tests/*.cpp)
BIN = run_tests

.PHONY: test clean

test: $(BIN)
	./$(BIN)

$(BIN): $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(TEST_SRCS)

clean:
	rm -f $(BIN) $(BIN).exe
