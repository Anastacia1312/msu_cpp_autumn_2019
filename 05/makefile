all: test

run: main  
	./main.exe

main: main.o 
	g++ main.o -o main.exe --std=c++14 -O2

main.o: main.cpp serializer.h
	g++ -c main.cpp --std=c++14 -O2
    
test: main
	./main.exe
    
clean: 
	rm *.o