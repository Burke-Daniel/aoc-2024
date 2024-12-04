all: day1 day2 day3

day1: day1.cpp
	g++ day1.cpp -o day1

day2: day2.cpp
	g++ day2.cpp -o day2

day3: day3.c
	gcc day3.c -o day3
