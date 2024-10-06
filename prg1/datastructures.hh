// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include "customtypes.hh"
#include <utility>
#include <vector>
#include <unordered_map>

// Add your own STL includes below this comment
#include <string>
#include <set>

template <typename Type>
Type random_in_range(Type start, Type end);

// This is the class you are supposed to implement

class Datastructures
{
public:
  Datastructures();
  ~Datastructures();

  // Estimate of performance: O(1)
  // Short rationale for estimate: Returns the size of the unordered map, which is a constant time operation.
  unsigned int get_bite_count();

  // Estimate of performance: O(n)
  // Short rationale for estimate: Clears both the unordered maps and sets, which takes linear time in the number of bites and contours.
  void clear_all();

  // Estimate of performance: O(n)
  // Short rationale for estimate: Iterates through all bites in the unordered map, which takes linear time.
  std::vector<BiteID> all_bites();

  // Estimate of performance: O(1)
  // Short rationale for estimate: Insertion into an unordered map is constant on average.
  bool add_bite(BiteID id, const Name &name, Coord xy);

  // Estimate of performance: O(1)
  // Short rationale for estimate: Accessing an element in an unordered map by key takes constant time.
  Name get_bite_name(BiteID id);

  // Estimate of performance: O(1)
  // Short rationale for estimate: Same as `get_bite_name`, this involves constant time lookup in the unordered map.
  Coord get_bite_coord(BiteID id);

  // Estimate of performance: O(n log n)
  // Short rationale for estimate: Sorting the bites by name requires sorting the list, which is O(n log n).
  std::vector<BiteID> get_bites_alphabetically();

  // Estimate of performance: O(n log n)
  // Short rationale for estimate: Sorting the bites by distance takes O(n log n) time.
  std::vector<BiteID> get_bites_distance_increasing();

  // Estimate of performance: O(1)
  // Short rationale for estimate: If `coord_bite_map_` is used, this is a constant-time lookup.
  BiteID find_bite_with_coord(Coord xy);

  // Estimate of performance: O(1)
  // Short rationale for estimate: Updating the coordinate in an unordered map is a constant time operation.
  bool change_bite_coord(BiteID id, Coord newcoord);

  // Estimate of performance: O(1)
  // Short rationale for estimate: Adding an entry to an unordered map takes constant time.
  bool add_contour(ContourID id, const Name & name, ContourHeight height, std::vector<Coord> coords);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Iterates through all contours, which takes linear time.
  std::vector<ContourID> all_contours();

  // Estimate of performance: O(1)
  // Short rationale for estimate: Accessing an element in an unordered map by key is a constant time operation.
  Name get_contour_name(ContourID id);

  // Estimate of performance: O(1)
  // Short rationale for estimate: Returns the vector of coordinates in constant time as it's stored in the map.
  std::vector<Coord> get_contour_coords(ContourID id);

  // Estimate of performance: O(1)
  // Short rationale for estimate: Accessing the height in an unordered map is a constant time operation.
  ContourHeight get_contour_height(ContourID id);

  // Estimate of performance: O(1)
  // Short rationale for estimate: Adding a subcontour to a set is a constant-time operation.
  bool add_subcontour_to_contour(ContourID id, ContourID parentid);

  // Estimate of performance: O(1)
  // Short rationale for estimate: Inserting into a set of bites is constant-time on average.
  bool add_bite_to_contour(BiteID biteid, ContourID contourid);

  // Estimate of performance: O(k)
  // Short rationale for estimate: Iterates over all contours containing the bite. Assuming `k` is the number of contours, it takes O(k) time.
  std::vector<ContourID> get_bite_in_contours(BiteID id);

  // Non-compulsory operations

  // Estimate of performance: O(k)
  // Short rationale for estimate: Iterates over all subcontours, which takes linear time in the number of subcontours.
  std::vector<ContourID> all_subcontours_of_contour(ContourID id);

  // Estimate of performance: O(n log n)
  // Short rationale for estimate: Sorting bites based on their proximity requires O(n log n) sorting.
  std::vector<BiteID> get_bites_closest_to(Coord xy);

  // Estimate of performance: O(1)
  // Short rationale for estimate: Removing a bite from an unordered map takes constant time on average.
  bool remove_bite(BiteID id);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Finding the common ancestor involves searching through the hierarchy of contours, which can take linear time.
  ContourID get_closest_common_ancestor_of_contours(ContourID id1, ContourID id2);

private:
  struct BiteInfo {
      Name name;
      Coord coord;
      ContourID owner = NO_CONTOUR;
  };

  struct ContourInfo {
      Name name;
      ContourHeight height;
      std::vector<Coord> coords;
      std::set<ContourID> subcontours; // To store IDs of subcontours
      std::set<BiteID> bites; // Assuming contours can contain multiple bites
      ContourID parentID = NO_CONTOUR;
  };

  std::unordered_map<BiteID, BiteInfo> bites_;

  std::unordered_map<ContourID, ContourInfo> contours;

  std::unordered_map<Coord, BiteID> coord_bite_map_;
};

