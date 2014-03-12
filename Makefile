CC = g++
FLAGS = -Wall

OBJ = main.o robot.o update.o map.o
EXE = robot

all: $(EXE)
$(EXE): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(EXE)

main.o: main.cpp robot.h
	$(CC) $(FLAGS) main.cpp -c

robot.o: robot.cpp robot.h
	$(CC) $(FLAGS) robot.cpp -c

update.o: update.cpp robot.h
	$(CC) $(FLAGS) -lm update.cpp -c

map.o: map.cpp map.h
	$(CC) $(FLAGS) map.cpp -c

clean:
	rm $(OBJ) $(EXE)
