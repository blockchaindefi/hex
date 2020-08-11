CCP=g++
CC=gcc
FLAGS=-Wall
PROGRAM_NAMES=hex_stake2day hex_percentage_growth

all: $(PROGRAM_NAMES)

debug: FLAGS=-O0 -g -W -ggdb -Wall
debug: $(PROGRAM_NAMES)


hex_stake2day: hex_stake2day.o
	$(CC) $(FLAGS) hex_stake2day.o -o hex_stake2day

hex_stake2day.o: hex_stake2day.c
	$(CC) $(FLAGS) -c hex_stake2day.c


hex_percentage_growth: hex_percentage_growth.o
	$(CCP) $(FLAGS) hex_percentage_growth.o -o hex_percentage_growth

hex_percentage_growth.o: hex_percentage_growth.cpp
	$(CCP) $(FLAGS) -c hex_percentage_growth.cpp


clean:
	rm -f *.o $(PROGRAM_NAMES)

