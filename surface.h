// surface.h
// 
// Copyright 1996-2001 Per Abrahamsen and S�ren Hansen
// Copyright 2000-2001 KVL.
//
// This file is part of Daisy.
// 
// Daisy is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
// 
// Daisy is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser Public License for more details.
// 
// You should have received a copy of the GNU Lesser Public License
// along with Daisy; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


#include "uzmodel.h"
#include <memory>

class Frame;
class FrameSubmodel;
class Log;
class SoilWater;
class Soil;
class Geometry;
class Geometry1D;
class Treelog;

class Surface
{
  struct Implementation;
  std::auto_ptr<Implementation> impl;

public:
  // Communication with soil water.
  enum top_t { forced_pressure, forced_flux, limited_water, soil };
  top_t top_type (const Geometry&, size_t edge) const;
  double q_top (const Geometry&, size_t edge, const double dt) const; // [cm/h]
  double h_top (const Geometry&, size_t edge) const; // [cm]
  void accept_top (double amount, const Geometry&, size_t edge, 
                   double dt, Treelog&);
  size_t last_cell (const Geometry&, size_t edge) const;

  // Column.
  double runoff_rate () const; // [h^-1]
  double mixing_resistance () const; // [h/mm]
  double mixing_depth () const; // [cm]
  
  // Ridge.
  void update_water (const Geometry1D& geo,
                     const Soil&, const std::vector<double>& S_,
		     std::vector<double>& h_, std::vector<double>& Theta_,
		     std::vector<double>& q, const std::vector<double>& q_p,
                     double dt);

  // Manager.
  void set_detention_capacity (double);
  void ridge (const Geometry1D& geo,
              const Soil& soil, const SoilWater& soil_water,
	      const FrameSubmodel&);
  void unridge ();

  // Simulation.
  void output (Log&) const;
  void update_pond_average (const Geometry& geo);
  void tick (Treelog&, 
             double PotSoilEvaporationWet, 
             double PotSoilEvaporationDry, 
             double flux_in /* [mm/h] */,
             double temp /* [dg C] */, const Geometry& geo,
             const Soil&, const SoilWater&,
             double soil_T /* [dg C] */, double dt /* [h] */);

  // Communication with bioclimate.
  double ponding_average () const; // [mm]
  double ponding_max () const;     // [mm]
  double temperature () const;     // [dg C]
  double EpFactor () const;        // []
  double albedo (const Geometry&, const Soil&, const SoilWater&) const;
  double exfiltration (double dt) const; // [mm/h]
  double evap_soil_surface () const; // [mm/h]
  double evap_pond (double dt, Treelog&) const; // [mm/h]
  void put_ponding (double pond);	// [mm]

  // Create.
  void initialize (const Geometry&);
  static void load_syntax (Frame&);
  Surface (const FrameSubmodel& par);
  ~Surface ();
};

