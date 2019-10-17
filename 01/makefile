all: run; 

run: calc  
	./calc.exe

test: calc
	python3 ./test.py

calc: 
	g++ calc.cpp -o calc.exe --std=c++14 -O2

clean: 
	del /f *.exe           