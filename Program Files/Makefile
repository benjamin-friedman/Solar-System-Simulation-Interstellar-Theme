CC = g++
CFLAGS = -std=c++17 -Wall -Werror -pedantic
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
OBJECTS = main.o CelestialBody.o Universe.o

all: NBody
NBody: $(OBJECTS)
	$(CC) $(CFLAGS) -o NBody $(OBJECTS) $(SFMLFLAGS)
main.o: main.cpp CelestialBody.h Universe.h
	$(CC) $(CFLAGS) -c main.cpp -o main.o 
CelestialBody.o: CelestialBody.cpp CelestialBody.h
	$(CC) $(CFLAGS) -c CelestialBody.cpp -o CelestialBody.o
Universe.o: Universe.cpp Universe.h
	$(CC) $(CFLAGS) -c Universe.cpp -o Universe.o
clean:
	rm NBody $(OBJECTS)
