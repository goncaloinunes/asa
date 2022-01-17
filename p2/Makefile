CXX = g++
CXXFLAGS = -std=c++11 -O3 -Wall -lm
CXXDEBUG = -std=c++11 -O0 -ggdb3 -pedantic -Wall -Wextra -Werror

all:: do
	$(MAKE) $(MFLAGS) -C tests

do: src/project.cpp
	$(CXX) $(CXXFLAGS) src/*.cpp -o project

debug: src/project.cpp
	$(CXX) $(CXXDEBUG) src/*.cpp -o project

valgrind: project
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --log-file=valgrind-out.log ./project

run: project
	./project

clean:
	rm -f project tests/*.diff

