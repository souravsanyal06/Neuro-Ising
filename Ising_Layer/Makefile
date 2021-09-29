DEPENDENCIES := src/main.o src/cost_function.o src/mylib.o src/problem.o src/ising_solver.o src/random_selector.o src/mid.o src/mid_grid.o
TARGET := ising

all: $(TARGET)

$(TARGET): $(DEPENDENCIES)
	g++ -O2 $^ -o $@

%.o: %.cpp
	g++ -std=c++14 -Wall -O2 -c $^ -o $@

clean:
	rm -f $(TARGET)
	rm -f src/*.o
