all: vector
	./vector
    
run: vector
	./vector
    
vector: main.o
	g++ main.o -o vector --std=c++14 -O2

main.o: main.cpp
	g++ main.cpp -c --std=c++14 -O2

clean: 
	rm *.o

test: 
	./vector