all: test

run: main  
	./main.exe

main: main.o bigint.o
	g++ main.o bigint.o -o main.exe --std=c++14 -O2

main.o: main.cpp
	g++ -c main.cpp --std=c++14 -O2
    
bigint.o: bigint.cpp bigint.h
	g++ -c bigint.cpp --std=c++14 -O2
    
test: main
	./main.exe
    
clean: 
	rm *.o