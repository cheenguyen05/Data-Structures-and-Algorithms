/**
 * @brief The Datastructures class
 * STUDENTS: Modify the code below to implement the functionality of the class.
 * Also remove comments from the parameter names when you implement an operation
 * (Commenting out parameter name prevents compiler from warning about unused
 * parameters on operations you haven't yet implemented.)
 */

#include "datastructures.hh"
#include "customtypes.hh"
#include <random>
#include <cmath>


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
  return bites.size();
}

void Datastructures::clear_all()
{
  // Replace the line below with your implementation
  bites.clear();
}

std::vector<BiteID> Datastructures::all_bites()
{
  // Replace the line below with your implementation
  std::vector<BiteID> bite_ids;
  for (const auto& [id, info] : bites) {
    bite_ids.push_back(id);
  }
  return bite_ids;
}

bool Datastructures::add_bite(BiteID id, const Name &name, Coord xy)
{
  if (bites.find(id) != bites.end()) {
        return false;
    }
    std::shared_ptr<BiteInfo> new_bite = std::make_shared<BiteInfo>();
    new_bite->name = name;
    new_bite->coord = xy;
    bites[id] = new_bite;
    bites_by_coord[xy].push_back(id);
    bites_distance_increasing[std::sqrt(xy.x*xy.x + xy.y*xy.y)].push_back(id);
    bites_alphabetically[name].push_back(id);
    return true;
}

Name Datastructures::get_bite_name(BiteID id)
{
  if (bites.find(id) == bites.end()) {
        return NO_NAME;
    }
    return bites[id]->name;
}

Coord Datastructures::get_bite_coord(BiteID id)
{
  if (bites.find(id) == bites.end()) {
        return NO_COORD;
    }
    return bites[id]->coord;
}

std::vector<BiteID> Datastructures::get_bites_alphabetically()
{
  std::vector<BiteID> all_bites;
  for (auto it = bites_alphabetically.begin(); it != bites_alphabetically.end(); ++it) {
    for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
      all_bites.push_back(*it2);
    }
  }
  return all_bites;
}

std::vector<BiteID> Datastructures::get_bites_distance_increasing()
{
  std::vector<BiteID> all_bites;
    for (auto it = bites_distance_increasing.begin(); it != bites_distance_increasing.end(); ++it) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            all_bites.push_back(*it2);
        }
    }
    return all_bites;
}

BiteID Datastructures::find_bite_with_coord(Coord xy)
{
  auto it = bites_by_coord.find(xy);
    if (it != bites_by_coord.end() && !it->second.empty()) {
        return it->second.front();
    }
    return NO_BITE;
}

bool Datastructures::change_bite_coord(BiteID id, Coord newcoord)
{
  if (bites.find(id) == bites.end()) {
        return false;
    }
    Coord old_coord = bites[id]->coord;
    bites[id]->coord = newcoord;
    for (auto it = bites_by_coord[old_coord].begin(); it != bites_by_coord[old_coord].end(); ++it) {
        if (*it == id) {
            bites_by_coord[old_coord].erase(it);
            break;
        }
    }
    bites_by_coord[newcoord].push_back(id);
    for (auto it = bites_distance_increasing.begin(); it != bites_distance_increasing.end(); ++it) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            if (*it2 == id) {
                it->second.erase(it2);
                break;
            }
        }
    }
    bites_distance_increasing[std::sqrt(newcoord.x*newcoord.x + newcoord.y*newcoord.y)].push_back(id);
    return true;
}

bool Datastructures::add_contour(ContourID id, const Name & name, ContourHeight height,
                                 std::vector<Coord> coords)
{
  // Replace the line below with your implementation
  throw NotImplemented("add_contour");
}

std::vector<ContourID> Datastructures::all_contours()
{
    std::vector<ContourID> all_contours;
    for (auto it = contours.begin(); it != contours.end(); ++it) {
        all_contours.push_back(it->first);
    }
    return all_contours;
}

Name Datastructures::get_contour_name(ContourID id)
{
  if (contours.find(id) == contours.end()) {
        return NO_NAME;
    }
    return contours[id]->name;
}

std::vector<Coord> Datastructures::get_contour_coords(ContourID /*id*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("get_contour_coords");
}

ContourHeight Datastructures::get_contour_height(ContourID id)
{
    if (contours.find(id) == contours.end()) {
        return NO_CONTOUR_HEIGHT;
    }
    return contours[id]->height;
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


