// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include "customtypes.hh"
#include <utility>
#include <vector>

// Add your own STL includes below this comment

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <functional>
#include <set>
#include <queue>
#include <stack>

template <typename Type>
Type random_in_range(Type start, Type end);

// This is the class you are supposed to implement

class Datastructures
{
public:
  Datastructures();
  ~Datastructures();

  // Estimate of performance: O(1)
  // Short rationale for estimate: Accessing the size of a map is a direct
  // operation, resulting in O(1) time complexity.
  unsigned int get_bite_count();

  // Estimate of performance: O(n)
  // Short rationale for estimate: The data structure contains multiple containers
  // for bites and contours, clearing all data requires iterating over the entire
  // container to remove every element, making this an O(n) operation.
  void clear_all();

  // Estimate of performance: O(n)
  // Short rationale for estimate: This function returns a std::vector<BiteID>
  // by value, which may involve copying the entire vector. If the vector
  // contains n elements, copying it requires iterating over all n elements,
  // leading to O(n) time complexity.
  std::vector<BiteID> all_bites();

  // Estimate of performance: O(n)
  // Short rationale for estimate: find() (hash table lookup) and insertion
  // in `bites_map_` and `bites_coordinate_` are O(n) time in worst case.
  bool add_bite(BiteID id, const Name& name, Coord xy);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Accessing an element in an unordered_map
  // (a hash map) takes average constant time operation, but in the
  // worst case (due to hash collisions), it could take linear time.
  Name get_bite_name(BiteID id);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Accessing an element in an unordered_map
  // (a hash map) takes average constant time operation, but in the
 // worst case (due to hash collisions), it could take linear time.
  Coord get_bite_coord(BiteID id);

  // We recommend you implement the operations below only after implementing the
  // ones above

  // Estimate of performance: O(n * log(n))
  // Short rationale for estimate: The std::sort() function is the primary
  // factor that affects operation time, std::sort() operates in O(n * log(n))
  // time in the worst case.
  std::vector<BiteID> get_bites_alphabetically();

  // Estimate of performance: O(n * log(n))
  // Short rationale for estimate: The std::sort() function is the primary
  // factor that affects operation time, std::sort() operates in O(n * log(n))
  // time in the worst case.
  std::vector<BiteID> get_bites_distance_increasing();

  // Estimate of performance: O(n)
  // Short rationale for estimate: both find() and access operations on the
  // bites_coordinate_ map are constant time, O(1), leading to an overall
  // complexity of O(1) for the function.
  BiteID find_bite_with_coord(Coord xy);

  // Estimate of performance: O(n)
  // Short rationale for estimate: checking for existence in contours_map_ is
  // O(1), checking the height is O(1), but inserting n coordinates into
  // new_contour.c_coordinates takes O(n). Therefore, the overall complexity
  // is O(n).
  bool add_contour(ContourID id, const Name & name, ContourHeight height,
                   std::vector<Coord> coords);

  // Estimate of performance: O(n)
  // Short rationale for estimate: iterating through contours_map_ takes O(n)
  // to collect all ContourIDs, where n is the number of entries in the map.
  // Therefore, the overall complexity is O(n).
  std::vector<ContourID> all_contours();

  // Estimate of performance: O(n)
  // Short rationale for estimate: This function returns a std::vector<BiteID>
  // by value, which may involve copying the entire vector. If the vector
  // contains n elements, copying it requires iterating over all n elements,
  // leading to O(n) time complexity.
  Name get_contour_name(ContourID id);

  // Estimate of performance: O(n)
  // Short rationale for estimate: checking for the existence of the ContourID
  // in contours_map_ is O(1), and accessing the ordered_coords is also O(1).
  // Thus, the overall complexity is O(1).
  std::vector<Coord> get_contour_coords(ContourID id);

  // Estimate of performance: O(n)
  // Short rationale for estimate: checking for the existence of the ContourID
  // in contours_map_ is O(n), and accessing the c_height is O(1).
  // Thus, the overall complexity is O(n).
  ContourHeight get_contour_height(ContourID id);

  // Estimate of performance: O(n)
  // Short rationale for estimate: finding the parent and sub-contour in
  // contours_map_ is O(1), but checking if the sub-contour is already a
  // child of the parent requires a linear search through parent.children,
  // leading to an overall complexity of O(n).
  bool add_subcontour_to_contour(ContourID id, ContourID parentid);

  // Estimate of performance: O(n)
  // Short rationale for estimate: checking for existence in bites_map_,
  // contours_map_, and bite_to_contour_ is O(1) each, and the search in
  // contour_coordinates (a set) is also O(1) on average.
  // Thus, the overall complexity is O(1).
  bool add_bite_to_contour(BiteID biteid, ContourID parentid);

  // Estimate of performance: O(n)
  // Short rationale for estimate: checking if the BiteID exists is O(1),
  // and traversing the parent chain up to n contours requires O(n) time,
  // leading to an overall complexity of O(n).
  std::vector<ContourID> get_bite_in_contours(BiteID id);

  // Non-compulsory operations

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<ContourID> all_subcontours_of_contour(ContourID /*id*/);

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<BiteID> get_bites_closest_to(Coord /*xy*/);

  // Estimate of performance:
  // Short rationale for estimate:
  bool remove_bite(BiteID /*id*/);

  // Estimate of performance:
  // Short rationale for estimate:
  ContourID get_closest_common_ancestor_of_contours(ContourID /*id1*/,
                                                    ContourID /*id2*/);




 /**
   * ============================
   * ============================
   * ========== PRG2 ============
   * ============================
   * ============================
   */

  // Estimate of performance: O(log(n))
  // Short rationale for estimate: Searching maps is O(log n). Reversing and inserting coordinates is O(m), where m is the length of xy.
  bool add_connection(ConnectionID connectionid, BiteID id1, BiteID id2,
                      std::vector<Coord> xy);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Clearing all containers (connections, bites) requires linear passes through them.
  void clear_connections();

  // Estimate of performance: O(n)
  // Short rationale for estimate: Iterates over all connections to find matches, taking linear time.
  std::vector<BiteID> get_next_bites_from(BiteID id);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Linear search through connections to match id1 and id2.
  std::vector<ConnectionID> get_connections(BiteID id1 = NO_BITE, BiteID id2 = NO_BITE);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Retrieves and processes connection coordinates, linear with the number of coordinates.
  std::vector<Coord> get_connection_coords(BiteID biteid,
                                           ConnectionID connectionid);

  // Estimate of performance: O(n^2)
  // Short rationale for estimate: BFS explores each bite and connection once, linear in nodes and edges.
  std::vector<std::pair<Coord, Distance>> path_any(BiteID fromid, BiteID toid);

  // Non-compulsory operations

   // Non-compulsory operations

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<std::pair<Coord, Distance>> path_shortest(BiteID /*fromid*/,
                                                        BiteID /*toid*/);

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<std::pair<Coord, Distance>> path_least_bites(BiteID /*fromid*/,
                                                           BiteID /*toid*/);

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<std::pair<Coord, Distance>> path_least_uphill(BiteID /*fromid*/,
                                                            BiteID /*toid*/);
private:
  struct Bite
  {
      BiteID id;
      Name name;
      Coord coord;
      ContourID assigned_contour = NO_CONTOUR;
      int distance;
      std::vector<ConnectionID> bite_connections = {};
  };

  struct Contour
  {
      ContourID c_id;
      Name c_name;
      ContourHeight c_height;
      std::unordered_set<Coord> c_coordinates;
      std::vector<Coord> ordered_coords;
      std::vector<ContourID> children;
      std::vector<BiteID> c_bite;
      ContourID parent = NO_CONTOUR;

  };

  struct CompareName
  {
      bool operator()(const std::pair<Name, BiteID>& a,
                      const std::pair<Name, BiteID>& b) const
      {
          return (a.first != b.first) ? (a.first < b.first) : (a.second < b.second);
      }
  };

  struct CompareDistance
  {
      bool operator()(const std::tuple<int, int, BiteID>& a,
                      const std::tuple<int, int, BiteID>& b) const
      {
          return (std::get<0>(a) != std::get<0>(b)) ? (std::get<0>(a) < std::get<0>(b)) :
                 (std::get<1>(a) != std::get<1>(b)) ? (std::get<1>(a) < std::get<1>(b)) :
                                                      (std::get<2>(a) < std::get<2>(b));
      }
  };

  std::vector<BiteID> id_alphabetically_;
  std::set<std::pair<Name, BiteID>, CompareName> id_sorted_aphabetically_;
  std::vector<BiteID> id_distance_wise_;
  std::set<std::tuple<int, int, BiteID>, CompareDistance> id_sorted_by_distance_;
  std::vector<ContourID> contours_vectors_;
  std::unordered_map<BiteID, Bite> bites_map_;
  std::unordered_map<Coord, BiteID> bites_coordinate_;
  std::unordered_map<BiteID, ContourID> bite_to_contour_;
  std::unordered_map<ContourID, Contour> contours_map_;

  bool alphabetically_sorted_ = false;
  bool distance_sorted_ = false;

  /**
    * ============================
    * ============================
    * ========== PRG2 ============
    * ============================
    * ============================
    */

    struct Connection
    {
        ConnectionID id;
        BiteID start_id;
        BiteID end_id;
        std::vector<Coord> coords;
    };

    std::vector<Connection> connections_;
    std::vector<ConnectionID> conn_id_;
    std::unordered_map<ConnectionID, Connection> connections_map_;
    std::unordered_map<BiteID, std::unordered_map<BiteID, std::vector<Coord>>> graph;


};

#endif // DATASTRUCTURES_HH
