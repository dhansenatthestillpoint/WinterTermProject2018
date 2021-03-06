
main: main.cpp MyArea.o fractal.o Entity.o vec4.o objectloader.o rasterizer.o renderer.o light_and_gravity.o color.o camera.o
	g++ -std=c++14 `pkg-config --cflags --libs gtkmm-3.0` -o main main.cpp MyArea.o fractal.o Entity.o vec4.o objectloader.o rasterizer.o renderer.o light_and_gravity.o color.o camera.o
MyArea.o: MyArea.cpp 
	g++ -std=c++14 `pkg-config --cflags --libs gtkmm-3.0` -c MyArea.cpp
fractal.o: fractal.cpp
	g++ -std=c++14 `pkg-config --cflags --libs gtkmm-3.0` -c fractal.cpp

Entity: Entity.cpp Entity.h vec4.o
	g++ -std=c++14 -o Entity Entity.cpp vec4.o

<<<<<<< HEAD
SpaceLoader: SpaceLoader.cpp spaceloader.h
	g++ -std=c++14 -o SpaceLoader SpaceLoader.cpp
=======
Entity.o: Entity.cpp
	g++ -std=c++14 -c Entity.cpp
>>>>>>> refs/remotes/origin/master

lightingtest: lightingtest.cpp vec4.o light.o
        g++ -std=c++14 lightingtest.cpp -o lightingtest vec4.o light.o

vec4.o: vec4.cpp
        g++ -std=c++14 -c vec4.cpp 

vectortest: vec4.o vectortest.cpp
	g++ -std=c++14 vectortest.cpp -o vectortest vec4.o 

light.o: light.cpp
	g++ -std=c++14 -c light.cpp
objectloadertest: objectloadertest.cpp objectloader.o vec4.o light_and_gravity.o color.o
	g++  -std=c++14  -o objectloadertest objectloadertest.cpp objectloader.o vec4.o color.o
objectloader.o: objectloader.cpp
	 g++ -std=c++14 -c objectloader.cpp
rasterizer.o: rasterizer.cpp
	g++ -std=c++14 `pkg-config --cflags --libs gtkmm-3.0` -c rasterizer.cpp
renderer.o: renderer.cpp
	g++ -std=c++14 `pkg-config --cflags --libs gtkmm-3.0` -c renderer.cpp
light_and_gravity.o: light_and_gravity.cpp
	g++ -std=c++14 -c light_and_gravity.cpp
color.o: color.cpp
	g++ -std=c++14 -c color.cpp
camera.o: camera.cpp
	g++ -std=c++14 -c camera.cpp

clean:
	rm *.o  main lightingtest objectloadertest vectortest

