all: compile run

compile:
	g++ ramEater64.cpp -O3 -o ramEater64.exe

run:
	./ramEater64.exe
   
