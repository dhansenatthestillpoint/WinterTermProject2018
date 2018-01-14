gtkmmWindowExample: gtkmmWindowExample.cpp
	g++ -std=c++14 `pkg-config --cflags --libs gtk+-3.0` `pkg-config --cflags --libs gtkmm-3.0` -o gtkmmWindowExample gtkmmWindowExample.cpp
main: main.cpp MyArea.o fractal.o
	g++ -std=c++14 `pkg-config --cflags --libs gtkmm-3.0` -o main main.cpp MyArea.o fractal.o
MyArea.o: MyArea.cpp 
	g++ -std=c++14 `pkg-config --cflags --libs gtkmm-3.0` -c MyArea.cpp
fractal.o: fractal.cpp
	g++ -std=c++14 `pkg-config --cflags --libs gtkmm-3.0` -c fractal.cpp
clean:
	rm MyArea.o fractal.o main