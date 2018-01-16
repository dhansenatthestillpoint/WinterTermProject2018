
main: main.cpp MyArea.o fractal.o
	g++ -std=c++14 `pkg-config --cflags --libs gtkmm-3.0` -o main main.cpp MyArea.o fractal.o
MyArea.o: MyArea.cpp 
	g++ -std=c++14 `pkg-config --cflags --libs gtkmm-3.0` -c MyArea.cpp
fractal.o: fractal.cpp
	g++ -std=c++14 `pkg-config --cflags --libs gtkmm-3.0` -c fractal.cpp

lightingtest: lightingtest.cpp vec4.o light.o
        g++ -std=c++14 lightingtest.cpp -o lightingtest vec4.o light.o
vec4.o: vec4.cpp
        g++ -std=c++14 -c vec4.cpp 

light.o: light.cpp
	g++ -std=c++14 -c light.cpp
clean:
	rm MyArea.o fractal.o main lightingtest vec4.o light.o