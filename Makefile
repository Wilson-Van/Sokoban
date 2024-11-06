CC = g++
FLAGS = -Wall -Werror -pedantic -std=c++17 -g
LIBS = -lboost_unit_test_framework -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

DEPS = Sokoban.hpp
OBJS = Sokoban.o

PROGRAM = Sokoban test

all: Sokoban Sokoban.a test

Sokoban: main.o Sokoban.a
	$(CC) $(FLAGS) -o $@ $^ $(LIBS)

test: test.o Sokoban.a
	$(CC) $(FLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp $(DEPS)
	$(CC) $(FLAGS) -c $<

Sokoban.a: Sokoban.o
	ar rcs Sokoban.a Sokoban.o

clean:
	rm *.o *.a $(PROGRAM)

lint:
	cpplint *.cpp *.hpp
