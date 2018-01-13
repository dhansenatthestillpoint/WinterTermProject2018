
main: main.cpp MyArea.o
	g++ -std=c++14 `pkg-config --cflags --libs gtkmm-3.0` -o main main.cpp MyArea.o
MyArea.o: MyArea.cpp
	g++ -std=c++14 `pkg-config --cflags --libs gtkmm-3.0` -c MyArea.cpp

clean:
	rm main MyArea.o