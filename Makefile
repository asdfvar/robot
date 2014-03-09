CC = g++
FLAGS = -Wall

OBS = main.o robot.o
EXE = robot

all: $(EXE)
$(EXE): $(OBS)
	$(CC) $(FLAGS) $(OBS) -o $(EXE)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp robot.h -c

robot.o: robot.cpp robot.h
	$(CC) $(FLAGS) robot.cpp robot.h -c
