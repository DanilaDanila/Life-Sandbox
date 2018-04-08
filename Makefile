CC=g++
SFML=-lsfml-graphics -lsfml-system -lsfml-window
GL=-framework OpenGL -framework GLUT

all: main.o gui.o god_window.o main_window.o my_text.o renderer.o executor.o lake.o fish.o
	$(CC) main.o gui.o god_window.o main_window.o my_text.o renderer.o executor.o lake.o fish.o libPolygons.a $(SFML) $(GL) -o Life\ Sandbox
main.o: main.cpp
	$(CC) -c main.cpp
gui.o: gui.hpp gui.cpp
	$(CC) -c gui.cpp
god_window.o: god_window.hpp god_window.cpp
	$(CC) -c god_window.cpp
main_window.o: main_window.hpp main_window.cpp
	$(CC) -c main_window.cpp
my_text.o: my_text.hpp my_text.cpp
	$(CC) -c my_text.cpp
renderer.o: renderer.hpp renderer.cpp
	$(CC) -c renderer.cpp
executor.o: executor.hpp executor.cpp
	$(CC) -c executor.cpp
lake.o: lake.hpp lake.cpp
	$(CC) -c lake.cpp
fish.o: fish.hpp fish.cpp
	$(CC) -c fish.cpp
clear:
	rm *.o *.gch