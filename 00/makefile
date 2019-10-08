all: run; 

run: task0_by_rows task0_by_columns 
	./task0_by_rows.exe && ./task0_by_columns.exe

task0_by_rows: 
	g++ 1.cpp -o task0_by_rows.exe

task0_by_columns: 
	g++ 2.cpp -o task0_by_columns.exe

clean: 
	del /f *.exe           