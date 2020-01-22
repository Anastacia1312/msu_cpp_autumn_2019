all: threadpool
	./threadpool

run: threadpool
	./threadpool

threadpool: main.o 
	g++ main.o -pthread -o threadpool --std=c++14 -O2

main.o: main.cpp threadpool.h
	g++ main.cpp -c --std=c++14 -O2

clean:
	rm *.o

test: 
	./threadpool