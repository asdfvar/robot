CC = g++
FLAGS = -Wall
LINK = -lm -lglut

OBJ = main.o robot.o update.o map.o \
      drawmap.o drawrobot.o loadmap.o \
      collide.o gettime.o distance.o
EXE = robot
TRASH = robot.h.gch constants.h.gch

all: $(EXE)
$(EXE): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LINK) -o $(EXE)

main.o: main.cpp robot.h
	$(CC) $(FLAGS) main.cpp -c

update.o: update.cpp robot.h constants.h
	$(CC) $(FLAGS) robot.h constants.h update.cpp -c

drawrobot.o: drawrobot.cpp robot.h constants.h
	$(CC) $(FLAGS) robot.h constants.h drawrobot.cpp -c

drawmap.o: drawmap.cpp map.h
	$(CC) $(FLAGS) drawmap.cpp -c

%.o: %.cpp
	$(CC) $(FLAGS) $^ -c

clean:
	rm $(OBJ) $(EXE) $(TRASH)
