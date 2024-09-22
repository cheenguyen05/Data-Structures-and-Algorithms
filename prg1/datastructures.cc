/**
 * @brief The Datastructures class
 * STUDENTS: Modify the code below to implement the functionality of the class.
 * Also remove comments from the parameter names when you implement an operation
 * (Commenting out parameter name prevents compiler from warning about unused
 * parameters on operations you haven't yet implemented.)
 */

#include "datastructures.hh"
#include "customtypes.hh"

Datastructures::Datastructures()
{
  // Write any initialization you need here
}

Datastructures::~Datastructures()
{
  // Write any cleanup you need here
}

unsigned int Datastructures::get_bite_count()
{
  // Replace the line below with your implementation
  return bites_.size();
}

void Datastructures::clear_all()
{
  // Replace the line below with your implementation
  bites_.clear();
}

std::vector<BiteID> Datastructures::all_bites()
{
  // Replace the line below with your implementation
  std::vector<BiteID> bite_ids;
  for (const auto& [id, info] : bites_) {
    bite_ids.push_back(id);
  }
  return bite_ids;
}

bool Datastructures::add_bite(BiteID id, const Name &name, Coord xy)
{
  // Replace the line below with your implementation
  if (bites_.find(id) != bites_.end()) {
    return false;
  }
  bites_[id] = {name, xy};
  return true;
}

Name Datastructures::get_bite_name(BiteID id)
{
  // Replace the line below with your implementation
  auto it = bites_.find(id);
  if (it == bites_.end()) {
  return NO_NAME;
  }
  return it->second.name;
}

Coord Datastructures::get_bite_coord(BiteID id)
{
  // Replace the line below with your implementation
  auto it = bites_.find(id);
  if (it == bites_.end()) {
      return NO_COORD; // Define NO_COORD appropriately
  }
  return it->second.coord;
}

std::vector<BiteID> Datastructures::get_bites_alphabetically()
{
  // Replace the line below with your implementation
  throw NotImplemented("get_bites_alphabetically");
}

std::vector<BiteID> Datastructures::get_bites_distance_increasing()
{
  // Replace the line below with your implementation
  throw NotImplemented("get_bites_distance_increasing");
}

BiteID Datastructures::find_bite_with_coord(Coord /*xy*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("find_bite_with_coord");
}

bool Datastructures::change_bite_coord(BiteID /*id*/, Coord /*newcoord*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("change_bite_coord");
}

bool Datastructures::add_contour(ContourID /*id*/, const Name & /*name*/, ContourHeight /*height*/,
                                 std::vector<Coord> /*coords*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("add_contour");
}

std::vector<ContourID> Datastructures::all_contours()
{
  // Replace the line below with your implementation
  throw NotImplemented("all_contours");
}

Name Datastructures::get_contour_name(ContourID /*id*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("get_contour_name");
}

std::vector<Coord> Datastructures::get_contour_coords(ContourID /*id*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("get_contour_coords");
}

ContourHeight Datastructures::get_contour_height(ContourID /*id*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("get_contour_height");
}

bool Datastructures::add_subcontour_to_contour(ContourID /*id*/,
                                               ContourID /*parentid*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("add_subcontour_to_contour");
}

bool Datastructures::add_bite_to_contour(BiteID /*biteid*/, ContourID /*contourid*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("add_bite_to_contour");
}

std::vector<ContourID> Datastructures::get_bite_in_contours(BiteID /*id*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("get_bite_in_contours");
}

std::vector<ContourID>
Datastructures::all_subcontours_of_contour(ContourID /*id*/)
{
  throw NotImplemented("all_subcontours_of_contour");
}

ContourID
Datastructures::get_closest_common_ancestor_of_contours(ContourID /*id1*/,
                                                        ContourID /*id2*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("get_closest_common_ancestor_of_contours");
}

bool Datastructures::remove_bite(BiteID /*id*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("remove_bite");
}

std::vector<BiteID> Datastructures::get_bites_closest_to(Coord /*xy*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("get_bites_closest_to");
}


