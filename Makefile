FLAGS = -pthread -pedantic-errors -std=c++11 -g

game: main.o io.o game_type.o
	g++ $(FLAGS) $^ -o game
game_type.o: game_type.cpp game_type.h
	g++ $(FLAGS) -c $<
io.o: io.cpp io.h game_type.h
	g++ $(FLAGS) -c $<
main.o: main.cpp game_type.h io.h
	g++ $(FLAGS) -c $<

clean:
	rm -f *.o game

.PHONY: clean