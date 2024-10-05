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

    // Use the map for checking if the coordinates are already in use
    if (coord_bite_map_.find(xy) != coord_bite_map_.end()) {
        return false; // Coordinates already taken
    }

    // Add the bite to the bites_ map and coord_bite_map_
    bites_[id] = {name, xy};
    coord_bite_map_[xy] = id; // Store the coordinates for quick lookup

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
    // Use the coord_bite_map_ for quick lookup by coordinates
    auto it = coord_bite_map_.find(xy);
    if (it != coord_bite_map_.end()) {
        return it->second; // Return the BiteID if found
    }
    
    return NO_BITE; // Define NO_BITE appropriately
}


bool Datastructures::change_bite_coord(BiteID id, Coord newcoord)
{
    // Check if the BiteID exists
    auto it = bites_.find(id);
    if (it == bites_.end()) {
        return false; // The bite doesn't exist
    }

    // Ensure no other bite has the same new coordinates
    if (coord_bite_map_.find(newcoord) != coord_bite_map_.end()) {
        return false; // Another bite has the same coordinates
    }

    // Remove the old coordinates from the map
    coord_bite_map_.erase(it->second.coord);

    // Update the coordinates in bites_ and coord_bite_map_
    it->second.coord = newcoord;
    coord_bite_map_[newcoord] = id;

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

    // Check if the subcontour exists
    auto subcontour_it = contours.find(id);
    if (subcontour_it == contours.end()) {
        return false; // Subcontour not found
    }

    // Check if the parent contour exists
    auto parent_it = contours.find(parentid);
    if (parent_it == contours.end()) {
        return false; // Parent contour not found
    }

    // Prevent adding itself as a subcontour (self-reference)
    if (id == parentid) {
        return false; // Cannot add a contour as its own subcontour
    }

    // Prevent circular references
    ContourID current_id = parentid;
    while (current_id >= 0) {
        if (current_id == id) {
            return false; // Circular reference detected
        }
        current_id = contours[current_id].parentID; // Move to the parent contour
    }

    // Add the subcontour and set the parent ID
    parent_it->second.subcontours.insert(id);  // Use a set for subcontours
    subcontour_it->second.parentID = parentid;

    return true;
}


bool Datastructures::add_bite_to_contour(BiteID bite_id, ContourID contour_id) {
    // Check if the contour exists
    if (contours.find(contour_id) == contours.end()) {
        std::cerr << "Contour not found." << std::endl;
        return false; // Contour doesn't exist
    }

    // Check if the bite exists
    if (bites_.find(bite_id) == bites_.end()) {
        std::cerr << "Bite not found." << std::endl;
        return false; // Bite doesn't exist
    }

    // Add bite to contour's set of bites
    if (contours[contour_id].bites.insert(bite_id).second) {
        std::cout << "Added '" << bites_[bite_id].name << "' to contour '" << contours[contour_id].name << "'" << std::endl;
        return true; // Successfully added
    }

    std::cerr << "Bite already exists in contour." << std::endl;
    return false; // Bite was already in the contour
}

std::vector<ContourID> Datastructures::get_bite_in_contours(BiteID id)
{
    std::vector<ContourID> result; // To store the IDs of contours containing the bite
    // Iterate through all contours
    for (const auto& pair : contours) {
        const ContourID contour_id = pair.first; // Get the ContourID
        const ContourInfo& contour_info = pair.second; // Get the ContourInfo

        // Check if the contour contains the bite
        if (contour_info.bites.count(id) > 0) {
            result.push_back(contour_id); // Add the ContourID to the result if the bite is found
        }
    }
    return result; // Return the vector of ContourIDs containing the bite
}

std::vector<ContourID> Datastructures::all_subcontours_of_contour(ContourID id)
{
    std::vector<ContourID> subcontours_vector;

    // Check if the contour ID is valid
    if (contours.find(id) == contours.end()) {
        return subcontours_vector; // Return an empty vector
    }

    // Get the subcontours for the given contour ID (subcontours is now a set)
    const std::set<ContourID>& subcontours_set = contours[id].subcontours;

    // Convert set to vector
    subcontours_vector.assign(subcontours_set.begin(), subcontours_set.end());

    return subcontours_vector; // Return the vector of subcontour IDs
}


ContourID
Datastructures::get_closest_common_ancestor_of_contours(ContourID id1,
                                                        ContourID id2)
{
  // Check if both contour IDs are valid
    if (contours.find(id1) == contours.end()) {
        std::cerr << "Error: Contour ID " << id1 << " not found." << std::endl;
        return NO_CONTOUR; // Define NO_CONTOUR appropriately
    }

    if (contours.find(id2) == contours.end()) {
        std::cerr << "Error: Contour ID " << id2 << " not found." << std::endl;
        return NO_CONTOUR; // Define NO_CONTOUR appropriately
    }

    // Use a set to keep track of the ancestors of id1
    std::set<ContourID> ancestors;

    // Find all ancestors of contour id1
    ContourID current = id1;
    while (current >= 0) {
        ancestors.insert(current);
        current = contours[current].parentID; // Move to the parent contour
    }

    // Now, traverse the ancestors of id2 to find the closest common ancestor
    current = id2;
    while (current >= 0) {
        if (ancestors.count(current) > 0) {
            return current; // Return the first common ancestor found
        }
        current = contours[current].parentID; // Move to the parent contour
    }

    std::cerr << "No common ancestor found for contours " << id1 << " and " << id2 << "." << std::endl;
    return NO_CONTOUR; // Define NO_CONTOUR appropriately
}

bool Datastructures::remove_bite(BiteID id)
{
    // Check if the bite exists
    auto it = bites_.find(id);
    if (it == bites_.end()) {
        return false; // Bite not found
    }

    // Remove the bite from all contours
    for (auto& [contour_id, contour_info] : contours) {
        contour_info.bites.erase(id); // Efficient removal from a set
    }

    // Remove the bite from the bites_ map and coord_bite_map_
    coord_bite_map_.erase(it->second.coord);
    bites_.erase(it); // Remove from bites_

    return true;
}

std::vector<BiteID> Datastructures::get_bites_closest_to(Coord xy)
{
    std::vector<std::pair<int, BiteID>> distance_id_pairs;

    for (const auto& [id, info] : bites_) {
        int dx = info.coord.x - xy.x;
        int dy = info.coord.y - xy.y;
        int distance_squared = dx * dx + dy * dy; // Squared distance calculation
        distance_id_pairs.emplace_back(distance_squared, id);
    }

    // Sort the bites based on the squared distances
    std::sort(distance_id_pairs.begin(), distance_id_pairs.end(),
              [](const std::pair<int, BiteID>& a, const std::pair<int, BiteID>& b) {
                  return a.first < b.first; 
              });

    // Extract sorted BiteIDs
    std::vector<BiteID> closest_bites;
    for (const auto& pair : distance_id_pairs) {
        closest_bites.push_back(pair.second);
    }

    return closest_bites;
}
