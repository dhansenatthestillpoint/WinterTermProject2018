#ifndef TICKUPDATE_H
#define TICKUPDATE_H

#include "light_and_gravity.h"
#include "Entity.h"
#include <vector>

class TickUpdate{
 public:
  char **inputlist;
  //list of all user and AI commands to be executed since the start of this one up until the start of this one
  SolarSystem *solarlist;
  //list of all planetary/asteroid/star bodies and its various satellites
  Entity *entitylist;
  //ships and missiles, essenitally anything that can take input from the player or AI
  Entity *entitylibrary;
  //a list of all unique entities for quick and easy lookup of class variables for spawning ships in
  std::unordered_map<string, std::vector<Entity>> collisionmap;
  //hashmap used to fill constructor
  TickUpdate(string entitylistfilename, string scenariofile);
  //reads in a list of entitties and initializes entity list with their respective properties. A scenario file is a list of entities with some optionally non default parameters, this list of celestial bodies and ships are used to initially fill solar system and entity list. 
  
  double cradius;
  //the largest radius by which we round to check for collision, most likely determined by the missile with the largest proximity trigger
  string cround(Entity inputentity);
  //rounds and converts a position vector to a string based on cradius
  void collisioncheck(double coll);
  //performs collision checks by checking 27 buckets in and around the ship for other vessels. Any further actions to be taken that result from collision get added to this iput list. total runtime is linerar for all ships

  void execscripts();
  //essentially a large case statement which alters entities in entitylist based on input from the players and AI, such function could hypotethiclally be tied to key presses but for now this seems like a more efficient way to program it? Will get back to this one. Linar time based on number of commands in script list. 

  void update();
  //calls the update function in every entity. For celestial bodies this means simply updating position and valocity. For ships and and other AI player based stuff this means not only updating velocity/positionrotation/ etc but also numerious class interactions such as heat and stuff. Linear runtime based on the number of elements in entitylist and solarlist.
  
  void drawthing();
  //renders an image to the screen. I'm not sure what parameters you want it to take so currently it takes a big array of null. While I don't know what the runtime is for this one my hope is to make .5 past lightspeed

  void updatetick();
  //wrapper function that calls collisioncheck(), execscripts(), update(), and drawthing() in that order()
};

