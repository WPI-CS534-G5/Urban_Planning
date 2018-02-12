

CFLAGS = -Wall -g

urbanplanning:  main.o genetic.o iofunctions.o global.h
	g++ $(CFLAGS) main.o genetic.o iofunctions.o -lm -o urbanplanning

main.o: main.cpp global.h
	g++ $(CFLAGS) -c main.cpp

genetic.o: genetic.cpp genetic.h 
	g++ $(CFLAGS) -c genetic.cpp

iofunctions.o: iofunctions.cpp iofunctions.h
	g++ $(CFLAGS) -c iofunctions.cpp


clean:
	rm -f *.o urbanplanning
