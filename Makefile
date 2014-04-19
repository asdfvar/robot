CC = g++
FLAGS = -Wall

OBJ = main.o robot.o update.o map.o \
      drawmap.o drawrobot.o loadmap.o \
      collide.o gettime.o
EXE = robot
TRASH = robot.h.gch constants.h.gch

all: $(EXE)
$(EXE): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -lglut -o $(EXE)

main.o: main.cpp robot.h
	$(CC) $(FLAGS) -lglut -lm main.cpp -c

update.o: update.cpp robot.h constants.h
	$(CC) $(FLAGS) -lm robot.h constants.h update.cpp -c

drawrobot.o: drawrobot.cpp robot.h constants.h
	$(CC) $(FLAGS) -lm -lglut robot.h constants.h drawrobot.cpp -c

drawmap.o: drawmap.cpp map.h
	$(CC) $(FLAGS) -lglut drawmap.cpp -c

%.o: %.cpp
	$(CC) $(FLAGS) $^ -c

clean:
	rm $(OBJ) $(EXE) $(TRASH)
