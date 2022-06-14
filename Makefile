all : main

main : *.cpp
	g++ main.cpp -lncursesw -o main && ./main