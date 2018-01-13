gtkmmWindowExample: gtkmmWindowExample.cpp
	g++ -std=c++14 `pkg-config --cflags --libs gtk+-3.0` `pkg-config --cflags --libs gtkmm-3.0` -o gtkmmWindowExample gtkmmWindowExample.cpp
clean:
	rm gtkmmWindowExample