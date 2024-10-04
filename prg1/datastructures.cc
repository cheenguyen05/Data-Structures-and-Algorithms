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
#include <iostream>   // For error logging

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
  bites_.clear();
  contours.clear();
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
    if (id<0 || contours.find(id) != contours.end()) {
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
  if (id<0){
    return NO_NAME;
  }
  auto it = contours.find(id);
  if (it == contours.end()) {
  return NO_NAME;
  }
  return it->second.name;
}

std::vector<Coord> Datastructures::get_contour_coords(ContourID id)
{
  if (id<0){
    return {NO_COORD};
  }
  auto it = contours.find(id);
  if (it == contours.end()) {
      return {NO_COORD}; // Define NO_COORD appropriately
  }
  return it->second.coords;
}

ContourHeight Datastructures::get_contour_height(ContourID id)
{
  if (id<0){
    return NO_CONTOUR_HEIGHT;
  }
  // Check if the contour with the given ID exists
    auto it = contours.find(id);
    if (it == contours.end()) {
        return NO_CONTOUR_HEIGHT;
    } 
    return it->second.height; // Assuming the contour structure has a 'height' member
}

bool Datastructures::add_subcontour_to_contour(ContourID id, ContourID parentid)
{
    // Check for invalid IDs
    if (id < 0 || parentid < 0) {
        return false; // Invalid contour IDs
    }

    // Check if the contour to be added as subcontour exists
    auto subcontour_it = contours.find(id);
    if (subcontour_it == contours.end()) {
        return false; // Subcontour not found
    }

    // Check if the parent contour exists
    auto parent_it = contours.find(parentid);
    if (parent_it == contours.end()) {
        return false; // Parent contour not found
    }

    // Check for circular reference by traversing the parent chain
    ContourID current_id = parentid; // Start with the parent contour
    while (current_id >= 0) {
        // If the current ancestor is the subcontour, reject the addition
        if (current_id == id) {
            return false; // Cannot add a contour as its own subcontour or any of its ancestors
        }
        
        // Move up the hierarchy (you need to have a way to get the parent ID)
        auto ancestor_it = contours.find(current_id);
        if (ancestor_it == contours.end()) break; // If the parent is not found, break
        current_id = ancestor_it->second.parentID; // Move to the parent contour
    }

    // If all checks pass, add the subcontour to the parent contour
    parent_it->second.subcontours.push_back(id); // Assuming subcontours is a vector in ContourInfo
    subcontour_it->second.parentID = parentid; // Update parent reference in the subcontour structure
    return true; // Successfully added
}


bool Datastructures::add_bite_to_contour(BiteID biteid, ContourID contourid)
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
  {
  std::vector<ContourID> result; // To store the IDs of contours containing the bite
    // Iterate through all contours
    for (const auto& pair : contours) {
        const ContourID contour_id = pair.first; // Get the ContourID
        const ContourInfo& contour_info = pair.second; // Get the ContourInfo

        // Check if the contour contains the bite
        if (std::find(contour_info.bites.begin(), contour_info.bites.end(), id) != contour_info.bites.end()) {
            result.push_back(contour_id); // Add the ContourID to the result if the bite is found
        }
    }
    return result; // Return the vector of ContourIDs containing the bite
  }
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