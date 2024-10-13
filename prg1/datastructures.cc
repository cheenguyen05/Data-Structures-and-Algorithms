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
#include <climits>

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

    // Sort by name, then by BiteID to ensure a stable sort
    std::sort(all_bites.begin(), all_bites.end(), [this](BiteID a, BiteID b) {
        if (bites_[a].name == bites_[b].name) {
            return a < b; // or however BiteID should be compared
        }
        return bites_[a].name < bites_[b].name;
    });

    return all_bites;
}


std::vector<BiteID> Datastructures::get_bites_distance_increasing()
{
    std::vector<std::tuple<int, int, BiteID>> bite_info;
    for(const auto& pair: bites_){
        int distance = abs(pair.second.coord.x) + abs(pair.second.coord.y);
        bite_info.emplace_back(distance,pair.second.coord.y,pair.first);
    }

    std::sort(bite_info.begin(), bite_info.end());
    std::vector<BiteID> sorted_bites;
    for(const auto& [distance, y, id] : bite_info){
        sorted_bites.push_back(id);
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

    auto& parent = parent_it->second;
    auto& subcontour = subcontour_it->second;

    if(subcontour.parentID != NO_CONTOUR){
        return false;
    }

    if(parent.subcontours.find(id) != parent.subcontours.end()){
        return false;
    }

    if(abs(subcontour.height - parent.height) != 1
            || abs(subcontour.height) < abs(parent.height)){
        return false;
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
        return false; // Contour doesn't exist
    }

    // Check if the bite exists
    if (bites_.find(bite_id) == bites_.end()) {
        return false; // Bite doesn't exist
    }

    const auto& contour_coords = contours[contour_id].coords;
    auto iter = std::find(contour_coords.begin(),contour_coords.end(),bites_[bite_id].coord);
    if(iter == contour_coords.end()) return false;

    if(contours[contour_id].bites.find(bite_id) != contours[contour_id].bites.end()){
        return false;
    }

    contours[contour_id].bites.insert(bite_id);
    bites_[bite_id].owner = contour_id;
    return true; // Bite was already in the contour
}

std::vector<ContourID> Datastructures::get_bite_in_contours(BiteID id)
{
    if(bites_.find(id) == bites_.end()) return {NO_CONTOUR};
    std::vector<ContourID> result; // To store the IDs of contours containing the bite

    ContourID owner = bites_[id].owner;
    if(owner == NO_CONTOUR) return {};
    while (owner != NO_CONTOUR) {
        result.push_back(owner);
        owner = contours[owner].parentID;
    }

    return result; // Return the vector of ContourIDs containing the bite
}

std::vector<ContourID> Datastructures::all_subcontours_of_contour(ContourID id)
{
    std::vector<ContourID> all_subcontours;

    // Check if the contour ID is valid
    if (contours.find(id) == contours.end()) {
        return {NO_CONTOUR}; // Return a special value indicating no contour
    }

    // Get the direct subcontours
    const std::set<ContourID>& direct_subcontours = contours[id].subcontours;

    // Recursively gather subcontours of each direct subcontour
    for (const ContourID& sub_id : direct_subcontours) {
        std::vector<ContourID> indirect_subcontours = all_subcontours_of_contour(sub_id);
        all_subcontours.insert(all_subcontours.end(), indirect_subcontours.begin(), indirect_subcontours.end());
    }

    // Add the direct subcontours at the end
    all_subcontours.insert(all_subcontours.end(), direct_subcontours.begin(), direct_subcontours.end());

    return all_subcontours;
}

ContourID Datastructures::get_closest_common_ancestor_of_contours(ContourID id1, ContourID id2) {
    // Define NO_CONTOUR appropriately
    const ContourID NO_CONTOUR = -1;

    // Check if both contour IDs are valid
    if (contours.find(id1) == contours.end() || contours.find(id2) == contours.end()) {
        return NO_CONTOUR;
    }

    // Use a map to keep track of the ancestors of id1 and their depths
    std::unordered_map<ContourID, int> ancestors;
    int depth = 0;

    // Find all ancestors of contour id1 and store their depths
    ContourID current = id1;
    while (current != NO_CONTOUR) {
        ancestors[current] = depth++;
        current = contours[current].parentID; // Move to the parent contour
    }

    // Now, traverse the ancestors of id2 to find the closest common ancestor
    current = id2;
    depth = 0;
    ContourID closest_common_ancestor = NO_CONTOUR;
    int min_depth = INT_MAX;

    while (current != NO_CONTOUR) {
        if (ancestors.count(current) > 0 && ancestors[current] < min_depth) {
            closest_common_ancestor = current;
            min_depth = ancestors[current];
        }
        current = contours[current].parentID; // Move to the parent contour
        depth++;
    }

    return closest_common_ancestor;
}


bool Datastructures::remove_bite(BiteID id) 
{
    // Check if the bite exists
    if (bites_.find(id) == bites_.end()) {
        return false; // Bite not found
    }

    // Remove the bite from relevant contours directly (using bite_to_contours_map_)
    if (bite_to_contours_map_.find(id) != bite_to_contours_map_.end()) {
        for (ContourID contour_id : bite_to_contours_map_[id]) {
            contours[contour_id].bites.erase(id); // Efficient removal from set
        }
        bite_to_contours_map_.erase(id); // Remove mapping of the bite to contours
    }

    // Remove the bite from coord_bite_map_
    coord_bite_map_.erase(bites_[id].coord);

    // Remove the bite from the bites_ map
    bites_.erase(id);

    return true; // Successfully removed
}


std::vector<BiteID> Datastructures::get_bites_closest_to(Coord xy)
{
    std::vector<BiteID> closest_bites;
    std::vector<BiteID> all_bites;

    // Collect all BiteIDs
    for (const auto& [id, info] : bites_) {
        all_bites.push_back(id);
    }

    // Sort based on integer distance (squared to avoid sqrt()) and tie-breaking on coordinates and BiteID
    std::sort(all_bites.begin(), all_bites.end(),
              [&](BiteID id1, BiteID id2) {
                  const Coord& coord1 = bites_.at(id1).coord;
                  const Coord& coord2 = bites_.at(id2).coord;

                  // Compute squared distances to avoid floating-point operations
                  int dist1_squared = (coord1.x - xy.x) * (coord1.x - xy.x) + (coord1.y - xy.y) * (coord1.y - xy.y);
                  int dist2_squared = (coord2.x - xy.x) * (coord2.x - xy.x) + (coord2.y - xy.y) * (coord2.y - xy.y);

                  if (dist1_squared != dist2_squared) {
                      // Sort by distance if distances are different
                      return dist1_squared < dist2_squared;
                  } else {
                      // Tie-breaking by x-coordinate, then y-coordinate, and finally by BiteID
                      if (coord1.x != coord2.x) {
                          return coord1.x < coord2.x;
                      }
                      if (coord1.y != coord2.y) {
                          return coord1.y < coord2.y;
                      }
                      return id1 < id2;
                  }
              });

    // If there are more than 3 bites, return the top 3 closest
    size_t count = std::min(static_cast<size_t>(3), all_bites.size());
    closest_bites.insert(closest_bites.end(), all_bites.begin(), all_bites.begin() + count);

    return closest_bites;
}


