CC = g++
FLAGS = -Wall

OBJ = main.o robot.o update.o
EXE = robot

all: $(EXE)
$(EXE): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(EXE)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp robot.h -c

robot.o: robot.cpp robot.h
	$(CC) $(FLAGS) robot.cpp robot.h -c

update.o: update.cpp robot.h
	$(CC) $(FLAGS) -lm update.cpp -c

clean:
	rm $(OBJ) $(EXE)
