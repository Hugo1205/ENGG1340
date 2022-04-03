# DO NOT edit Makefile in the editor
# Either copy-and-paste from your version,
#   or use the "Submission" tab
FLAGS = -pedantic-errors -std=c++11

io.o: io.cpp io.h
	g++ $(FLAGS) -c $<


main.o: main.cpp io.h 
	g++ $(FLAGS) -c $<

game: main.o io.o
	g++ $(FLAGS) $^ -o game

clean:
	rm -f *.o game

.PHONY: clean