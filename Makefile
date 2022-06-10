all : main

main : *.cpp
	g++ main.cpp -lncurses -o main && ./main