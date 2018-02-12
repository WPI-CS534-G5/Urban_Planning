

CFLAGS = -Wall -g

urbanplanning:  main.o genetic.o iofunctions.o 
	g++ $(CFLAGS) main.o genetic.o iofunctions.o -lm -o urbanplanning

main.o: main.cpp global.h
	g++ $(CFLAGS) -c main.cpp

genetic.o: genetic.cpp genetic.h global.h
	g++ $(CFLAGS) -c genetic.cpp

iofunctions.o: iofunctions.cpp iofunctions.h global.h
	g++ $(CFLAGS) -c iofunctions.cpp


clean:
	rm -f *.o urbanplanning
