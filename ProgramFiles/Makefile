# Author: Benjamin G. Friedman
# GitHub: benjamin-friedman
# Date: 01/19/2023
# File: Makefile
# Description: Makefile for the solar system simulation program.


CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic #-Og -g -fsanitize=undefined
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
EXE1 = SolarSystemSimulation
OBJ1 = Main.o Planet.o SolarSystem.o
EXES = $(EXE1)


all: $(EXES)
.PHONY: all clean


$(EXE1): $(OBJ1)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-rm $(EXES) $(wildcard *.o)