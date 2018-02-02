#include "MyArea.h"


int main(int argc, char** argv)
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  Gtk::Window window;
  window.set_title("Magnificient, aren't they");
  window.set_default_size(WIDTH, HEIGHT);
  MyArea area;
  window.add(area);
  area.show();

  return app->run(window);
}

