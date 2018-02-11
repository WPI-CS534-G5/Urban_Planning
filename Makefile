

CFLAGS = -Wall -g

urbanplanning:  main.o
	g++ $(CFLAGS) main.o -lm -o urbanplanning

main.o: main.cpp global.h
	g++ $(CFLAGS) -c main.cpp

clean:
	rm -f *.o urbanplanning
