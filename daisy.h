// daisy.h

#ifndef DAISY_H
#define DAISY_H

#include "time.h"

class Manager;
class Weather;
class Groundwater;
class Log;
class Filter;
class ColumnList;
class Syntax;
class AttributeList;

class Daisy
{
  // Content.
public:
  Log& log;
  Time time;
  Manager& manager;
  Weather& weather;
  Groundwater& groundwater;
  ColumnList& columns;

  // Simulation.
public:
  void run();
  void output (Log&, const Filter*) const;

  // Create and Destroy.
public:
  static void load_syntax (Syntax&);
  Daisy (const AttributeList&);
  ~Daisy ();
};

#endif DAISY_H

