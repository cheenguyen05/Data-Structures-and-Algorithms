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
    return bites_map_.size();
}

void Datastructures::clear_all()
{
    bites_map_.clear();
    bites_coordinate_.clear();
    contours_map_.clear();
    contours_vectors_.clear();
    bite_to_contour_.clear();
    id_alphabetically_.clear();
    id_distance_wise_.clear();
    clear_connections();
}

std::vector<BiteID> Datastructures::all_bites()
{
    return id_alphabetically_;
}

bool Datastructures::add_bite(BiteID id, const Name & name, Coord xy)
{
    auto iter = bites_map_.find(id);
    if(iter != bites_map_.end()) return false;

    auto iter_xy = bites_coordinate_.find(xy);
    if(iter_xy != bites_coordinate_.end()) return false;

    Bite new_bite = {id, name, xy, NO_CONTOUR, 0};
    new_bite.distance = std::abs(xy.x) + std::abs(xy.y);

    bites_map_[id] = new_bite;
    bites_coordinate_[xy] = id;
    id_alphabetically_.push_back(id);
    id_sorted_aphabetically_.insert({name, id});
    id_sorted_by_distance_.insert({new_bite.distance, xy.y, id});
    id_distance_wise_.push_back(id);

    alphabetically_sorted_ = false;
    distance_sorted_ = false;

    return true;
}

Name Datastructures::get_bite_name(BiteID id)
{
    auto iter = bites_map_.find(id);
    if(iter != bites_map_.end())
    {
        return iter->second.name;
    }
    return NO_NAME;
}


Coord Datastructures::get_bite_coord(BiteID id)
{
    auto iter = bites_map_.find(id);
    if(iter != bites_map_.end())
    {
        return iter->second.coord;
    }
    return NO_COORD;
}

std::vector<BiteID> Datastructures::get_bites_alphabetically()
{
    if(!alphabetically_sorted_)
    {
        id_alphabetically_.clear();
        id_alphabetically_.reserve(bites_map_.size());

        for(auto& [pair, op] : id_sorted_aphabetically_)
        {
            id_alphabetically_.push_back(op);
        }

        alphabetically_sorted_ = true;
    }

    return id_alphabetically_;
}

std::vector<BiteID> Datastructures::get_bites_distance_increasing()
{
    if (!distance_sorted_)
    {
        id_distance_wise_.clear();
        id_distance_wise_.reserve(bites_map_.size());

        for (auto [distance, y, id] : id_sorted_by_distance_)
        {
            id_distance_wise_.push_back(id);
        }

        distance_sorted_ = true;
    }
    return id_distance_wise_;
}

BiteID Datastructures::find_bite_with_coord(Coord xy)
{
    auto iter_coord = bites_coordinate_.find(xy);
    if(iter_coord != bites_coordinate_.end())
    {
        return bites_coordinate_[xy];
    }
    return NO_BITE;
}

bool Datastructures::add_contour(ContourID id, const Name & name, ContourHeight height,
                                 std::vector<Coord> coords)
{
    if (contours_map_.find(id) != contours_map_.end()) return false;
    if (height > MAX_CONTOUR_HEIGHT|| height < - MAX_CONTOUR_HEIGHT) return false;
    Contour new_contour = {id, name, height, {}, coords, {}, {}};
    for (const auto &coord : coords)
    {
        new_contour.c_coordinates.insert(coord);
    }
    contours_map_[id] = new_contour;
    contours_vectors_.push_back(id);

    return true;
}

std::vector<ContourID> Datastructures::all_contours()
{
    return contours_vectors_;
}

Name Datastructures::get_contour_name(ContourID id)
{
    auto iter_id = contours_map_.find(id);
    if(iter_id != contours_map_.end())
    {
        return iter_id->second.c_name;
    }
    return NO_NAME;
}

std::vector<Coord> Datastructures::get_contour_coords(ContourID id)
{
    auto iter_id = contours_map_.find(id);
    if(iter_id != contours_map_.end())
    {
        return iter_id->second.ordered_coords;//
    }
    return {NO_COORD};
}

ContourHeight Datastructures::get_contour_height(ContourID id)
{
    if(contours_map_.find(id) != contours_map_.end())
    {
        return contours_map_[id].c_height;
    }
    return NO_CONTOUR_HEIGHT;

}

bool Datastructures::add_subcontour_to_contour(ContourID id,
                                               ContourID parentid)
{
    auto parent_iter = contours_map_.find(parentid);
    auto sub_iter = contours_map_.find(id);

    if (sub_iter == contours_map_.end() || parent_iter == contours_map_.end())
    {
        return false;
    }

    Contour& parent = parent_iter->second;
    Contour& sub = sub_iter->second;

    if (sub.parent != NO_CONTOUR) {
        return false;
    }

    if (std::find(parent.children.begin(), parent.children.end(), id) != parent.children.end()) {
        return false;
    }

    if (std::abs(sub.c_height - parent.c_height) != 1
            || std::abs(sub.c_height) < std::abs(parent.c_height)) {
        return false;
    }

    sub.parent = parentid;
    parent.children.push_back(id);
    return true;
}

bool Datastructures::add_bite_to_contour(BiteID biteid, ContourID parentid)
{
    if(bites_map_.find(biteid) == bites_map_.end()) return false;
    if(contours_map_.find(parentid) == contours_map_.end()) return false;

    if(bite_to_contour_.find(biteid) != bite_to_contour_.end()) return false;

    const auto& contour_coordinates = contours_map_[parentid].c_coordinates;
    if(contour_coordinates.find(bites_map_[biteid].coord) == contour_coordinates.end())
    {
        return false;
    }

    bites_map_[biteid].assigned_contour = parentid;
    contours_map_[parentid].c_bite.push_back(biteid);
    bite_to_contour_[biteid] = parentid;

    return true;
}

std::vector<ContourID> Datastructures::get_bite_in_contours(BiteID id)
{
    if(bites_map_.find(id) == bites_map_.end()) return {NO_CONTOUR};

    std::vector<ContourID> contour_family;
    ContourID current_contour = bites_map_[id].assigned_contour;

    if (current_contour == NO_CONTOUR) return {};

    while (current_contour != NO_CONTOUR)
    {
        contour_family.push_back(current_contour);
        current_contour = contours_map_[current_contour].parent;
    }
    return contour_family;
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
    throw NotImplemented("get_closest_common_ancestor_of");
}


bool Datastructures::remove_bite(BiteID /*id*/)
{
    throw NotImplemented("remove_bite");
}


std::vector<BiteID> Datastructures::get_bites_closest_to(Coord /*xy*/)
{
    throw NotImplemented("get_bites_closest_to");
}


/**
 * ============================
 * ============================
 * ========== PRG2 ============
 * ============================
 * ============================
 */

bool Datastructures::add_connection(ConnectionID connectionid, BiteID id1, BiteID id2,
                                    std::vector<Coord> xy)
{
    auto iter1 = bites_map_.find(id1);
    auto iter2 = bites_map_.find(id2);
    if(iter1 == bites_map_.end() || iter2 == bites_map_.end()) return false;

    auto iter_con = connections_map_.find(connectionid);
    if(iter_con != connections_map_.end()) return false;

    Connection new_connection = {connectionid, id1, id2, xy};
    connections_map_[connectionid] = new_connection;
    connections_.push_back(new_connection);
    conn_id_.push_back(connectionid);
    iter1->second.bite_connections.push_back(connectionid);
    iter2->second.bite_connections.push_back(connectionid);

    graph[id1][id2] = xy;

    std::reverse(xy.begin(), xy.end());
    graph[id2][id1] = xy ;
    return true;
}

void Datastructures::clear_connections()
{
    connections_map_.clear();
    connections_.clear();
    conn_id_.clear();
    graph.clear();
    for(auto& [id, bite] : bites_map_)
    {
        bite.bite_connections.clear();
    }
}

std::vector<BiteID> Datastructures::get_next_bites_from(BiteID id)
{
    if(bites_map_.find(id) == bites_map_.end()) return {NO_BITE};

    std::vector<BiteID> results;
    for (auto it = connections_map_.begin(); it != connections_map_.end(); ++it)
    {
        const Connection& connection = it->second;
        if (connection.start_id == id)
        {
            if(std::find(results.begin(), results.end(), connection.end_id) != results.end())
            {
                continue;
            }
            results.push_back(connection.end_id);
        }
        else if (connection.end_id == id)
        {
            if(std::find(results.begin(), results.end(), connection.start_id) != results.end())
            {
                continue;
            }
            results.push_back(connection.start_id);
        }
    }
    return results;
}

std::vector<ConnectionID> Datastructures::get_connections(BiteID id1, BiteID id2)
{
    std::vector<ConnectionID> result;

    if(id1 == NO_BITE && id2 == NO_BITE) return conn_id_;
    if(id1 != NO_BITE && id2 == NO_BITE)
    {
        auto iter1 = bites_map_.find(id1);
        if(iter1 == bites_map_.end()) return {NO_CONNECTION};

        for (const auto& [conn_id, connection] : connections_map_)
        {
            if (connection.start_id == id1 || connection.end_id == id1)
            {
                result.push_back(conn_id);
            }
        }
    }

    if(id1 != NO_BITE && id2 != NO_BITE)
    {
        auto iter1 = bites_map_.find(id1);
        auto iter2 = bites_map_.find(id2);
        if(iter1 == bites_map_.end() || iter2 == bites_map_.end())
        {
            return {NO_CONNECTION};
        }
        for (const auto& [conn_id, connection] : connections_map_)
        {
            if ((connection.start_id == id1 && connection.end_id == id2)
                    || (connection.start_id == id2 && connection.end_id == id1))
            {
                result.push_back(conn_id);
            }
        }
    }

    return result;
}

std::vector<Coord> Datastructures::get_connection_coords(BiteID biteid,
                                                         ConnectionID connectionid)
{
    std::vector<Coord> result;
    auto iter_con = connections_map_.find(connectionid);
    if(iter_con == connections_map_.end()) return {NO_COORD};

    if(iter_con->second.start_id != biteid && iter_con->second.end_id != biteid)
    {
        return {NO_COORD};
    }

    if(iter_con->second.start_id == biteid)
    {
        result.push_back(bites_map_[biteid].coord);
        for(const auto& coord : iter_con->second.coords)
        {
            result.push_back(coord);
        }
        result.push_back(bites_map_[iter_con->second.end_id].coord);

    }
    else if(iter_con->second.end_id == biteid)
    {
        result.push_back(bites_map_[biteid].coord);
        for (int i = iter_con->second.coords.size() - 1; i >= 0; --i)
        {
            result.push_back(iter_con->second.coords[i]);
        }
        result.push_back(bites_map_[iter_con->second.start_id].coord);
    }

    return result;
}

std::vector<std::pair<Coord, Distance>> Datastructures::path_any(BiteID fromid, BiteID toid)
{
    if (fromid == toid) return {};

    if (bites_map_.find(fromid) == bites_map_.end() || bites_map_.find(toid) == bites_map_.end())
    {
        return { { NO_COORD, NO_DISTANCE } };
    }


    std::unordered_map<BiteID, BiteID> parent;
    std::queue<BiteID> queue;
    std::unordered_set<BiteID> visited;
    queue.push(fromid);
    visited.insert(fromid);
    parent[fromid] = NO_BITE;

    while (!queue.empty())
    {
        BiteID current = queue.front();
        queue.pop();
        if (current == toid)
        {
            std::vector<BiteID> path;
            BiteID step = toid;
            while (step != NO_BITE)
            {
                path.push_back(step);
                step = parent[step];
            }
            std::reverse(path.begin(), path.end());

            std::vector<std::pair<Coord, Distance>> result;
            Distance total_distance = 0;
            Coord previous_coord = bites_map_[path[0]].coord;
            result.push_back({previous_coord, total_distance});

            for (size_t i = 1; i < path.size(); ++i)
            {
                const Coord& current_coord = bites_map_[path[i]].coord;
                auto connection_coords = graph[path[i-1]][path[i]];
                for (const auto& intermediate_coord : connection_coords)
                {
                    Distance dist = std::abs(previous_coord.x - intermediate_coord.x)
                                  + std::abs(previous_coord.y - intermediate_coord.y);
                    total_distance += dist;
                    result.push_back({intermediate_coord, total_distance});
                    previous_coord = intermediate_coord;
                }
                Distance dist = std::abs(previous_coord.x - current_coord.x)
                              + std::abs(previous_coord.y - current_coord.y);
                total_distance += dist;
                result.push_back({current_coord, total_distance});
                previous_coord = current_coord;
            }
            return result;
        }

        for (const auto& neighbor : graph[current])
        {
            if (visited.find(neighbor.first) == visited.end())
            {
                visited.insert(neighbor.first);
                parent[neighbor.first] = current;
                queue.push(neighbor.first);
            }
        }
    }

    return {};

}
// Non-compulsory operations
std::vector<std::pair<Coord, Distance>> Datastructures::path_shortest(BiteID fromid,
                                                                      BiteID toid)
{
    // Edge case: if start and end are the same, return an empty path
    if (fromid == toid) return {};

    // Edge case: if either bite doesn't exist, return NO_COORD and NO_DISTANCE
    if (bites_map_.find(fromid) == bites_map_.end() || bites_map_.find(toid) == bites_map_.end())
    {
        return { { NO_COORD, NO_DISTANCE } };
    }

    // Priority queue for Dijkstra: (distance_from_start, current_bite)
    std::priority_queue<std::pair<Distance, BiteID>,
                        std::vector<std::pair<Distance, BiteID>>,
                        std::greater<>> pq;

    // Map to store the shortest distance to each bite
    std::unordered_map<BiteID, Distance> dist;
    for (const auto& [bite_id, bite] : bites_map_)
    {
        dist[bite_id] = NO_DISTANCE;  // Initialize distances to "infinity"
    }
    dist[fromid] = 0;  // Distance to start node is 0

    // Map to store the previous bite in the shortest path
    std::unordered_map<BiteID, BiteID> prev;

    // Push the starting bite into the priority queue
    pq.push({0, fromid});

    while (!pq.empty())
    {
        auto [current_dist, current_bite] = pq.top();
        pq.pop();

        // If we reached the target bite, reconstruct the path
        if (current_bite == toid) break;

        // Get all neighboring bites from the current bite
        for (const auto& connection_id : bites_map_[current_bite].bite_connections)
        {
            const auto& connection = connections_map_[connection_id];
            BiteID neighbor_bite = (connection.start_id == current_bite) ? connection.end_id : connection.start_id;

            // Calculate the distance to the neighboring bite
            Distance additional_dist = std::abs(bites_map_[current_bite].coord.x
                                              - bites_map_[neighbor_bite].coord.x)
                                     + std::abs(bites_map_[current_bite].coord.y
                                              - bites_map_[neighbor_bite].coord.y);
            Distance new_dist = current_dist + additional_dist;

            // If a shorter path to neighbor_bite is found, update distance and previous bite
            if (new_dist < dist[neighbor_bite])
            {
                dist[neighbor_bite] = new_dist;
                prev[neighbor_bite] = current_bite;
                pq.push({new_dist, neighbor_bite});
            }
        }
    }

    // If the target bite was not reached, return NO_COORD and NO_DISTANCE
    if (dist[toid] == NO_DISTANCE) return { { NO_COORD, NO_DISTANCE } };

    // Reconstruct the path from "toid" back to "fromid"
    std::vector<std::pair<Coord, Distance>> path;
    BiteID current_bite = toid;
    Distance total_distance = 0;

    while (current_bite != fromid)
    {
        BiteID previous_bite = prev[current_bite];
        Coord current_coord = bites_map_[current_bite].coord;
        Distance segment_distance = std::abs(bites_map_[previous_bite].coord.x
                                             - current_coord.x)
                                    + std::abs(bites_map_[previous_bite].coord.y
                                             - current_coord.y);

        path.push_back({current_coord, segment_distance});
        total_distance += segment_distance;
        current_bite = previous_bite;
    }

    // Don't forget to add the starting bite
    path.push_back({bites_map_[fromid].coord, total_distance});

    // The path is built backwards, so reverse it
    std::reverse(path.begin(), path.end());

    return path;
}
std::vector<std::pair<Coord, Distance>> Datastructures::path_least_bites(BiteID /*fromid*/,
                                                                         BiteID /*toid*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("path_least_bites");
}
std::vector<std::pair<Coord, Distance>> Datastructures::path_least_uphill(BiteID fromid,
                                                                          BiteID toid)
{
    if (fromid == toid) return {};

    // Check if both bites exist
    if (bites_map_.find(fromid) == bites_map_.end() || bites_map_.find(toid) == bites_map_.end())
    {
        return { { NO_COORD, NO_DISTANCE } };
    }

    std::unordered_map<BiteID, std::pair<Distance, Distance>> distance_uphill;
    std::priority_queue<std::tuple<Distance,Distance,BiteID>> priority_queue;
    distance_uphill[fromid] = {0,0};
    priority_queue.push({0,0, fromid});

    while(!priority_queue.empty())
    {
        auto[uphill, distance, current_id] = priority_queue.top();
        priority_queue.pop();

        for(const auto& [neighbor, coordinates] : graph[current_id])
        {
            Distance path_uphill,path_distance = 0;
            Coord previous_coord = bites_map_[current_id].coord;
            ContourHeight previous_height =
        }


    }

}
