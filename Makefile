

CFLAGS = -Wall -g

urbanplanning:  main.o genetic.o HillClimbing.o fitness.o iofunctions.o global.h
	g++ $(CFLAGS) main.o genetic.o HillClimbing.o fitness.o iofunctions.o -lm -o urbanplanning

main.o: main.cpp global.h
	g++ $(CFLAGS) -c main.cpp

genetic.o: genetic.cpp genetic.h
	g++ $(CFLAGS) -c genetic.cpp

HillClimbing.o: HillClimbing.cpp HillClimbing.h
	g++ $(CFLAGS) -c HillClimbing.cpp

fitness.o: fitness.cpp fitness.h
	g++ $(CFLAGS) -c fitness.cpp

iofunctions.o: iofunctions.cpp iofunctions.h
	g++ $(CFLAGS) -c iofunctions.cpp


clean:
	rm -f *.o urbanplanning
