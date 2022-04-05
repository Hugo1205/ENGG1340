# DO NOT edit Makefile in the editor
# Either copy-and-paste from your version,
#   or use the "Submission" tab
FLAGS = -pedantic-errors -std=c++11

game: main.o io.o game_type.o
	g++ $(FLAGS) $^ -o game

io.o: io.cpp io.h
	g++ $(FLAGS) -c $<

main.o: main.cpp io.h game_type.h
	g++ $(FLAGS) -c $<

game_type.o: game_type.cpp game_type.h
	g++ $(FLAGS) -c $<


clean:
	rm -f *.o game

.PHONY: clean