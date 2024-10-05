#include "datastructures.hh"
#include "customtypes.hh"
#include <algorithm>  // For std::sort
#include <iostream>   // For error logging

Datastructures::Datastructures() {}

Datastructures::~Datastructures() {}

unsigned int Datastructures::get_bite_count()
{
    return bites_.size();
}

void Datastructures::clear_all()
{
    bites_.clear();
    contours.clear();
}

std::vector<BiteID> Datastructures::all_bites()
{
    std::vector<BiteID> all_bites;
    for (const auto& [id, info] : bites_) {
        all_bites.push_back(id);
    }
    return all_bites;
}

bool Datastructures::add_bite(BiteID id, const Name &name, Coord xy)
{
    if (bites_.find(id) != bites_.end() || coord_bite_map_.find(xy) != coord_bite_map_.end()) {
        return false;
    }

    bites_[id] = {name, xy};
    coord_bite_map_[xy] = id;

    return true;
}

Name Datastructures::get_bite_name(BiteID id)
{
    auto it = bites_.find(id);
    if (it == bites_.end()) {
        return NO_NAME;
    }
    return it->second.name;
}

Coord Datastructures::get_bite_coord(BiteID id)
{
    auto it = bites_.find(id);
    if (it == bites_.end()) {
        return NO_COORD;
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
    std::vector<std::pair<int, BiteID>> distance_id_pairs;

    for (const auto& [id, info] : bites_) {
        int x = info.coord.x;
        int y = info.coord.y;
        int distance_squared = x * x + y * y;
        distance_id_pairs.emplace_back(distance_squared, id);
    }

    std::sort(distance_id_pairs.begin(), distance_id_pairs.end(),
              [](const std::pair<int, BiteID>& a, const std::pair<int, BiteID>& b) {
                  return a.first < b.first;
              });

    std::vector<BiteID> sorted_bites;
    for (const auto& pair : distance_id_pairs) {
        sorted_bites.push_back(pair.second);
    }

    return sorted_bites;
}

BiteID Datastructures::find_bite_with_coord(Coord xy)
{
    auto it = coord_bite_map_.find(xy);
    if (it != coord_bite_map_.end()) {
        return it->second;
    }
    return NO_BITE;
}

bool Datastructures::change_bite_coord(BiteID id, Coord newcoord)
{
    auto it = bites_.find(id);
    if (it == bites_.end() || coord_bite_map_.find(newcoord) != coord_bite_map_.end()) {
        return false;
    }

    coord_bite_map_.erase(it->second.coord);
    it->second.coord = newcoord;
    coord_bite_map_[newcoord] = id;

    return true;
}

bool Datastructures::add_contour(ContourID id, const Name &name, ContourHeight height, std::vector<Coord> coords)
{
    if (id < 0 || contours.find(id) != contours.end()) {
        return false;
    }

    contours[id] = {name, height, coords, {}, {}};
    return true;
}

std::vector<ContourID> Datastructures::all_contours()
{
    std::vector<ContourID> all_contours;
    for (const auto& [id, info] : contours) {
        all_contours.push_back(id);
    }
    return all_contours;
}

Name Datastructures::get_contour_name(ContourID id)
{
    if (id < 0) {
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
    if (id < 0) {
        return {NO_COORD};
    }
    auto it = contours.find(id);
    if (it == contours.end()) {
        return {NO_COORD};
    }
    return it->second.coords;
}

ContourHeight Datastructures::get_contour_height(ContourID id)
{
    if (id < 0) {
        return NO_CONTOUR_HEIGHT;
    }
    auto it = contours.find(id);
    if (it == contours.end()) {
        return NO_CONTOUR_HEIGHT;
    }
    return it->second.height;
}

bool Datastructures::add_subcontour_to_contour(ContourID id, ContourID parentid)
{
    if (id < 0 || parentid < 0 || contours.find(id) == contours.end() || contours.find(parentid) == contours.end() || id == parentid) {
        return false;
    }

    ContourID current_id = parentid;
    while (current_id >= 0) {
        if (current_id == id) {
            return false;
        }
        current_id = contours[current_id].parentID;
    }

    contours[parentid].subcontours.insert(id);
    contours[id].parentID = parentid;

    return true;
}

bool Datastructures::add_bite_to_contour(BiteID bite_id, ContourID contour_id)
{
    if (contours.find(contour_id) == contours.end() || bites_.find(bite_id) == bites_.end()) {
        return false;
    }

    const auto& contour_coords = contours[contour_id].coords;
    auto iter = std::find(contour_coords.begin(), contour_coords.end(), bites_[bite_id].coord);
    if (iter != contour_coords.end() || contours[contour_id].bites.find(bite_id) != contours[contour_id].bites.end()) {
        return false;
    }

    contours[contour_id].bites.insert(bite_id);
    bites_[bite_id].owner = contour_id;

    return true;
}

std::vector<ContourID> Datastructures::get_bite_in_contours(BiteID id)
{
    if (bites_.find(id) == bites_.end()) {
        return {NO_CONTOUR};
    }

    std::vector<ContourID> result;
    ContourID owner = bites_[id].owner;
    if (owner == NO_CONTOUR) {
        return {};
    }

    while (owner != NO_CONTOUR) {
        result.push_back(owner);
        owner = contours[owner].parentID;
    }

    return result;
}

std::vector<ContourID> Datastructures::all_subcontours_of_contour(ContourID id)
{
    std::vector<ContourID> subcontours_vector;
    if (contours.find(id) == contours.end()) {
        return subcontours_vector;
    }

    const std::set<ContourID>& subcontours_set = contours[id].subcontours;
    subcontours_vector.assign(subcontours_set.begin(), subcontours_set.end());

    return subcontours_vector;
}

ContourID Datastructures::get_closest_common_ancestor_of_contours(ContourID id1, ContourID id2)
{
    if (contours.find(id1) == contours.end() || contours.find(id2) == contours.end()) {
        return NO_CONTOUR;
    }

    std::set<ContourID> ancestors;
    ContourID current = id1;
    while (current >= 0) {
        ancestors.insert(current);
        current = contours[current].parentID;
    }

    current = id2;
    while (current >= 0) {
        if (ancestors.count(current) > 0) {
            return current;
        }
        current = contours[current].parentID;
    }

    return NO_CONTOUR;
}

bool Datastructures::remove_bite(BiteID id)
{
    auto it = bites_.find(id);
    if (it == bites_.end()) {
        return false;
    }

    for (auto& [contour_id, contour_info] : contours) {
        contour_info.bites.erase(id);
    }

    coord_bite_map_.erase(it->second.coord);
    bites_.erase(it);

    return true;
}

std::vector<BiteID> Datastructures::get_bites_closest_to(Coord xy)
{
    std::vector<std::pair<int, BiteID>> distance_id_pairs;

    for (const auto& [id, info] : bites_) {
        int dx = info.coord.x - xy.x;
        int dy = info.coord.y - xy.y;
        int distance_squared = dx * dx + dy * dy;
        distance_id_pairs.emplace_back(distance_squared, id);
    }

    std::sort(distance_id_pairs.begin(), distance_id_pairs.end(),
              [](const std::pair<int, BiteID>& a, const std::pair<int, BiteID>& b) {
                  return a.first < b.first;
              });

    std::vector<BiteID> sorted_bites;
    for (const auto& pair : distance_id_pairs) {
        sorted_bites.push_back(pair.second);
    }

    return sorted_bites;
}
