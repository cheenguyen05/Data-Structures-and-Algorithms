/**
 * @brief The Datastructures class
 * STUDENTS: Modify the code below to implement the functionality of the class.
 * Also remove comments from the parameter names when you implement an operation
 * (Commenting out parameter name prevents compiler from warning about unused
 * parameters on operations you haven't yet implemented.)
 */

#include "datastructures.hh"
#include "customtypes.hh"
#include <algorithm>  // For std::sort


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
  std::vector<BiteID> all_bites;
  for (const auto& [id, info] : bites_) {
    all_bites.push_back(id);
  }
  return all_bites;
}

bool Datastructures::add_bite(BiteID id, const Name &name, Coord xy)
{
  // Replace the line below with your implementation
  // Check if the ID already exists
  if (bites_.find(id) != bites_.end()) {
      return false; // ID already exists
  }

  // Check if any bite exists with the same coordinates
  for (const auto& [existing_id, bite] : bites_) {
      if (bite.coord == xy) {
          return false; // Coordinate already taken
      }
  }

  // Add the bite if both checks pass
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
   std::vector<BiteID> all_bites;
    for (const auto& pair : bites_) {
        all_bites.push_back(pair.first);
    }
    
    std::sort(all_bites.begin(), all_bites.end(), [this](BiteID a, BiteID b) {
        return bites_[a].name < bites_[b].name;
    });
    
    return all_bites;
}

std::vector<BiteID> Datastructures::get_bites_distance_increasing()
{
  // Vector to hold pairs of <distance_squared, id>
    std::vector<std::pair<int, BiteID>> distance_id_pairs;

    // Fill the vector with distances (squared) and corresponding IDs
    for (const auto& [id, info] : bites_) {
        int x = info.coord.x;
        int y = info.coord.y;
        int distance_squared = x * x + y * y;  // Calculate distance squared
        distance_id_pairs.emplace_back(distance_squared, id);
    }

    // Sort the vector of pairs based on distances (squared)
    std::sort(distance_id_pairs.begin(), distance_id_pairs.end(),
              [](const std::pair<int, BiteID>& a, const std::pair<int, BiteID>& b) {
                  return a.first < b.first;  // Compare distances
              });

    // Vector to hold sorted IDs
    std::vector<BiteID> sorted_bites;
    for (const auto& pair : distance_id_pairs) {
        sorted_bites.push_back(pair.second);  // Get the ID from the pair
    }

    return sorted_bites;
}

BiteID Datastructures::find_bite_with_coord(Coord xy)
{
  // Iterate over all bites to find one with matching coordinates
    for (const auto& [id, info] : bites_) {
        if (info.coord == xy) {
            return id;  // Return the BiteID if coordinates match
        }
    }

    // If no bite is found, return NO_BITE (you may define it or use an appropriate value)
    return NO_BITE;
}

bool Datastructures::change_bite_coord(BiteID id, Coord newcoord)
{
  // Check if the BiteID exists
    auto it = bites_.find(id);
    if (it == bites_.end()) {
        return false; // The bite doesn't exist
    }

    // Ensure no other bite has the same new coordinates
    for (const auto& [existing_id, bite] : bites_) {
        if (existing_id != id && bite.coord == newcoord) {
            return false; // Another bite has the same coordinates
        }
    }

    // If all checks pass, update the coordinates
    it->second.coord = newcoord;
    return true;
}

bool Datastructures::add_contour(ContourID id, const Name &name, ContourHeight height,
                                 std::vector<Coord> coords)
{
  // Check if the ContourID already exists
    if (contours.find(id) != contours.end()) {
        return false;  // ContourID already exists
    }

    // Add the new contour
    contours[id] = {name, height, coords, {}, {}}; // Initialize subcontours and bites as empty vectors
    return true;  // Successfully added
}

std::vector<ContourID> Datastructures::all_contours()
{
  // Replace the line below with your implementation
  std::vector<ContourID> all_contours;
  for (const auto& [id, info] : contours) {
    all_contours.push_back(id);
  }
  return all_contours;
}

Name Datastructures::get_contour_name(ContourID id)
{
  // Replace the line below with your implementation
  auto it = contours.find(id);
  if (it == contours.end()) {
  return NO_NAME;
  }
  return it->second.name;
}

std::vector<Coord> Datastructures::get_contour_coords(ContourID id)
{
  auto it = contours.find(id);
  if (it == contours.end()) {
      return {NO_COORD}; // Define NO_COORD appropriately
  }
  return it->second.coords;
}

ContourHeight Datastructures::get_contour_height(ContourID id)
{
  // Check if the contour with the given ID exists
    auto it = contours.find(id);
    if (it != contours.end()) {
        return it->second.height; // Assuming the contour structure has a 'height' member
    } else {
    return NO_CONTOUR_HEIGHT;
    }
}

bool Datastructures::add_subcontour_to_contour(ContourID id,
                                               ContourID parentid)
{
  if (id == parentid){
    return false;
  }
  auto parent_it = contours.find(parentid);
  if (parent_it == contours.end()) {
      return false; // Parent contour not found
  }

  auto it = contours.find(id);
  if (it != contours.end()) {
      parent_it->second.subcontours.push_back(id); // Add the subcontour to the parent
      return true; // Successfully added subcontour
  } else {
      return false; // Subcontour ID not found
  }
}

bool Datastructures::add_bite_to_contour(BiteID /*biteid*/, ContourID /*contourid*/)
{
  // Validate the ContourID
    if (contourid < 0 || contours.find(contourid) == contours.end()) {
        return false; // ContourID is invalid or not found
    }

    // Validate the BiteID
    if (biteid < 0 || bites_.find(biteid) == bites_.end()) {
        return false; // BiteID is invalid or not found
    }

    // Add the BiteID to the contour's list of bites
    contours[contourid].bites.push_back(biteid); // Assuming ContourInfo has a member 'bites' which is a vector of BiteID
    return true; // Return true to indicate successful addition
}

std::vector<ContourID> Datastructures::get_bite_in_contours(BiteID id)
{
  std::vector<ContourID> contourIDs; // To store the IDs of contours containing the bite

    // Iterate through all contours
    for (const auto& contour_pair : contours) {
        const auto& contour = contour_pair.second;

        // Check if the current contour contains the given bite ID
        if (std::find(contour.bites.begin(), contour.bites.end(), id) != contour.bites.end()) {
            // If it does, add the contour ID to the result vector
            contourIDs.push_back(contour_pair.first); // Assuming contour_pair.first is the ContourID
        }
    }

    return contourIDs; // Return the vector of ContourIDs containing the bite
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