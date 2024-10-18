/**
 * @brief The Datastructures class
 * STUDENTS: Modify the code below to implement the functionality of the class.
 * Also remove comments from the parameter names when you implement an operation
 * (Commenting out parameter name prevents compiler from warning about unused
 * parameters on operations you haven't yet implemented.)
 */

#include "datastructures.hh"
#include "customtypes.hh"
#include <algorithm>  
#include <iostream> 
#include <queue>

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

ContourID
Datastructures::get_closest_common_ancestor_of_contours(ContourID id1,
                                                        ContourID id2)
{
    // Check if both contours exist
    auto it1 = contours.find(id1);
    auto it2 = contours.find(id2);
    if (it1 == contours.end() || it2 == contours.end()) {
        return NO_CONTOUR;
    }

    // Lambda function to get the parent chain of a contour
    auto get_parent_chain = [this](ContourID c) -> std::vector<ContourID> {
        std::vector<ContourID> result;
        auto it = contours.find(c);

        // Traverse up the parent chain until there is no parent
        while (it != contours.end() && it->second.parentID != NO_CONTOUR) {
            result.push_back(it->second.parentID);
            it = contours.find(it->second.parentID); // Move to the parent
        }

        return result;
    };

    // Get the parent chains for both contours
    auto c1_parent = get_parent_chain(id1);
    auto c2_parent = get_parent_chain(id2);

    // Find the first common ancestor in the parent chains
    for (const auto& c1 : c1_parent) {
        if (std::find(c2_parent.begin(), c2_parent.end(), c1) != c2_parent.end()) {
            return c1;
        }
    }

    return NO_CONTOUR; // No common ancestor found
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
    std::vector<std::pair<int, BiteID>> distances;

    for (const auto& pair : bites_) {  // Change bite_map to bites_
        const auto& bite_coord = pair.second.coord; // Access coord from BiteInfo
        // Compute the Manhattan distance
        int manhattan_distance = std::abs(bite_coord.x - xy.x) + std::abs(bite_coord.y - xy.y);
        distances.emplace_back(manhattan_distance, pair.first);
    }

    std::sort(distances.begin(), distances.end(), [&](const auto &a, const auto &b) {
        if (a.first != b.first) return a.first < b.first;
        const auto& coordA = bites_.at(a.second).coord; // Access coord from BiteInfo
        const auto& coordB = bites_.at(b.second).coord; // Access coord from BiteInfo

        if (coordA.y != coordB.y) return coordA.y < coordB.y;
        return a.second < b.second;
    });

    std::vector<BiteID> closest_bites;
    for (size_t i = 0; i < std::min<size_t>(3, distances.size()); ++i) {
        closest_bites.push_back(distances[i].second);
    }

    return closest_bites;
}

/**
 * ============================
 * ============================
 * ========== PRG2 ============
 * ============================
 * ============================
 */

bool Datastructures::add_connection(ConnectionID connectionid, BiteID id1, BiteID id2, std::vector<Coord> xy) 
{
    // Ensure both bites exist
    if (bites_.find(id1) == bites_.end() || bites_.find(id2) == bites_.end()) {
        return false; // One or both bites don't exist
    }

    // Ensure the connection doesn't already exist
    if (connections_.find(connectionid) != connections_.end()) {
        return false; // Connection already exists
    }

    // Add the connection
    connections_[connectionid] = {id1, id2, xy};

    // Update adjacency lists for each bite (assuming bidirectional connection)
    adj_list_[id1].insert(id2);
    adj_list_[id2].insert(id1);

    return true; // Successfully added
}

void Datastructures::clear_connections() 
{
    connections_.clear();     // Remove all connections
    adj_list_.clear();        // Clear the adjacency lists
}

std::vector<BiteID> Datastructures::get_next_bites_from(BiteID id)
{
    // Check if the bite exists
    if (bites_.find(id) == bites_.end()) {
        return {}; // Bite doesn't exist, return an empty list
    }

    std::vector<BiteID> next_bites;

    // Get the adjacent bites from the adjacency list
    if (adj_list_.find(id) != adj_list_.end()) {
        next_bites.assign(adj_list_[id].begin(), adj_list_[id].end());
    }

    return next_bites.empty() ? std::vector<BiteID>{NO_BITE} : next_bites; // return NO_BITE if empty
}

std::vector<ConnectionID> Datastructures::get_connections(BiteID id1, BiteID id2)
{
    std::vector<ConnectionID> result;

    for (const auto& [connection_id, connection_info] : connections_) {
        const BiteID& bite1 = std::get<0>(connection_info);
        const BiteID& bite2 = std::get<1>(connection_info);

        // Check if both bites are involved in the connection
        if ((bite1 == id1 && bite2 == id2) || (bite1 == id2 && bite2 == id1)) {
            result.push_back(connection_id);
        }
    }

    return result.empty() ? std::vector<ConnectionID>{NO_CONNECTION} : result; // return NO_CONNECTION if empty
}

std::vector<Coord> Datastructures::get_connection_coords(BiteID biteid, ConnectionID connectionid)
{
    auto it = connections_.find(connectionid);
    if (it == connections_.end()) {
        return {}; // Return empty vector if connection doesn't exist
    }

    const auto& connection_info = it->second;
    BiteID bite1 = std::get<0>(connection_info);
    BiteID bite2 = std::get<1>(connection_info);

    // Check if the given bite is part of the connection
    if (bite1 == biteid || bite2 == biteid) {
        return std::get<2>(connection_info); // Return the coordinates
    }

    return {}; // Return empty vector if bite is not part of the connection
}

std::vector<std::pair<Coord, Distance>> Datastructures::path_any(BiteID fromid, BiteID toid)
{
    // If either bite is not present in the graph
    if (bites_.find(fromid) == bites_.end() || bites_.find(toid) == bites_.end()) {
        return {}; // No path found
    }

    // BFS setup
    std::queue<BiteID> to_visit;
    std::map<BiteID, BiteID> came_from; // To reconstruct the path
    std::map<BiteID, int> distance;

    to_visit.push(fromid);
    came_from[fromid] = NO_BITE; // Mark the start point
    distance[fromid] = 0;

    while (!to_visit.empty()) {
        BiteID current = to_visit.front();
        to_visit.pop();

        if (current == toid) {
            // Path found, now reconstruct the path
            std::vector<std::pair<Coord, Distance>> path;
            BiteID step = toid;
            while (step != NO_BITE) {
                path.push_back({bites_[step].coord, distance[step]});
                step = came_from[step];
            }
            std::reverse(path.begin(), path.end()); // Reverse to get path from `fromid` to `toid`
            return path;
        }

        for (const BiteID& neighbor : adj_list_[current]) {
            if (came_from.find(neighbor) == came_from.end()) {
                to_visit.push(neighbor);
                came_from[neighbor] = current;
                distance[neighbor] = distance[current] + 1;
            }
        }
    }

    return {}; // No path found
}

// Non-compulsory operations
std::vector<std::pair<Coord, Distance>> Datastructures::path_shortest(BiteID /*fromid*/,
                                                                      BiteID /*toid*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("path_shortest");
}
std::vector<std::pair<Coord, Distance>> Datastructures::path_least_bites(BiteID /*fromid*/,
                                                                         BiteID /*toid*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("path_least_bites");
}
std::vector<std::pair<Coord, Distance>> Datastructures::path_least_uphill(BiteID /*fromid*/,
                                                                          BiteID /*toid*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("path_least_uphill");
}