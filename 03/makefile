all: run; 

run: main  
	./main.exe

main: main.o matrix.o
	g++ main.o matrix.o -o main.exe --std=c++14 -O2

main.o: main.cpp
	g++ -c main.cpp --std=c++14 -O2
    
matrix.o: matrix.cpp matrix.h
	g++ -c matrix.cpp --std=c++14 -O2
    
test: main
	python3 ./test.py
    
clean: 
	rm *.o