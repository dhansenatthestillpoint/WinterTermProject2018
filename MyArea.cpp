#include "MyArea.h"
#include "fractal.h"
#include <stdlib.h> 
#include "light_and_gravity.h"
#include <iostream> //for debugging
#define DEBUG true

MyArea::MyArea()
{
  if(DEBUG) std::cout << "starting up myArea\n";
  //runs the timer, but I have no idea what goes on behind the scenes
  Glib::signal_timeout().connect( sigc::mem_fun(*this, &MyArea::on_timeout), TICKMS );
  //initialize pixbuf
  pixbuf = Gdk::Pixbuf::create_from_file("assets/sunrise512.png");
  //initialize ships n shit
  std::vector<Entity *> * allEntities = new std::vector<Entity *>();
  if(DEBUG) std::cout << "Pixbuf and entity vector initialized\n";
  SolarSystem * solarsystem = new SolarSystem();
  solarsystem->add(new ConstantLight(Color(30,30,50)));
  Sun *  sun  = new Sun (Vec4f(0,0,0), Color(300, 250, 200), 100); //i have no idea what mass is reasonable
  if(DEBUG) std::cout << "about to load textures \n";
  sun->shipmodel = new ObjectMap("Sun.obj");
  
  if(DEBUG) std::cout << "loaded a texture\n";
  solarsystem->add(sun);
  allEntities->push_back(sun);

  Planet * saturn = new Planet(sun, sun, Color(70,70,30),20, Vec4f(100,20,0), 3);
  saturn->shipmodel = new ObjectMap("Saturn.obj");
  solarsystem->add(saturn);
  allEntities->push_back(saturn);
  std::cout<<"loaded planets\n";

  Camera * camera = new Camera(Vec4f(150, 0, 0), Vec4f(0, 0, 225),10, 500, 2, 2);
  renderer = new Renderer (allEntities, camera, solarsystem);

  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();


  int rowstride = pixbuf->get_rowstride();
  int nchannels = pixbuf->get_n_channels();

  renderer->set_pixbuf(pixbuf,  rowstride,  nchannels,  width, height);

  std::cout <<"loaded renderer\n";

}

MyArea::~MyArea()
{
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();


  int rowstride = pixbuf->get_rowstride();
  int nchannels = pixbuf->get_n_channels();

  //set values
  //  update(pixbuf, rowstride, nchannels);

  renderer->render(0.0);
  //pixbuf to cairo                                                             
  Gdk::Cairo::set_source_pixbuf (cr,pixbuf , 0, 0);
  //draw the cairo object                                                       
  cr->paint();


  return true;
}


bool MyArea::on_timeout()
{

  auto win = get_window();
  if (win)
    {
      Gdk::Rectangle r(0, 0, get_allocation().get_width(),
		       get_allocation().get_height());
      win->invalidate_rect(r, false);
    }
  return true;
}
