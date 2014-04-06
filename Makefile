CC = g++
FLAGS = -Wall

OBJ = main.o robot.o update.o map.o \
      drawmap.o drawrobot.o loadmap.o
EXE = robot
TRASH = robot.h.gch

all: $(EXE)
$(EXE): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -lglut -o $(EXE)

main.o: main.cpp robot.h
	$(CC) $(FLAGS) -lglut -lm main.cpp -c

robot.o: robot.cpp robot.h
	$(CC) $(FLAGS) robot.cpp -c

update.o: update.cpp robot.h
	$(CC) $(FLAGS) -lm robot.h update.cpp -c

drawrobot.o: drawrobot.cpp robot.h
	$(CC) $(FLAGS) -lm -lglut drawrobot.cpp -c

map.o: map.cpp map.h
	$(CC) $(FLAGS) map.cpp -c

loadmap.o: loadmap.cpp map.h
	$(CC) $(FLAGS) loadmap.cpp -c

drawmap.o: drawmap.cpp map.h
	$(CC) $(FLAGS) -lglut drawmap.cpp -c

clean:
	rm $(OBJ) $(EXE) $(TRASH)
