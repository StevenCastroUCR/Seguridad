FLAGS = -g -c --std=c++17

all:
	mkdir -p obj
	mkdir -p bin
	g++ $(FLAGS) src/main.cc -o obj/calc.o
	g++ -g -o bin/organizador obj/calc.o 
	 
	


clean:
	rm -Rf bin
	rm -Rf obj


	FLAGS = -g -fPIC -c --std=c++17

