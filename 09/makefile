all: main
	./main
    
run: main
	./main

test: main
	./main
    
main: main.o
	g++ main.o -pthread -o main --std=c++14 -O2
    
main.o: main.cpp
	g++ main.cpp -c --std=c++14 -O2
    
clean:
	rm *.o main output.txt