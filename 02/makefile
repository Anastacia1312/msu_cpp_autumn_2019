all: run; 

run: main  
	./main.exe

main: main.o allocator.o
	g++ main.o allocator.o -o main.exe --std=c++14 -O2

main.o: main.cpp
	g++ -c main.cpp --std=c++14 -O2
    
allocator.o: allocator.cpp allocator.h
	g++ -c allocator.cpp --std=c++14 -O2
    
test: main
	python3 ./test.py
    
clean: 
	rm *.o    